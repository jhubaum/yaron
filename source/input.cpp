#include <input.hpp>

#include <algorithm>

#include <glm/glm.hpp>

namespace yaron {
  InputManager::InputManager()
    : _window(nullptr)
  {}

  InputManager::InputManager(GLFWwindow *window)
    : _window(window)
  {}

  glm::vec2 InputManager::mousePosition() const {
    if (nullptr == _window)
      return glm::vec2(0.0f, 0.0f);

    double x, y;
    glfwGetCursorPos(_window, &x, &y);

    int width, height;
    glfwGetWindowSize(_window, &width, &height);

    return glm::vec2(std::clamp(static_cast<float>(x / width), 0.0f, 1.0f),
                     std::clamp(1.0f - static_cast<float>(y / height), 0.0f, 1.0f));
  };
}
