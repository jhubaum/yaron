#include <text.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

std::shared_ptr<TextRenderer> TextRenderer::create(const std::string &fontname, int size) {
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

  FT_Face face;
  if (FT_New_Face(ft, fontname.c_str(), 0, &face))
    std::cout << "Freetype Error: Failed to load font " << fontname << std::endl;

  FT_Set_Pixel_Sizes(face, 0, size);

  TextRenderer *renderer = new TextRenderer(fontname, size);

  return std::shared_ptr<TextRenderer>(renderer);
}

TextRenderer::TextRenderer(const std::string &fontname, int size) {
  
}

TextRenderer::~TextRenderer() {
}

//void TextRenderer::renderText(uint32_t x, uint32_t y, const std::string &text) {
//}

void TextRenderer::renderText(float x, float y, const std::string &text) {
}
