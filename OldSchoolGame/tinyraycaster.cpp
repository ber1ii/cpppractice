#include "color.h"
#include "draw.h"
#include "image.h"
#include "map.h"
#include "sprite.h"
#include "texture.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

// Pick flat colors in case texture lookup fails
uint32_t wallColor(char tile) {
  switch (tile) {
  case '1':
    return packColor(122, 56, 3); // dark orange (lava)
  case '2':
    return packColor(221, 249, 241); // ice white
  case '3':
    return packColor(0, 21, 21); // dark turquoise
  default:
    return packColor(17, 17, 17); // dark grey
  }
}

int main() {
  int tex_w, tex_h;
  std::unordered_map<char, std::vector<uint32_t>> textures;
  std::unordered_map<std::string, std::vector<uint32_t>> spriteTextures;
  std::unordered_map<std::string, std::pair<int, int>>
      spriteTexSize; // store w,h

  // Load wall textures
  textures['0'] = loadTexture("textures/cobblestone.png", tex_w, tex_h);
  textures['1'] = loadTexture("textures/lava.png", tex_w, tex_h);
  textures['2'] = loadTexture("textures/whitestone.png", tex_w, tex_h);
  textures['3'] = loadTexture("textures/pentagram.png", tex_w, tex_h);

  spriteTextures["caprademon"] =
      loadTexture("textures/caprademon.png", tex_w, tex_h);
  spriteTexSize["caprademon"] = {tex_w, tex_h};

  spriteTextures["imp"] = loadTexture("textures/imp.png", tex_w, tex_h);
  spriteTexSize["imp"] = {tex_w, tex_h};

  spriteTextures["elemental"] =
      loadTexture("textures/elemental.png", tex_w, tex_h);
  spriteTexSize["elemental"] = {tex_w, tex_h};

  spriteTextures["lostsoul"] =
      loadTexture("textures/lostsoul.png", tex_w, tex_h);
  spriteTexSize["lostsoul"] = {tex_w, tex_h};

  std::vector<Sprite> sprites = {
      {3.5f, 4.5f, "imp"} // just below the player’s start
  };

  // Window dimensions
  constexpr size_t win_w = 512;
  constexpr size_t win_h = 512;

  // Output framebuffer: right half is 3D view, left half is minimap
  constexpr size_t out_w = win_w * 2;
  constexpr size_t out_h = win_h;

  constexpr int numFrames = 120; // 120 frames (simulate 360° rotation)

  // Starting position of the player (center-ish of map)
  float player_x = 3.5f * tileSize;
  float player_y = 3.5f * tileSize;

  for (int frame = 0; frame < numFrames; frame++) {
    // Framebuffer: initialized to black
    std::vector<uint32_t> framebuffer(out_w * out_h, packColor(0, 0, 0));

    // Determine player's viewing angle for this frame
    float player_a = 2 * M_PI * frame / numFrames;
    // Central camera angle, eg ray to where
    // the camera is pointing
    std::vector<float> zBuffer(win_w);

    // === BACKGROUND FILL ===
    for (size_t j = 0; j < win_h; j++) {
      for (size_t i = 0; i < win_w; i++)
        framebuffer[j * out_w + i] = packColor(245, 245, 220); // minimap bg

      for (size_t i = win_w; i < out_w; i++) {
        if (j < win_h / 2)
          framebuffer[j * out_w + i] = packColor(245, 245, 220); // ceiling
        else
          framebuffer[j * out_w + i] = packColor(245, 245, 220); // floor
      }
    }

    // === DRAW MAP ===
    for (size_t j = 0; j < map_h; ++j) {
      for (size_t i = 0; i < map_w; ++i) {
        char tile = map[j * map_w + i];
        if (tile != ' ') {
          drawRectangle(framebuffer, out_w, out_h, i * tileSize, j * tileSize,
                        tileSize, tileSize, wallColor(tile));
        }
      }
    }

    // DRAW SPRITES ON MAP
    for (auto &s : sprites) {
      int px = int(s.x * tileSize);
      int py = int(s.y * tileSize);
      drawRectangle(framebuffer, out_w, out_h, px - 2, py - 2, 4, 4,
                    packColor(255, 0, 255)); // magenta = sprite
    }

    // === DRAW PLAYER ON MINIMAP ===
    constexpr int player_size = 5;
    int half_size = player_size / 2;
    drawRectangle(framebuffer, out_w, out_h, int(player_x - half_size),
                  int(player_y - half_size), player_size, player_size,
                  packColor(0, 0, 0));

    // === CAST RAYS (FOR BOTH MINIMAP + 3D VIEW) ===
    float fov = M_PI / 3.0f;
    int numRays = win_w;

    // 3D RENDERING
    for (int k = 0; k < numRays; k++) {
      float ray_angle = player_a - fov / 2 + fov * (float(k) / (numRays - 1));
      // player_a - fov/2 is the left most ray, while adding fov * k/numRays
      // creates player_a + fov/2 rightmost
      float dirX = cos(ray_angle), dirY = sin(ray_angle);

      // Draw green rays on minimap (short preview rays)
      int ray_x = int(player_x + dirX * 40);
      int ray_y = int(player_y + dirY * 40);
      drawLine(framebuffer, out_w, out_h, int(player_x), int(player_y), ray_x,
               ray_y, packColor(57, 255, 20));

      // === RAYCASTING LOOP (DDA) ===
      float posX = player_x / float(tileSize);
      float posY = player_y / float(tileSize);

      int mapX = int(posX);
      int mapY = int(posY);

      float deltaDistX = (dirX == 0) ? 1e30f : std::fabs(1.0f / dirX);
      float deltaDistY = (dirY == 0) ? 1e30f : std::fabs(1.0f / dirY);

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

      // Step until hit
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

      // === WALL HEIGHT CALCULATION ===
      float perpWallDist;
      if (side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2.0f) / dirX;
      else
        perpWallDist = (mapY - posY + (1 - stepY) / 2.0f) / dirY;

      zBuffer[k] = perpWallDist;
      int wall_h = int((win_h * tileSize) / (perpWallDist * tileSize + 1e-6f));
      int y0 = win_h / 2 - wall_h / 2;
      int y1 = win_h / 2 + wall_h / 2;
      if (y0 < 0)
        y0 = 0;
      if (y1 > (int)win_h)
        y1 = win_h;

      // === TEXTURE SAMPLING ===
      int col = win_w + k; // draw into 3D side (right half)
      if (textures.find(hitTile) != textures.end()) {
        auto &tex = textures[hitTile];
        float wallX;
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

        for (int y = y0; y < y1; ++y) {
          int d = (y - y0) * 256;
          int tex_y = ((d * tex_h) / wall_h) / 256;
          framebuffer[y * out_w + col] = tex[tex_y * tex_w + tex_x];
        }
      } else {
        // fallback: solid color
        uint32_t color = wallColor(hitTile);
        for (int y = y0; y < y1; ++y) {
          framebuffer[y * out_w + col] = color;
        }
      }
    }
    std::vector<Sprite> sortedSprites = sprites;

    std::sort(sortedSprites.begin(), sortedSprites.end(),
              [&](const Sprite &a, const Sprite &b) {
                float dxA = a.x * tileSize + float(tileSize) / 2 - player_x;
                float dyA = a.y * tileSize + float(tileSize) / 2 - player_y;
                float dxB = b.x * tileSize + float(tileSize) / 2 - player_x;
                float dyB = b.y * tileSize + float(tileSize) / 2 - player_y;
                // sort descending (farthest first)
                return dxA * dxA + dyA * dyA > dxB * dxB + dyB * dyB;
              });

    /*printf("Sprite %s: transformX=%.2f transformY=%.2f screenX=%d\n",
           s.type.c_str(), transformX, transformY, spriteScreenX);*/

    renderSprites(framebuffer, out_w, win_w, win_h, player_x, player_y,
                  player_a, zBuffer, sortedSprites, spriteTextures,
                  spriteTexSize);

    // Save current frame
    char fname[64];
    std::sprintf(fname, "framenext_%03d.ppm", frame);
    dropPpmImage(fname, framebuffer, out_w, out_h);
  }

  return 0;
}