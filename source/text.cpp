#include <text.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

std::shared_ptr<TextRenderer> TextRenderer::create(const std::string &fontname, int size) {
  // Load font face
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "Freetype Error: Could not initialize Library" << std::endl;

  FT_Face face;
  if (FT_New_Face(ft, fontname.c_str(), 0, &face))
    std::cout << "Freetype Error: Failed to load font " << fontname << std::endl;

  FT_Set_Pixel_Sizes(face, 0, size);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // Load characters
  std::map<char, Character> chars;
  for (char c=0; c<128; ++c) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      std::cout << "Freetype Error: Could not load face" << std::endl;
      continue;
    }

    // generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,
                 face->glyph->bitmap.width,
                 face->glyph->bitmap.rows,
                 0, GL_R8, GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer);

    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    chars.insert({c, {
      texture,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      static_cast<uint32_t>(face->glyph->advance.x)
    }});
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  return std::shared_ptr<TextRenderer>(new TextRenderer(chars));
}

TextRenderer::TextRenderer(const std::map<char, Character> &chars)
  : _characters(chars)
{ }

TextRenderer::~TextRenderer() {
  for (auto it = _characters.begin(); it != _characters.end(); it++)
    glDeleteTextures(1, &it->second.textureID);
}

void TextRenderer::renderText(GLFWwindow *window, float x_f, float y_f, const std::string &text) {
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  int x = static_cast<int>(x_f * width);
  int y = static_cast<int>(y_f * height);
}
