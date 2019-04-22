#pragma once

#include <glm/glm.hpp>
#include <transform.hpp>

class Camera {
public:
  Camera(float near, float far);
  virtual ~Camera() = 0;

  virtual glm::mat4 calculateViewProjectionMatrix() const = 0;

  float near() const;
  float far() const;

  void near(float value);
  void far(float value);

private:
  float _near;
  float _far;
};

class PerspectiveCamera : public Camera {
public:
  PerspectiveCamera(float fov, float aspect, float near=0.1f, float far=100.0f);

  float fov() const;
  float aspect() const;

  Transform& transform();

  void fov(float value);
  void aspect(float value);

  void position(const glm::vec3& value);
  void forward(const glm::vec3& value);
  void up(const glm::vec3& value);

  glm::mat4 calculateViewProjectionMatrix() const final override;

private:
  float _fov;
  float _aspect;

  Transform _transform;
};
