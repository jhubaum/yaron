#pragma once

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct VertexP {
  glm::vec3 pos;

  VertexP()
    : pos(glm::vec3(0.0f, 0.0f, 0.0f))
  {}

  VertexP(const glm::vec3 pos)
    : pos(pos)
  {}
};

struct VertexPCN {
  glm::vec3 pos;
  glm::vec3 col;
  glm::vec3 normal;
};

template<typename TVertex>
void enableVertexAttributes(GLuint vertexBuffer, GLuint indexBuffer);

template<typename TVertex>
void disableVertexAttributes();
