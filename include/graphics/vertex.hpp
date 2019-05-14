#pragma once
#include <fwd.hpp>

#include <glm/glm.hpp>

namespace yaron {
  namespace graphics {
    /// A vertex type containing a position vector.
    struct VertexP {
      glm::vec3 pos; /*!< the position vector */

      /// Create a new VertexP
      /**
       * the position will be set to the zero vector
       */
      VertexP()
        : pos(glm::vec3(0.0f, 0.0f, 0.0f))
      {}

      /// Create a new VertexP
      /**
       * \param pos: the position vector
       */
      VertexP(const glm::vec3 pos)
        : pos(pos)
      {}
    };

    /// A vertex type containing a position vector and a face normal
    struct VertexPN {
      glm::vec3 pos; /*!< the position vector */
      glm::vec3 normal; /*!< the face normal */

      /// Create a new VertexPN
      /**
       * Both the position vector and the face normal will be set to the zero vector
       */
      VertexPN()
        : pos(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f)
      {}

      /// Create a new VertexPN
      /**
       * The face normal will be set to the zero vector
       * \param pos: the position vector
       */
      VertexPN(const glm::vec3 &pos)
        : pos(pos), normal(0.0f, 0.0f, 0.0f)
      {}

      /// Create a new VertexPN
      /**
       * \param pos: the position vector
       * \param normal: the face normal
       */
      VertexPN(const glm::vec3 &pos, const glm::vec3 &normal)
        : pos(pos), normal(normal)
      {}
    };
  }
}
