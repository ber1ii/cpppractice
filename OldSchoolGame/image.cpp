#include "image.h"
#include "color.h"
#include <array>
#include <cassert>
#include <fstream>

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