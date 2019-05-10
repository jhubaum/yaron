#pragma once

#include <string>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <map>

struct Character {
  GLuint textureID;
  glm::ivec2 size;
  glm::ivec2 bearing;
  uint32_t advance;
};

class TextRenderer {
public:
  static std::shared_ptr<TextRenderer> create(const std::string &fontname, int size);

  ~TextRenderer();

  void renderText(GLFWwindow*, float x, float y, const std::string &text);

private:
  TextRenderer(const std::map<char, Character>&);

  std::map<char, Character> _characters;
  GLuint _vao, _vbo;
};
