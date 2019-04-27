#pragma once

#include <string>
#include <memory>

#include <GL/glew.h>
#include <glm/fwd.hpp>

#include <color.hpp>

class Shader;
typedef std::shared_ptr<Shader> ShaderPtr;

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

class Shader {
  friend class ShaderBuilder;
public:
  ~Shader();

  void setActive();
  void setViewProjection(const glm::mat4 &value);
  void setWorld(const glm::mat4 &value);

  void drawMode(DrawMode value) { _drawMode = value; }
  DrawMode drawMode() const { return _drawMode; }

  template<typename T>
  void set(const std::string &name, const T&);

private:
  Shader();
  bool init(GLuint);

  GLuint _program;
  GLuint _vpHandle;
  GLuint _worldHandle;
  DrawMode _drawMode;
};
