#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <object.hpp>

class RenderContext {
public:
  RenderContext();

  bool init(uint32_t width, uint32_t height);
  void deinit();

  void beginFrame();
  void endFrame();

  void useShader(GLuint shader);
  void renderObject(const Object &object);

  bool exitRequest() const;

private:
  GLFWwindow *_window;
};
