#include <primitives.hpp>

#include <glm/gtc/constants.hpp>

#include <vector>
#include <vertex.hpp>

#include <iostream>

void addNormals(std::vector<VertexPN> &vertices, unsigned short a, unsigned short b, unsigned short c) {
  glm::vec3 normal = glm::cross(vertices[c].pos - vertices[a].pos,
                                vertices[b].pos - vertices[a].pos);
  normal = glm::normalize(normal);
  vertices[a].normal = normal;
  vertices[b].normal = normal;
  vertices[c].normal = normal;
}

void addNormals(std::vector<VertexPN> &vertices, const std::vector<unsigned short> &indices) {
for(int i=0; i<indices.size()/3; ++i)
  addNormals(vertices, indices[3*i], indices[3*i+1], indices[3*i+2]);
}

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

GeometryPtr createTriangle() {
  std::vector<VertexPN> vertices(3);
  for (int i=0; i<3; ++i) {
    float angle = calcAngleFromRot(i, 3);
    vertices[i].pos = glm::vec3(cos(angle), sin(angle), 0.0f);
  }

  std::vector<unsigned short> indices = {0, 2, 1};
  addNormals(vertices, 0, 2, 1);
  return Geometry<VertexPN>::create(vertices, indices);
};

GeometryPtr createSphere(uint32_t lonCount, uint32_t latCount, float radius) {
  // Lon: vertical lines
  // Lat: horizontal lines
  //return createTriangle();


  std::vector<VertexPN> vertices(2);
  vertices[0].pos = glm::vec3(0.0f, radius, 0.0f);
  vertices[0].pos = glm::vec3(0.0f, -radius, 0.0f);

  latCount += 1;
  for (int i=1; i<latCount; ++i) {
    for (int j=0; j<lonCount; ++j) {
      float angle = 2 * glm::pi<float>() * j / lonCount;
      VertexPN vertex;
      vertex.pos = glm::vec3(radius * cos(angle),
                             radius - 2.0f * (static_cast<float>(i) / latCount)*radius,
                             radius * sin(angle));
      vertices.push_back(vertex);
    }
  }

  //vertices[0].normal = glm::vec3(0.0f, radius, 0.0f);
  //vertices[0].normal = glm::vec3(0.0f, -radius, 0.0f);


  std::vector<unsigned short> indices =
    {
     0, 3, 2,
     0, 4, 3,
     0, 5, 4,
     1, 3, 2,
     1, 4, 3,
     1, 5, 4
    };

  addNormals(vertices, indices);

  return Geometry<VertexPN>::create(vertices, indices);

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

      {
     0, 2, 1,
     //0, 3, 1,
     //1, 3, 2,
     //0, 3, 2
  };

  */
}

GeometryPtr createCube() {
  std::vector<VertexPN> vertices = {
    glm::vec3(-0.5f,-0.5f, 0.5f),
    glm::vec3( 0.5f,-0.5f, 0.5f),
    glm::vec3( 0.5f,-0.5f,-0.5f),
    glm::vec3(-0.5f,-0.5f,-0.5f),

    glm::vec3(-0.5f,-0.5f,-0.5f),
    glm::vec3( 0.5f,-0.5f,-0.5f),
    glm::vec3( 0.5f, 0.5f,-0.5f),
    glm::vec3(-0.5f, 0.5f,-0.5f),

    glm::vec3(-0.5f,-0.5f,-0.5f),
    glm::vec3(-0.5f, 0.5f,-0.5f),
    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3(-0.5f,-0.5f, 0.5f),

    glm::vec3(-0.5f, 0.5f,-0.5f),
    glm::vec3( 0.5f, 0.5f,-0.5f),
    glm::vec3( 0.5f, 0.5f, 0.5f),
    glm::vec3(-0.5f, 0.5f, 0.5f),

    glm::vec3(-0.5f, 0.5f, 0.5f),
    glm::vec3( 0.5f, 0.5f, 0.5f),
    glm::vec3( 0.5f,-0.5f, 0.5f),
    glm::vec3(-0.5f,-0.5f, 0.5f),

    glm::vec3( 0.5f,-0.5f, 0.5f),
    glm::vec3( 0.5f, 0.5f, 0.5f),
    glm::vec3( 0.5f, 0.5f,-0.5f),
    glm::vec3( 0.5f,-0.5f,-0.5f),
  };

  std::vector<unsigned short> indices;
  for(int i=0; i<6; ++i) {
    indices.push_back(4*i);
    indices.push_back(4*i + 2);
    indices.push_back(4*i + 1);
    indices.push_back(4*i);
    indices.push_back(4*i + 3);
    indices.push_back(4*i + 2);
  }
  addNormals(vertices, indices);

  return Geometry<VertexPN>::create(vertices, indices);
}
