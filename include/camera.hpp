#pragma once

#include <glm/glm.hpp>

class PerspectiveCamera {
public:
  PerspectiveCamera(float fov, float aspect, float near=0.1f, float far=100.0f);

  // Getter
  float fov() const;
  float aspect() const;
  float near() const;
  float far() const;

  const glm::vec3& position() const;
  const glm::vec3& forward() const;
  const glm::vec3& up() const;

  // Setter
  void fov(float value);
  void aspect(float value);
  void near(float value);
  void far(float value);

  void position(const glm::vec3& value);
  void forward(const glm::vec3& value);
  void up(const glm::vec3& value);

  glm::mat4 calculateViewProjectionMatrix() const;

private:
  glm::vec3 _position;
  glm::vec3 _forward;
  glm::vec3 _up;

  float _fov;
  float _aspect;
  float _near;
  float _far;
};
