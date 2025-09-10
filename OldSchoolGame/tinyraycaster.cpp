#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <span>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Define a 16x16 map
constexpr size_t map_w = 16;
constexpr size_t map_h = 16;
constexpr size_t tileSize = 32;
const char map[] = "0000222222220000"
                   "1              0"
                   "1      11111   0"
                   "1     0        0"
                   "0     0  1110000"
                   "0     3        0"
                   "0   10000      0"
                   "0   0   11100  0"
                   "0   0   0      0"
                   "0   0   1  00000"
                   "0       1      0"
                   "2       1      0"
                   "0       0      0"
                   "0 0000000      0"
                   "0              0"
                   "0002222222200000";

// Representing colors in a 32bit integer
constexpr uint32_t packColor(const uint8_t r, const uint8_t g, const uint8_t b,
                             const uint8_t a = 255) noexcept {
  return (uint32_t(a) << 24) | (uint32_t(b) << 16) | (uint32_t(g) << 8) |
         (uint32_t(r));
}

// Unpack colors into an array
constexpr std::array<uint8_t, 4> unpackColor(uint32_t color) noexcept {
  return {static_cast<uint8_t>(color & 0xFF),
          static_cast<uint8_t>((color >> 8) & 0xFF),
          static_cast<uint8_t>((color >> 16) & 0xFF),
          static_cast<uint8_t>((color >> 24) & 0xFF)};
}

// Save framebuffer as a PPM image
void dropPpmImage(const std::string &filename, std::span<const uint32_t> image,
                  std::size_t w, std::size_t h) {
  assert(image.size() == w * h);

  std::ofstream ofs(filename, std::ios::binary);
  ofs << "P6\n" << w << " " << h << "\n255\n";

  for (auto color : image) {
    auto [r, g, b, a] = unpackColor(color);
    std::array<char, 3> pixel = {static_cast<char>(r), static_cast<char>(g),
                                 static_cast<char>(b)};
    ofs.write(pixel.data(), pixel.size());
  }
}

void drawRectangle(std::vector<uint32_t> &fb, size_t fb_w, size_t fb_h,
                   size_t x, size_t y, size_t w, size_t h, uint32_t color) {
  for (size_t j{}; j < h; ++j) {
    if (y + j >= fb_h)
      continue;
    for (size_t i{}; i < w; ++i) {
      if (x + i >= fb_w)
        continue;
      fb[(y + j) * fb_w + (x + i)] = color;
    }
  }
}

// Bresenham's line drawing algorithm
void drawLine(std::vector<uint32_t> &fb, size_t fb_w, size_t fb_h, int x0,
              int y0, int x1, int y1, uint32_t color) {
  int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;

  while (true) {
    if (x0 >= 0 && y0 >= 0 && x0 < (int)fb_w && y0 < (int)fb_h)
      fb[y0 * fb_w + x0] = color;
    if (x0 == x1 && y0 == y1)
      break;

    int e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    }
  }
}

uint32_t wallColor(char tile) {
  switch (tile) {
  case '1':
    return packColor(122, 56, 3); // dark orange
  case '2':
    return packColor(221, 249, 241); // ice white
  case '3':
    return packColor(0, 21, 21); // dark turquoise
  default:
    return packColor(17, 17, 17); // dark grey
  }
}

std::vector<uint32_t> loadTexture(const std::string &filename, int &tex_w,
                                  int &tex_h) {
  int n;
  unsigned char *data = stbi_load(filename.c_str(), &tex_w, &tex_h, &n, 4);

  if (!data) {
    throw std::runtime_error("Failed to load texture: " + filename);
  }

  std::vector<uint32_t> tex(tex_w * tex_h);

  for (int i{}; i < tex_w * tex_h; i++) {
    tex[i] = (uint32_t(data[4 * i + 3]) << 24) | // A
             (uint32_t(data[4 * i + 2]) << 16) | // B
             (uint32_t(data[4 * i + 1]) << 8) |  // G
             (uint32_t(data[4 * i + 0]));        // R
  }
  stbi_image_free(data);
  return tex;
}

