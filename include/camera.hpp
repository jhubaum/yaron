#pragma once

#include <glm/glm.hpp>
#include <transform.hpp>

#include <memory>

class Camera {
public:
  Camera(float near, float far);
  virtual ~Camera() = 0;

  glm::mat4 viewProjectionMatrix() const;

  float near() const;
  float far() const;

  void near(float value);
  void far(float value);

  std::weak_ptr<Transform> transform();

protected:
  virtual glm::mat4 projectionMatrix() const = 0;

private:
  float _near;
  float _far;

  std::shared_ptr<Transform> _transform;
};

class PerspectiveCamera : public Camera {
public:
  PerspectiveCamera(float fov, float aspect, float near=0.1f, float far=100.0f);

  float fov() const;
  float aspect() const;

  void fov(float value);
  void aspect(float value);

protected:
  glm::mat4 projectionMatrix() const final override;

private:
  float _fov;
  float _aspect;
};

class OrthographicCamera : public Camera {
public:
  OrthographicCamera(float left, float right, float bottom, float top, float near=0.1f, float far=100.0f);

  float left() const;
  float right() const;
  float bottom() const;
  float top() const;

  void left(float value);
  void right(float value);
  void bottom(float value);
  void top(float value);

protected:
  glm::mat4 projectionMatrix() const final override;

private:
  float _left;
  float _right;
  float _bottom;
  float _top;
};
