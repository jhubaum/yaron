#pragma once
#include <fwd.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace yaron {
  class Controller {
  public:
    Controller();
    Controller(std::weak_ptr<Transform> transform, GLFWwindow *window);
    void update(float dt);

  private:
    std::weak_ptr<Transform> _transform;
    GLFWwindow *_window;

    float _xAxisRot;
    float _yAxisRot;
  };
}
