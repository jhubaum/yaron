#pragma once

#include <string>
#include <memory>

#include <GL/glew.h>
#include <glm/fwd.hpp>

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

class Shader {
  friend class ShaderBuilder;
public:
  ~Shader();

  void setActive();
  void setMVP(const glm::mat4 &value);

private:
  Shader();
  bool init(GLuint);

  GLuint _program;
  GLuint _mvpHandle;
};
