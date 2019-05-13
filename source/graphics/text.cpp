#include <graphics/text.hpp>

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <graphics/context.hpp>
#include <graphics/shader.hpp>

yaron::graphics::ShaderPtr createTextShader() {
  return yaron::graphics::ShaderBuilder()
    .addVertexShader("resources/shaders/text.vertexshader")
    .addFragmentShader("resources/shaders/text.fragmentshader")
    .build();
}

static yaron::graphics::ShaderPtr shader = nullptr;

namespace yaron {
  namespace graphics {
    Text::Text(const std::string &text, const glm::vec2 &pos)
      : Text(text, pos, Color::black)
    { }

    Text::Text(const std::string &text, const glm::vec2 &pos,
               const Color &col, float scale)
      : text(text), pos(pos), color(col), scale(scale) {
    }

    std::shared_ptr<TextRenderer> TextRenderer::create(const std::string &fontname, int size) {
      if (nullptr == shader)
        shader = createTextShader();

      // Load font face
      FT_Library ft;
      if (FT_Init_FreeType(&ft))
        std::cout << "Freetype Error: Could not initialize Library" << std::endl;

      FT_Face face;
      if (FT_New_Face(ft, fontname.c_str(), 0, &face))
        std::cout << "Freetype Error: Failed to load font " << fontname << std::endl;

      FT_Set_Pixel_Sizes(face, 0, size);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      // Load characters
      std::map<char, _internal::Character> chars;
      for (int c = 0; c < 128; ++c) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
          std::cout << "Freetype Error: Could not load face" << std::endl;
          continue;
        }

        // generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     face->glyph->bitmap.width,
                     face->glyph->bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        chars.insert({static_cast<char>(c), {
          texture,
          glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
          glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
          static_cast<uint32_t>(face->glyph->advance.x)
        }});
      }

      FT_Done_Face(face);
      FT_Done_FreeType(ft);

      // Create vao and vbo
      GLuint vao, vbo;
      glGenVertexArrays(1, &vao);
      glGenBuffers(1, &vbo);

      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);

      return std::shared_ptr<TextRenderer>(new TextRenderer(chars, vao, vbo));
    }

    TextRenderer::TextRenderer(const std::map<char, _internal::Character> &chars, GLuint vao, GLuint vbo)
      : _characters(chars), _vao(vao), _vbo(vbo)
    { }

    TextRenderer::~TextRenderer() {
      for (auto it = _characters.begin(); it != _characters.end(); it++)
        glDeleteTextures(1, &it->second.textureID);

      glDeleteVertexArrays(1, &_vao);
      glDeleteBuffers(1, &_vbo);
    }

    void TextRenderer::renderText(RenderContextPtr context, const Text &text) {
      int width, height;
      glfwGetWindowSize(context->window(), &width, &height);
      int x = static_cast<int>(text.pos.x * width);
      int y = static_cast<int>(text.pos.y * height);

      context->useShader(shader);
      context->enableBlending(BlendFunc::SrcAlpha,
                              BlendFunc::OneMinusSrcAlpha);

      shader->set("textColor", text.color);
      shader->set("projection", glm::ortho(0.0f, static_cast<float>(width),
                                       0.0f, static_cast<float>(height)));

      glActiveTexture(GL_TEXTURE0);
      glBindVertexArray(_vao);

      for (auto c = text.text.begin(); c != text.text.end(); c++) {
        _internal::Character ch = _characters[*c];

        float xpos = x + ch.bearing.x * text.scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * text.scale;

        float w = ch.size.x * text.scale;
        float h = ch.size.y * text.scale;

        float vertices[6][4] = {
          { xpos    , ypos + h, 0.0f, 0.0f },
          { xpos    , ypos    , 0.0f, 1.0f },
          { xpos + w, ypos    , 1.0f, 1.0f },

          { xpos    , ypos + h, 0.0f, 0.0f },
          { xpos + w, ypos    , 1.0f, 1.0f },
          { xpos + w, ypos + h, 1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advance >> 6) * text.scale;
      }

      glBindVertexArray(0);
      glBindTexture(GL_TEXTURE_2D, 0);
      context->disableBlending();
    }
  }
}