int main() {
  int tex_w, tex_h;
  std::unordered_map<char, std::vector<uint32_t>> textures;

  textures['0'] = loadTexture("cobblestone.png", tex_w, tex_h);
  textures['1'] = loadTexture("lava.png", tex_w, tex_h);
  textures['2'] = loadTexture("whitestone.png", tex_w, tex_h);
  textures['3'] = loadTexture("pentagram.png", tex_w, tex_h);
  constexpr size_t win_w = 512;
  constexpr size_t win_h = 512;

  // Output framebuffer size = 2x width!
  constexpr size_t out_w = win_w * 2;
  constexpr size_t out_h = win_h;

  constexpr int numFrames = 120; // 360deg angle

  // Drawing the player
  float player_x = 3.5f * tileSize;
  float player_y = 3.5f * tileSize;

  for (int frame{}; frame < numFrames; frame++) {
    std::vector<uint32_t> framebuffer(out_w * out_h, packColor(0, 0, 0));

    // Compute angle forr this frame
    float player_a =
        2 * M_PI * frame / numFrames; // Central camera angle, eg ray to where
                                      // the camera is pointing

    // Background filling
    for (size_t j{}; j < win_h; j++) {
      for (size_t i{}; i < win_w; i++)
        framebuffer[j * out_w + i] = packColor(245, 245, 220); // minimap bg

      for (size_t i{win_w}; i < out_w; i++) {
        if (j < win_h / 2)
          framebuffer[j * out_w + i] = packColor(245, 245, 220); // ceiling
        else
          framebuffer[j * out_w + i] = packColor(245, 245, 220); // floor cream
      }
    }

    // Map drawing
    for (size_t j = 0; j < map_h; ++j) {
      for (size_t i = 0; i < map_w; ++i) {
        char tile = map[j * map_w + i];
        if (tile != ' ') {
          // Walls = cyan
          uint32_t color = wallColor(tile);
          drawRectangle(framebuffer, out_w, out_h, i * tileSize, j * tileSize,
                        tileSize, tileSize, color);
        }
      }
    }

    constexpr int player_size = 5;
    int half_size = player_size / 2;

    drawRectangle(framebuffer, out_w, out_h,
                  static_cast<int>(player_x - half_size),
                  static_cast<int>(player_y - half_size), player_size,
                  player_size, packColor(0, 0, 0));

    // FOV rays
    float fov = M_PI / 3.0f;
    int numRays = win_w;

    // FOV Direction minimap
    for (int k{}; k < numRays; k++) {
      float t = float(k) / (numRays - 1);
      float ang = player_a - fov / 2 + fov * t; // per-ray angle
      float dx = cos(ang), dy = sin(ang);
      int x1 = int(player_x + dx * 40);
      int y1 = int(player_y + dy * 40);
      drawLine(framebuffer, out_w, out_h, int(player_x), int(player_y), x1, y1,
               packColor(57, 255, 20));
    }

    // 3D Rendering into right half
    for (int k{}; k < numRays; k++) {

      float angle =
          player_a - fov / 2 + fov * (static_cast<float>(k) / (numRays - 1));
      // player_a - fov/2 is the left most ray, while adding fov * k/numRays
      // creates player_a + fov/2 rightmost

      float dirX = std::cos(angle); // Directional vectors
      float dirY = std::sin(angle);

      // Raymcarching until wall
      float posX = player_x / float(tileSize);
      float posY = player_y / float(tileSize);

      int mapX = int(posX);
      int mapY = int(posY);

      float deltaDistX = (dirX == 0) ? 1e30f : fabs(1.0f / dirX);
      float deltaDistY = (dirY == 0) ? 1e30f : fabs(1.0f / dirY);

      int stepX, stepY;
      float sideDistX, sideDistY;

      if (dirX < 0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      } else {
        stepX = 1;
        sideDistX = (mapX + 1.0f - posX) * deltaDistX;
      }
      if (dirY < 0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      } else {
        stepY = 1;
        sideDistY = (mapY + 1.0f - posY) * deltaDistY;
      }

      bool hit = false;
      int side{};
      char hitTile = ' ';

      while (!hit) {
        if (sideDistX < sideDistY) {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        } else {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        if (mapX < 0 || mapX >= (int)map_w || mapY < 0 || mapY >= (int)map_h)
          break;
        char tile = map[mapY * map_w + mapX];
        if (tile != ' ') {
          hit = true;
          hitTile = tile;
        }
      }

      // Distance to wall (perpendicular)
      float perpWallDist;
      if (side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2.0f) / dirX;
      else
        perpWallDist = (mapY - posY + (1 - stepY) / 2.0f) / dirY;

      // Projected wall height
      int wall_h =
          (int)((win_h * tileSize) / (perpWallDist * tileSize + 1e-6f));
      int y0 = win_h / 2 - wall_h / 2;
      int y1 = win_h / 2 + wall_h / 2;
      if (y0 < 0)
        y0 = 0;
      if (y1 > (int)win_h)
        y1 = win_h;

      // ---- Texture sampling ----
      if (textures.find(hitTile) != textures.end()) {
        auto &tex = textures[hitTile];

        float wallX; // exact hit location in [0,1)
        if (side == 0)
          wallX = posY + perpWallDist * dirY;
        else
          wallX = posX + perpWallDist * dirX;
        wallX -= floor(wallX);

        int tex_x = int(wallX * tex_w);
        if (side == 0 && dirX > 0)
          tex_x = tex_w - tex_x - 1;
        if (side == 1 && dirY < 0)
          tex_x = tex_w - tex_x - 1;

        int col = win_w + k;
        for (int y = y0; y < y1; ++y) {
          int d = (y - y0) * 256;
          int tex_y = ((d * tex_h) / wall_h) / 256;
          framebuffer[y * out_w + col] = tex[tex_y * tex_w + tex_x];
        }
      } else {
        // fallback flat color
        uint32_t color = wallColor(hitTile);
        int col = win_w + k;
        for (int y = y0; y < y1; ++y) {
          framebuffer[y * out_w + col] = color;
        }
      }
    }

    char fname[64];
    sprintf(fname, "frametex_%03d.ppm", frame);
    dropPpmImage(fname, framebuffer, out_w, out_h);
  }
  return 0;
}