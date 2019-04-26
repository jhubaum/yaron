#include <primitives.hpp>

#include <glm/gtc/constants.hpp>

#include <vector>
#include <vertex.hpp>

#include <iostream>

GeometryPtr createCircle(uint32_t vertexCount, float radius) {
  std::vector<VertexP> vertices(vertexCount);
  for (int i=0; i<vertexCount; ++i) {
    float angle = 2 * glm::pi<float>() * i / vertexCount;
    vertices[i] = { glm::vec3(radius * cos(angle),
                              radius * sin(angle), 0.0f) };
  }

  std::vector<unsigned short> indices;
  for (int i=0; i<vertexCount-2; ++i) {
    indices.push_back(0);
    indices.push_back(i + 2);
    indices.push_back(i + 1);
  }

  return Geometry<VertexP>::create(vertices, indices);
}

float calcAngleFromRot(float rot) {
  return 2.0f * glm::pi<float>() * rot;
}

float calcAngleFromRot(int i, int size) {
  return calcAngleFromRot(static_cast<float>(i) / size);
}

GeometryPtr createSphere(uint32_t lonCount, uint32_t latCount, float radius) {
  // Lon: vertical lines
  // Lat: horizontal lines

  std::vector<VertexP> vertices = { glm::vec3(0.0f, radius, 0.0f),
                                      glm::vec3(0.0f, -radius, 0.0f) };

  latCount += 1;
  for (int i=1; i<latCount; ++i) {
    for (int j=0; j<lonCount; ++j) {
      float angle = 2 * glm::pi<float>() * j / lonCount;
      auto vertex = glm::vec3(radius * cos(angle),
                              radius - 2.0f * (static_cast<float>(i) / latCount)*radius,
                              radius * sin(angle));
      vertices.push_back({vertex});
    }
  }


  std::vector<unsigned short> indices =
    {
     0, 2, 3,
     0, 3, 4,
     0, 4, 5,
     1, 2, 3,
     1, 3, 4,
     1, 4, 5
    };


  return Geometry<VertexP>::create(vertices, indices);

  /*
  for (int i=0; i<degree; ++i) {
    float a1 = 2.0f * glm::pi<float>() * static_cast<float>(i) / degree;
    for (int j=0; j<degree; ++j) {
      float a2 = 2.0f * glm::pi<float>() * static_cast<float>(j) / degree;
      vertices.push_back(glm::vec3(radius * sin(a1) * cos(a2),
                                   radius * sin(a1) * cos(a2),
                                   radius * cos(a1)));
    }
  }

  float angle = calcAngleFromRot(0.3333333f);
  vertices.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
  vertices.push_back(glm::vec3(cos(angle), sin(angle), 0.0f));
  angle = calcAngleFromRot(0.6666666f);
  vertices.push_back(glm::vec3(cos(angle), sin(angle), 0.0f));

    {
     0, 2, 1,
     //0, 3, 1,
     //1, 3, 2,
     //0, 3, 2
  };

  */
}
