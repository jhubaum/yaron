#pragma once
#include <fwd.hpp>

#include <glm/glm.hpp>

namespace yaron {
  namespace graphics {
    struct VertexP {
      glm::vec3 pos;

      VertexP()
        : pos(glm::vec3(0.0f, 0.0f, 0.0f))
      {}

      VertexP(const glm::vec3 pos)
        : pos(pos)
      {}
    };

    struct VertexPN {
      glm::vec3 pos;
      glm::vec3 normal;

      VertexPN()
        : pos(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f)
      {}

      VertexPN(const glm::vec3 &pos)
        : pos(pos), normal(0.0f, 0.0f, 0.0f)
      {}

      VertexPN(const glm::vec3 &pos, const glm::vec3 &normal)
        : pos(pos), normal(normal)
      {}
    };
  }
}
