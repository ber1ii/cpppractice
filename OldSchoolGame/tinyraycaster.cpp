#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <span>
#include <string>
#include <vector>

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

int main() {
  constexpr size_t win_w = 512;
  constexpr size_t win_h = 512;

  // Output framebuffer size = 2x width!
  constexpr size_t out_w = win_w * 2;
  constexpr size_t out_h = win_h;

  std::vector<uint32_t> framebuffer(out_w * out_h);

  // Minimap floor color
  for (size_t j = 0; j < win_h; ++j) {
    for (size_t i = 0; i < win_w; ++i) {
      framebuffer[i + j * out_w] = packColor(245, 245, 220);
    }
  }

  for (size_t j{}; j < win_h; j++) {
    for (size_t i = win_w; i < out_w; i++) {
      if (j < win_h / 2) {
        framebuffer[i + j * out_w] = packColor(245, 245, 220); // White
      } else {
        framebuffer[i + j * out_w] = packColor(245, 245, 220); // Beige
      }
    }
  }

  // Define a 16x16 map
  constexpr size_t map_w = 16;
  constexpr size_t map_h = 16;
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
  constexpr size_t tileSize = 32;

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

  // Drawing the player
  float player_x = 3.5f * tileSize;
  float player_y = 3.5f * tileSize;

  constexpr int player_size = 5;
  int half_size = player_size / 2;

  drawRectangle(framebuffer, out_w, out_h,
                static_cast<int>(player_x - half_size),
                static_cast<int>(player_y - half_size), player_size,
                player_size, packColor(0, 0, 0));

  // Player direction
  float player_a = M_PI / 4.0f;

  // FOV rays
  float fov = M_PI / 3.0f;
  int numRays = win_w;

  // FOV Direction minimap
  for (int k = 0; k < numRays; k++) {
    float t = float(k) / (numRays - 1);
    float ang = player_a - fov / 2 + fov * t;
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
    // creates player_a + fov/2

    float dirX = std::cos(angle); // Directional vectors
    float dirY = std::sin(angle);

    // Raymcarching until wall
    float rayX = player_x;
    float rayY = player_y;
    float dist = 0.f;
    const float step = 1.f;
    char hitTile = ' ';

    while (true) {
      int mapX = static_cast<int>(rayX / tileSize); // y index
      int mapY = static_cast<int>(rayY / tileSize); // x index

      if (mapX < 0 || mapY < 0 || mapX >= (int)map_w || mapY >= (int)map_h)
        break;

      char tile = map[mapY * map_w + mapX]; // mapY * map_w = correct row (eg
                                            // row 2*16) + mapX is the column
      if (tile != ' ') {
        hitTile = tile;
        break;
      }

      rayX += dirX * step; // Store each ray while moving forward
      rayY += dirY * step; // and return it to mapX and mapY
      dist += step;
    }

    int wall_h = (int)((win_h * tileSize) / (dist + 0.0001f));
    // screenHeight = wall_h, realHeight = tileSize, focalLength = win_h,
    // distance = measured ray length
    // screenHeight = (realHeight * focalLength) / distance

    int y0 = win_h / 2 - wall_h / 2; // locking y axis
    int y1 = win_h / 2 + wall_h / 2;

    if (y0 < 0)
      y0 = 0;
    if (y1 > (int)win_h)
      y1 = win_h;

    uint32_t color = wallColor(hitTile);

    int col = win_w + k;
    for (int y = y0; y < y1; y++) {
      framebuffer[y * out_w + col] = color;
    }
  }

  dropPpmImage("3dmodel.ppm", framebuffer, out_w, out_h);
  return 0;
}