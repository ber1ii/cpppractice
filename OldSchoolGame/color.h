#pragma once
#include <array>
#include <cstdint>

constexpr uint32_t packColor(uint8_t r, uint8_t g, uint8_t b,
                             uint8_t a = 255) noexcept {
  return (uint32_t(a) << 24) | (uint32_t(b) << 16) | (uint32_t(g) << 8) |
         (uint32_t(r));
}

constexpr std::array<uint8_t, 4> unpackColor(uint32_t color) noexcept {
  return {static_cast<uint8_t>(color & 0xFF),
          static_cast<uint8_t>((color >> 8) & 0xFF),
          static_cast<uint8_t>((color >> 16) & 0xFF),
          static_cast<uint8_t>((color >> 24) & 0xFF)};
}