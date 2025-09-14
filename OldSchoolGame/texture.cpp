#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"
#include "stb_image.h"
#include <cstdint>
#include <stdexcept>
#include <vector>

std::vector<uint32_t> loadTexture(const std::string &filename, int &tex_w,
                                  int &tex_h) {
  int n;
  unsigned char *data = stbi_load(filename.c_str(), &tex_w, &tex_h, &n, 4);
  if (!data) {
    throw std::runtime_error("Failed to load texture: " + filename);
  }

  std::vector<uint32_t> tex(tex_w * tex_h);

  for (int i = 0; i < tex_w * tex_h; i++) {
    // Force opaque alpha channel (0xFF)
    tex[i] = (0xFFu << 24) | (uint32_t(data[4 * i + 2]) << 16) | // B
             (uint32_t(data[4 * i + 1]) << 8) |                  // G
             (uint32_t(data[4 * i + 0]));                        // R
  }

  stbi_image_free(data);
  return tex;
}