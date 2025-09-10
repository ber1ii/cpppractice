#pragma once
#include <cstddef>
#include <cstdint>
#include <span>
#include <string>

void dropPpmImage(const std::string &filename, std::span<const uint32_t> image,
                  std::size_t w, std::size_t h);