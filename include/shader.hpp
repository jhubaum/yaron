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

enum class DepthTest : GLenum {
  Never = GL_NEVER,
  Less = GL_LESS,
  Equal = GL_EQUAL,
  Lequal = GL_LEQUAL,
  Greater = GL_GREATER,
  NotEqual = GL_NOTEQUAL,
  Gequal = GL_GEQUAL,
  Always = GL_ALWAYS
};

enum class CullFace {
  None  = 0,
  Front = 1 << 0,
  Back  = 1 << 1
};

CullFace operator &(CullFace a, CullFace b);
CullFace operator |(CullFace a, CullFace b);

enum class BlendFunc : GLenum {
  Zero = GL_ZERO,
  One = GL_ONE,
  SrcColor = GL_SRC_COLOR,
  OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
  DstColor = GL_DST_COLOR,
  OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,
  SrcAlpha = GL_SRC_ALPHA,
  OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
  DstAlpha = GL_DST_ALPHA,
  OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,
  ConstantColor = GL_CONSTANT_COLOR,
  OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
  ConstantAlpha = GL_CONSTANT_ALPHA,
  OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
  SrcAlphaSaturate = GL_SRC_ALPHA_SATURATE,
  Src1Color = GL_SRC1_COLOR,
  OneMinusSrc1Color = GL_ONE_MINUS_SRC1_COLOR,
  Src1Alpha = GL_SRC1_ALPHA,
  OneMinusSrc1Alpha = GL_ONE_MINUS_SRC1_ALPHA
};

enum class PolygonMode : GLenum {
  Point = GL_POINT,
  Line = GL_LINE,
  Fill = GL_FILL
};

class Shader {
  friend class ShaderBuilder;
public:
  ~Shader();

  void setActive();
  void setViewProjection(const glm::mat4 &value);
  void setWorld(const glm::mat4 &value);

  void enableBlending(BlendFunc sfactor=BlendFunc::One, BlendFunc dfactor=BlendFunc::Zero);
  void disableBlending();


  void enableDepthTest(DepthTest);
  void disableDepthTest();

  void setCulling(CullFace);
  void setPolygonMode(PolygonMode);

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
