#include <transform.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace yaron {
  Transform::Transform()
    : Transform({0.0f, 0.0f, 0.0f}, glm::quat(), {1.0f, 1.0f, 1.0f})
  {}

  Transform::Transform(const glm::vec3 &position)
    : Transform(position, glm::quat(), {1.0f, 1.0f, 1.0f})
  {}

  Transform::Transform(const glm::vec3 &position, const glm::quat &rotation)
    : Transform(position, rotation, {1.0f, 1.0f, 1.0f})
  {}

  Transform::Transform(const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale)
    : position(position), rotation(rotation), scale(scale)
  {}

  glm::mat4 Transform::calculateWorld() const {
    glm::mat4 world(1.0f);
    world = glm::translate(world, position);
    world *= glm::mat4_cast(rotation);
    world = glm::scale(world, scale);
    return world;
  }
}
