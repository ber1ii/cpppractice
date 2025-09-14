#include "sprite.h"
#include "map.h"
#include <algorithm> // for std::min, std::max
#include <cmath>

void renderSprites(
    std::vector<uint32_t> &framebuffer, size_t out_w, size_t win_w,
    size_t win_h, float player_x, float player_y, float player_a,
    const std::vector<float> &zBuffer, const std::vector<Sprite> &sprites,
    const std::unordered_map<std::string, std::vector<uint32_t>>
        &spriteTextures,
    const std::unordered_map<std::string, std::pair<int, int>> &spriteTexSize) {
  for (auto &s : sprites) {
    // Convert from map units → world pixels
    float spriteX = s.x * tileSize + float(tileSize) / 2 - player_x;
    float spriteY = s.y * tileSize + float(tileSize) / 2 - player_y;

    float dirX = cos(player_a);
    float dirY = sin(player_a);
    float planeX = -dirY * 0.66f;
    float planeY = dirX * 0.66f;

    // Inverse camera transform
    float invDet = 1.0f / (planeX * dirY - dirX * planeY);

    // camera space
    float transformX = invDet * (dirY * spriteX - dirX * spriteY);
    float transformY = invDet * (-planeY * spriteX + planeX * spriteY);
    if (transformY <= 0)
      continue; // behind camera

    int spriteScreenX =
        int((float(win_w) / 2.0f) * (1 + transformX / transformY));

    // Project sprite onto screen
    int spriteHeight = std::abs(int(win_h / transformY));
    int drawStartY = std::max(-spriteHeight / 2 + (int)win_h / 2, 0);
    int drawEndY = std::min(spriteHeight / 2 + (int)win_h / 2, (int)win_h - 1);

    int spriteWidth = spriteHeight;
    int drawStartX = std::max(-spriteWidth / 2 + spriteScreenX, 0);
    int drawEndX = std::min(spriteWidth / 2 + spriteScreenX, (int)win_w - 1);

    // Lookup texture
    auto &tex = spriteTextures.at(s.type);
    auto [tex_w, tex_h] = spriteTexSize.at(s.type);

    // Draw vertical strips
    for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
      int texX = (int)((stripe - (-spriteWidth / 2 + spriteScreenX)) * tex_w /
                       spriteWidth);

      // if (transformY > 0 && stripe >= 0 && stripe < (int)win_w &&
      //     transformY < zBuffer[stripe]) {
      if (transformY > 0 && stripe >= 0 && stripe < (int)win_w) {
        for (int y = drawStartY; y < drawEndY; y++) {
          int d = (y - (-spriteHeight / 2 + win_h / 2)) * 256;
          int texY = (d * tex_h / spriteHeight) / 256;

          uint32_t color = tex[texY * tex_w + texX];
          if ((color >> 24) > 0) { // alpha test
            framebuffer[y * out_w + (win_w + stripe)] = color;
          }
        }
      }
    }
  }
}