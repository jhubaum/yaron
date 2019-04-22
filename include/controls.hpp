#pragma once

#include <camera.hpp>
#include <memory>

#include <GLFW/glfw3.h>

class Controller {
public:
  Controller();
  Controller(std::weak_ptr<PerspectiveCamera> camera, GLFWwindow *window);
  void update(float dt);

private:
  std::weak_ptr<PerspectiveCamera> _camera;
  GLFWwindow *_window;

  float _xAxisRot;
  float _yAxisRot;
};
