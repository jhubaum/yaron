#include <graphics/geometry.hpp>

namespace yaron {
  namespace graphics {
    Geometry_B::Geometry_B(GLuint vertexArrayObject, GLuint vertexBuffer,
                           GLuint indexBuffer, uint32_t indexCount)
      : _vertexArray(vertexArrayObject), _vertexBuffer(vertexBuffer),
        _indexBuffer(indexBuffer), _indexCount(indexCount)
    {}

    Geometry_B::~Geometry_B() {
      glDeleteBuffers(1, &_indexBuffer);
      glDeleteBuffers(1, &_vertexBuffer);
      glDeleteVertexArrays(1, &_vertexArray);
    }

    uint32_t Geometry_B::indexCount() const { return _indexCount; }
    GLuint Geometry_B::vertexBuffer() const { return _vertexBuffer; }
    GLuint Geometry_B::indexBuffer() const { return _indexBuffer; }
    GLuint Geometry_B::vertexArray() const { return _vertexArray; }

    GeometryOut createGeometry(const GeometryIn &in) {
      GeometryOut o;

      glGenVertexArrays(1, &o.vertexArrayObject);
      glBindVertexArray(o.vertexArrayObject);

      glGenBuffers(1, &o.vertexBuffer);
      glBindBuffer(GL_ARRAY_BUFFER, o.vertexBuffer);
      glBufferData(GL_ARRAY_BUFFER, in.vertexSize * in.vertexCount,
                   in.vertices, GL_STATIC_DRAW);

      glGenBuffers(1, &o.indexBuffer);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o.indexBuffer);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, in.indexCount * sizeof(unsigned short), in.indices , GL_STATIC_DRAW);

      return o;
    }
  }
}
