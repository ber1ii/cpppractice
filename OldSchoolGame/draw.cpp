#include "draw.h"
#include <cmath>

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

void drawLine(std::vector<uint32_t> &fb, size_t fb_w, size_t fb_h, int x0,
              int y0, int x1, int y1, uint32_t color) {
  int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;
  while (true) {
    if (x0 >= 0 && y0 >= 0 && x0 < (int)fb_w && y0 < (int)fb_h) {
      fb[y0 * fb_w + x0] = color;
    }
    if (x0 == x1 && y0 == y1)
      break;
    int e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    }
  }
}