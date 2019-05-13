#pragma once
#include <fwd.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// This include makes calling Geometry::create without including
// graphics/vertex.hpp each time possible
#include <graphics/vertex.hpp>

namespace yaron {
  namespace graphics {
    class Geometry_B {
    public:
      virtual ~Geometry_B();

      uint32_t indexCount() const;
      GLuint vertexBuffer() const;
      GLuint indexBuffer() const;
      GLuint vertexArray() const;

      virtual void vEnableVertexAttributes() = 0;
      virtual void vDisableVertexAttributes() = 0;

    protected:
      Geometry_B(GLuint vertexArrayObject, GLuint vertexBuffer,
                 GLuint indexBuffer, uint32_t indexCount);

    private:
      GLuint _vertexArray;
      GLuint _vertexBuffer;
      GLuint _indexBuffer;

      uint32_t _indexCount;
    };

    template<typename TVertex>
    class Geometry : Geometry_B {
    public:
      static GeometryPtr create(const std::vector<TVertex> &vertices, const std::vector<unsigned short> &indices);

      void vEnableVertexAttributes() final override;
      void vDisableVertexAttributes() final override;
    private:
      Geometry(GLuint vao, GLuint vb, GLuint ib, uint32_t ic);
    };

    template<typename TVertex>
    void enableVertexAttributes(GLuint vertexBuffer, GLuint indexBuffer);

    template<typename TVertex>
    void disableVertexAttributes();

    struct GeometryIn {
      const void *vertices;
      const void *indices;
      uint32_t vertexSize;
      uint32_t vertexCount;
      uint32_t indexCount;
    };

    struct GeometryOut {
      GLuint vertexArrayObject;
      GLuint vertexBuffer;
      GLuint indexBuffer;
    };

    GeometryOut createGeometry(const GeometryIn&);

#include "geometry.inl"
  }
}
