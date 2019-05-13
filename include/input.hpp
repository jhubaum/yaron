#pragma once
#include <fwd.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace yaron {
  class InputManager {
  public:
    InputManager();
    InputManager(GLFWwindow *window);

    glm::vec2 mousePosition() const;

  private:
    GLFWwindow *_window;
  };
}
