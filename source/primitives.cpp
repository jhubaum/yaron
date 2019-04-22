#include <primitives.hpp>

#include <vector>
#include <glm/glm.hpp>

#include <iostream>

GeometryPtr createCircle(uint32_t vertexCount, float radius) {
  std::vector<glm::vec3> vertices(vertexCount);
  for (int i=0; i<vertexCount; ++i) {
    float angle = 2 * glm::pi<float>() * i / vertexCount;
    vertices[i] = {radius * cos(angle), radius * sin(angle), 0.0f};
  }

  std::vector<unsigned short> indices;
  for (int i=0; i<vertexCount-2; ++i) {
    indices.push_back(0);
    indices.push_back(i + 1);
    indices.push_back(i + 2);
  }

  return Geometry::create(vertices, indices);
}
