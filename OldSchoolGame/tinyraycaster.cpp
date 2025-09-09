#include <array>
#include <cassert>
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

int main() {
  constexpr size_t win_w = 512;
  constexpr size_t win_h = 512;

  std::vector<uint32_t> framebuffer(win_w * win_h);

  // Define a 16x16 map
  constexpr size_t map_w = 16;
  constexpr size_t map_h = 16;
  const std::array<std::array<int, map_w>, map_h> map = {
      {{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
       {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
       {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
       {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
       {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}},
       {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}}};

  constexpr size_t tileSize = 32;

  for (size_t j{}; j < map_h; ++j) {
    for (size_t i{}; i < map_w; ++i) {
      uint32_t color = (map[j][i] == 1)
                           ? packColor(255, 255, 255) // Walls = white
                           : packColor(0, 0, 0);      // Walls = black
      drawRectangle(framebuffer, win_w, win_h, i * tileSize, j * tileSize,
                    tileSize, tileSize, color);
    }
  }

  dropPpmImage("map.ppm", framebuffer, win_w, win_h);

  return 0;
}