#pragma once
#include <fwd.hpp>

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

namespace yaron {
  class InputManager {
  public:
    glm::vec2 mousePosition() const;

    bool getKeyPressed(int key);
    bool getKeyDown(int key);
    bool getKeyUp(int key);

    void update(GLFWwindow *window);

  private:
    enum class KeyState {
      None,
      Pressed,
      Down,
      Up
    };

    KeyState _getKeyState(int key);

    std::map<int, KeyState> _keys;
    glm::vec2 _mousePosition;
  };
}
