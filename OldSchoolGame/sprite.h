#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

// Sprite = just position + type (texture lookup happens via type)
struct Sprite {
  float x;
  float y;
  std::string type;
};

void renderSprites(
    std::vector<uint32_t> &framebuffer, size_t out_w, size_t win_w,
    size_t win_h, float player_x, float player_y, float player_a,
    const std::vector<float> &zBuffer, const std::vector<Sprite> &sprites,
    const std::unordered_map<std::string, std::vector<uint32_t>>
        &spriteTextures,
    const std::unordered_map<std::string, std::pair<int, int>> &spriteTexSize);