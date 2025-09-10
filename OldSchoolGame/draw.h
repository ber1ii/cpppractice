#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

void drawRectangle(std::vector<uint32_t> &fb, size_t fb_w, size_t fb_h,
                   size_t x, size_t y, size_t w, size_t h, uint32_t color);

void drawLine(std::vector<uint32_t> &fb, size_t fb_w, size_t fb_h, int x0,
              int y0, int x1, int y1, uint32_t color);