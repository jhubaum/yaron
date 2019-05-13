#pragma once
#include <fwd.hpp>

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace yaron {
  namespace graphics {

    enum class DrawMode : GLenum {
      Points = GL_POINTS,
      LineStrip = GL_LINE_STRIP,
      LineLoop = GL_LINE_LOOP,
      Lines = GL_LINES,
      LineStrupAdjacency = GL_LINE_STRIP_ADJACENCY,
      LinesAdjacency = GL_LINES_ADJACENCY,
      TriangleStrip = GL_TRIANGLE_STRIP,
      TriangleFan = GL_TRIANGLE_FAN,
      Triangles = GL_TRIANGLES,
      TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
      TrianglesAdjacency = GL_TRIANGLES_ADJACENCY
    };

    class ShaderBuilder {
    public:
      ShaderBuilder();
      ~ShaderBuilder();

      ShaderBuilder& addVertexShader(const std::string& filename);
      ShaderBuilder& addFragmentShader(const std::string& filename);

      ShaderPtr build();

    private:
      GLuint _vertex;
      GLuint _fragment;
    };

    class Shader {
      friend class ShaderBuilder;
    public:
      ~Shader();

      template<typename T>
      void set(const std::string &name, const T&);

      void drawMode(DrawMode);
      DrawMode drawMode() const;
      GLuint handle() const;

    private:
      Shader();
      bool init(GLuint);

      GLuint _program;
      DrawMode _drawMode;
    };
  }
}
