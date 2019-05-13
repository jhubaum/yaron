#include <controls.hpp>
#include <transform.hpp>


namespace yaron {
  Controller::Controller()
  {}

  Controller::Controller(std::weak_ptr<Transform> transform, GLFWwindow *window)
    : _transform(transform), _window(window), _xAxisRot(0.0f),
      _yAxisRot(0.0f)
  {}

  bool getKey(GLFWwindow *w, int key) {
    return GLFW_PRESS == glfwGetKey(w, key);
  }

  float clampRotation(float rot) {
    if (rot < 0.0f)
      return rot + 1.0f;
    if (rot > 1.0f)
      return rot - 1.0f;
    return rot;
  }

  void Controller::update(float dt) {
    if (_transform.expired())
      return;

    auto t = _transform.lock();

    if (getKey(_window, GLFW_KEY_LEFT_SHIFT))
      dt *= 2.0f;

    glm::vec3 pos(0.0f, 0.0f, 0.0f);

    if (getKey(_window, GLFW_KEY_W))
      pos.z += dt;
    if (getKey(_window, GLFW_KEY_S))
      pos.z -= dt;
    if (getKey(_window, GLFW_KEY_A))
      pos.x += dt;
    if (getKey(_window, GLFW_KEY_D))
      pos.x -= dt;

    if (getKey(_window, GLFW_KEY_LEFT_CONTROL))
      pos.y -= dt;
    if (getKey(_window, GLFW_KEY_SPACE))
      pos.y += dt;


    dt *= 0.125f;
    if (getKey(_window, GLFW_KEY_UP))
      _xAxisRot += dt;
    if (getKey(_window, GLFW_KEY_DOWN))
      _xAxisRot -= dt;
    if (getKey(_window, GLFW_KEY_LEFT))
      _yAxisRot += dt;
    if (getKey(_window, GLFW_KEY_RIGHT))
      _yAxisRot -= dt;

    _xAxisRot = clampRotation(_xAxisRot);
    _yAxisRot = clampRotation(_yAxisRot);



    t->rotation = glm::quat({_xAxisRot * glm::pi<float>() * 2.0f,
                             _yAxisRot * glm::pi<float>() * 2.0f,
                             0.0f});

    t->position += glm::mat3_cast(t->rotation) * pos;
  }
}
