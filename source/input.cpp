#include <input.hpp>

#include <algorithm>

#include <glm/glm.hpp>

namespace yaron {
  void InputManager::update(GLFWwindow *window) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    _mousePosition = glm::vec2(std::clamp(static_cast<float>(x / width),
                                          0.0f, 1.0f),
                               std::clamp(1.0f - static_cast<float>(y / height),
                                          0.0f, 1.0f));

    for (auto & key : _keys) {
      if (GLFW_PRESS == glfwGetKey(window, key.first))
        key.second =
          (KeyState::Pressed == key.second ||
           KeyState::Down == key.second) ?
          KeyState::Down : KeyState::Pressed;
      else
        key.second = KeyState::Up;
    }
  }

  glm::vec2 InputManager::mousePosition() const {
    return _mousePosition;
  }

  bool InputManager::getKeyPressed(int key) {
    return KeyState::Pressed == _getKeyState(key);
  }

  bool InputManager::getKeyDown(int key) {
    return KeyState::Down == _getKeyState(key);
  }

  bool InputManager::getKeyUp(int key) {
    return KeyState::Up == _getKeyState(key);
  }

  InputManager::KeyState InputManager::_getKeyState(int key) {
    auto search = _keys.find(key);

    if(_keys.end() == search) {
      _keys.insert({key, KeyState::None});
      return KeyState::None;
    }
    return search->second;
  }
}
