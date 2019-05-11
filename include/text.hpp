#pragma once

#include <string>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <color.hpp>

#include <map>

struct Character {
  GLuint textureID;
  glm::ivec2 size;
  glm::ivec2 bearing;
  uint32_t advance;
};

struct Text {
  Text(const std::string &text, const glm::vec2 &pos);
  Text(const std::string &text, const glm::vec2 &pos, const Color &col, float scale=1.0f);

  std::string text;
  glm::vec2 pos;
  Color color;
  float scale;
};

class TextRenderer {
public:
  static std::shared_ptr<TextRenderer> create(const std::string &fontname, int size);

  ~TextRenderer();

  void renderText(GLFWwindow*, const Text&);

private:
  TextRenderer(const std::map<char, Character>&, GLuint, GLuint);

  std::map<char, Character> _characters;
  GLuint _vao, _vbo;
};
