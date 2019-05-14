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
      /// The representation of the texture for a font character
      struct Character {
        GLuint textureID; /*!< the texture id*/
        glm::ivec2 size; /*!< the width and height of the character in pixels*/
        glm::ivec2 bearing; /*!< the position of the character relative to the baseline in pixels*/
        uint32_t advance; /*!< the horizontal distance of the origin of this character to the origin of the next character*/
      };
    }

    /// The representation of a text that can be rendered
    struct Text {
      std::string text; /*!< the actual text*/
      glm::vec2 pos; /*!< the position of the text (in normalized screen coordinates)*/
      Color color; /*!< the text color*/
      float scale; /*!< a scaling factor for the text*/

      /// Create a new Text object
      /**
       * the color will be initialized to be black, the scale will have the value 1.0f
       * \param text the actual text
       * \param pos the screen coordinates for the text
       */
      Text(const std::string &text, const glm::vec2 &pos);

      /// Create a new Text object
      /**
       * \param text the actual text
       * \param pos the screen coordinates for the text
       * \param col the text color
       * \param scale the scale of the text
       */
      Text(const std::string &text, const glm::vec2 &pos,
           const Color &col, float scale=1.0f);
    };

    /// A renderer class for 2D text
    /**
     * This class is used to render text represented by a Text object
     */
    class TextRenderer {
    public:
      /// Create a new TextRenderer
      /**
       * \param fontname the font that will be used for the renderer
       * \param size the fontsize for the renderer in pixels
       */
      static std::shared_ptr<TextRenderer> create(const std::string &fontname, int size);

      ~TextRenderer();

      /// Render a Text object
      /**
       * \param context the RenderContext that will be used to render the text
       * \param text the text that will be rendered
       */
      void renderText(RenderContextPtr, const Text&);

    private:
      TextRenderer(const std::map<char, _internal::Character>&,
                   GLuint vao, GLuint vbo);

      std::map<char, _internal::Character> _characters;
      GLuint _vao, _vbo;
    };
  }
}
