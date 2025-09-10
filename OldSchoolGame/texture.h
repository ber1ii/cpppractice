#pragma once
#include <cstdint>
#include <string>
#include <vector>

std::vector<uint32_t> loadTexture(const std::string &filename, int &tex_w,
                                  int &tex_h);