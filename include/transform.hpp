#pragma once
#include <fwd.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace yaron {
  struct Transform {
    Transform();
    Transform(const glm::vec3 &position);
    Transform(const glm::vec3 &position, const glm::quat &rotation);
    Transform(const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale);

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    glm::mat4 calculateWorld() const;
    glm::mat4 calculateWorld(const glm::mat4 &parent) const;
  };
}
