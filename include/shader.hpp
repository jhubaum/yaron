#pragma once

#include <string>
#include <GL/glew.h>


class ShaderBuilder {
public:
  ShaderBuilder();
  ~ShaderBuilder();

  ShaderBuilder& addVertexShader(const std::string& filename);
  ShaderBuilder& addFragmentShader(const std::string& filename);

  GLuint build();

private:
  GLuint _vertex;
  GLuint _fragment;
};
