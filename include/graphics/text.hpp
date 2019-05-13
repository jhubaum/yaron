#pragma once
#include <fwd.hpp>

#include <map>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <color.hpp>

namespace yaron {
  namespace graphics {
    namespace _internal {
      struct Character {
        GLuint textureID;
        glm::ivec2 size;
        glm::ivec2 bearing;
        uint32_t advance;
      };
    }

    struct Text {
      std::string text;
      glm::vec2 pos;
      Color color;
      float scale;

      Text(const std::string &text, const glm::vec2 &pos);
      Text(const std::string &text, const glm::vec2 &pos,
           const Color &col, float scale=1.0f);
    };

    class TextRenderer {
    public:
      static std::shared_ptr<TextRenderer> create(const std::string &fontname, int size);

      ~TextRenderer();

      void renderText(RenderContextPtr, const Text&);

    private:
      TextRenderer(const std::map<char, _internal::Character>&,
                   GLuint vao, GLuint vbo);

      std::map<char, _internal::Character> _characters;
      GLuint _vao, _vbo;
    };
  }
}
