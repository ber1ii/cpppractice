#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <span>
#include <string>
#include <vector>

// Representing colors
constexpr uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b,
                              const uint8_t a = 255) noexcept {
  return (uint32_t(a) << 24) | (uint32_t(b) << 16) | (uint32_t(g) << 8) |
         (uint32_t(r));
}

constexpr std::array<uint8_t, 4> unpack_color(uint32_t color) noexcept {
  return {static_cast<uint8_t>(color & 0xFF),
          static_cast<uint8_t>((color >> 8) & 0xFF),
          static_cast<uint8_t>((color >> 16) & 0xFF),
          static_cast<uint8_t>((color >> 24) & 0xFF)};
}

void drop_ppm_image(const std::string &filename,
                    std::span<const uint32_t> image, std::size_t w,
                    std::size_t h) {
  assert(image.size() == w * h);

  std::ofstream ofs(filename, std::ios::binary);
  ofs << "P6\n" << w << " " << h << "\n255\n";

  for (auto color : image) {
    auto [r, g, b, a] = unpack_color(color);
    std::array<char, 3> pixel = {static_cast<char>(r), static_cast<char>(g),
                                 static_cast<char>(b)};
    ofs.write(pixel.data(), pixel.size());
  }
}

int main() {
  constexpr size_t win_w = 512;
  constexpr size_t win_h = 512;

  std::vector<uint32_t> framebuffer(win_w * win_h);

  for (size_t j{}; j < win_h; ++j) {
    for (size_t i{}; i < win_w; ++i) {
      uint8_t r = static_cast<uint8_t>(255.0f * j / win_h);
      uint8_t g = static_cast<uint8_t>(255.0f * i / win_w);
      uint8_t b = 0;
      framebuffer[i + j * win_w] = pack_color(r, g, b);
    }
  }

  drop_ppm_image("out.ppm", framebuffer, win_w, win_h);
}