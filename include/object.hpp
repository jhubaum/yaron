#pragma once
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Geometry;
typedef std::shared_ptr<Geometry> GeometryPtr;

class Geometry {
public:
  ~Geometry();

  static GeometryPtr create(const std::vector<glm::vec3> &vertices, const std::vector<unsigned short> &indices);

  uint32_t indexCount() const { return _indexCount; }
  GLuint vertexBuffer() const { return _vertexBuffer; }
  GLuint indexBuffer() const { return _indexBuffer; }

private:
  Geometry();
  bool init(const std::vector<glm::vec3> &vertices, const std::vector<unsigned short> &indices);

  GLuint _vertexArray;
  GLuint _vertexBuffer;
  GLuint _indexBuffer;

  uint32_t _indexCount;
};
