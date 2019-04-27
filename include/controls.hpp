#pragma once

#include <camera.hpp>
#include <memory>

#include <GLFW/glfw3.h>

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
