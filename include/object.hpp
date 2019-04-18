#pragma once
#include <vector>

#include <glm/vec3.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Object {
public:
  Object();
  ~Object();

  bool init(const std::vector<glm::vec3> &vertices, const std::vector<unsigned short> &indices);
  void deinit();

  uint32_t indexCount() const { return _indexCount; }
  GLuint vertexBuffer() const { return _vertexBuffer; }
  GLuint indexBuffer() const { return _indexBuffer; }
  
private:
  GLuint _vertexArray;
  GLuint _vertexBuffer;
  GLuint _indexBuffer;

  uint32_t _indexCount;
};
