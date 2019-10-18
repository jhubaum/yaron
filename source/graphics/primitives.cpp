#include <graphics/primitives.hpp>

#include <iostream>

#include <glm/gtc/constants.hpp>

#include <graphics/geometry.hpp>
#include <graphics/vertex.hpp>

void addNormals(std::vector<yaron::graphics::VertexPN> &vertices, unsigned short a, unsigned short b, unsigned short c) {
  glm::vec3 normal = glm::cross(vertices[b].pos - vertices[a].pos,
                                vertices[c].pos - vertices[a].pos);
  normal = glm::normalize(normal);
  vertices[a].normal = normal;
  vertices[b].normal = normal;
  vertices[c].normal = normal;
}

void addNormals(std::vector<yaron::graphics::VertexPN> &vertices, const std::vector<unsigned short> &indices) {
for(int i=0; i<indices.size()/3; ++i)
  addNormals(vertices, indices[3*i], indices[3*i+1], indices[3*i+2]);
}

namespace yaron {
  namespace graphics {
    GeometryPtr createPlane(const Rect &rect) {
      std::vector<VertexP> vertices(4);
      vertices[0] = { glm::vec3(rect.left, rect.bottom, 0.0f) };
      vertices[1] = { glm::vec3(rect.left, rect.top, 0.0f) };
      vertices[2] = { glm::vec3(rect.right, rect.top, 0.0f) };
      vertices[3] = { glm::vec3(rect.right, rect.bottom, 0.0f) };

      return Geometry<VertexP>::create(vertices, {0, 1, 2, 0, 2, 3});
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

    GeometryPtr createSphere(uint32_t lonCount, uint32_t latCount, float radius) {
      std::vector<VertexPN> vertices;
      std::vector<unsigned short> indices;

      // Add top vertices
      for (int i=0; i<lonCount; ++i) {
        vertices.push_back(glm::vec3(0.0f, radius, 0.0f));
      }

      // Add vertical lines
      for (int i=0; i<latCount; ++i) {
        float theta = glm::pi<float>() *
          static_cast<float>(i+1) / (latCount+1);

        for (int j=0; j<lonCount; ++j) {
          float phi = 2 * glm::pi<float>() * j / lonCount;
          vertices.push_back(glm::vec3(radius * sin(theta) * cos(phi),
                                       radius * cos(theta),
                                       radius * sin(theta) * sin(phi)));
        }
      }

      // Add bottom vertices
      for(int i=0; i<lonCount; ++i) {
        vertices.push_back(glm::vec3(0.0f, -radius, 0.0f));
      }

      // Add indices connecting the bottom and the top vertices with horizontal lines
      int bottomVertexStart = vertices.size() - lonCount;
      for (int i=0; i<lonCount; ++i) {
        indices.push_back(i);
        indices.push_back(lonCount + (i + 1) % lonCount);
        indices.push_back(lonCount + i);

        indices.push_back(bottomVertexStart + i);
        indices.push_back(bottomVertexStart - lonCount + i);
        indices.push_back(bottomVertexStart - lonCount + (i + 1) % lonCount);
      }

      // Add indices between vertical lines
      for (int i=1; i<latCount; ++i) {
        for (int j=0; j<lonCount; ++j) {
          indices.push_back(lonCount * i + j);
          indices.push_back(lonCount * i + (j + 1) % lonCount);
          indices.push_back(lonCount * (i+1) + j);

          indices.push_back(lonCount * i + (j+1) % lonCount);
          indices.push_back(lonCount * (i+1) + (j + 1) % lonCount);
          indices.push_back(lonCount * (i+1) + j);
        }
      }

      addNormals(vertices, indices);
      return Geometry<VertexPN>::create(vertices, indices);
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
  }
}
