#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <object.hpp>
#include <camera.hpp>

class RenderContext {
public:
  RenderContext();

  bool init(uint32_t width, uint32_t height);
  void deinit();

  void beginFrame(const glm::mat4 &viewProjectionMatrix);
  void endFrame();

  void useShader(GLuint shader);
  void renderObject(const Object &object);

  bool exitRequest() const;

  float aspectRatio() const { return _aspect; }

private:
  GLFWwindow *_window;
  glm::mat4 _viewProjectionMatrix;
  GLuint _mvpHandle;

  float _aspect;
};
