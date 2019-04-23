#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager {
public:
  InputManager();
  InputManager(GLFWwindow *window);

  glm::vec2 mousePosition() const;

private:
  GLFWwindow *_window;
};
