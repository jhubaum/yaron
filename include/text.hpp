#pragma once

#include <string>
#include <memory>

class TextRenderer {
public:
  static std::shared_ptr<TextRenderer> create(const std::string &fontname, int size);

  ~TextRenderer();

  //void renderText(uint32_t x, uint32_t y, const std::string &text);
  void renderText(float x, float y, const std::string &text);

private:
  TextRenderer(const std::string &fontname, int size);
};
