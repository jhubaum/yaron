#include <camera.hpp>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float near, float far)
  : _near(near), _far(far), _transform(Transform())
{}

Camera::~Camera()
{}

glm::mat4 Camera::viewProjectionMatrix() const {
  auto rot = glm::mat3_cast(_transform.rotation);

  return projectionMatrix() *
    glm::lookAt(_transform.position,
                _transform.position + rot * glm::vec3(0.0f, 0.0f, 1.0f),
                rot * glm::vec3(0.0f, 1.0f, 0.0f));
}

float Camera::near() const { return _near; }
float Camera::far() const { return _far; }

void Camera::near(float value) { _near = value; }
void Camera::far(float value) { _far = value; }

Transform& Camera::transform() { return _transform; }


PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
  : Camera(near, far), _fov(fov), _aspect(aspect)
{}

float PerspectiveCamera::fov() const { return _fov; }
float PerspectiveCamera::aspect() const { return _aspect; }

void PerspectiveCamera::fov(float value) { _fov = value; }
void PerspectiveCamera::aspect(float value) { _aspect = value; }

glm::mat4 PerspectiveCamera::projectionMatrix() const {
  return glm::perspective(_fov, _aspect, near(), far());
}

OrthographicCamera::OrthographicCamera(float left, float right,
                                       float bottom, float top,
                                       float near, float far)
  : Camera(near, far), _left(left), _right(right),
    _bottom(bottom), _top(top)
{}

float OrthographicCamera::left() const { return _left; }
float OrthographicCamera::right() const { return _right; }
float OrthographicCamera::bottom() const { return _bottom; }
float OrthographicCamera::top() const { return _top; }

void OrthographicCamera::left(float value) { _left = value; }
void OrthographicCamera::right(float value) { _right = value; }
void OrthographicCamera::bottom(float value) { _bottom = value; }
void OrthographicCamera::top(float value) { _top = value; }

glm::mat4 OrthographicCamera::projectionMatrix() const {
  return glm::ortho(_left, _right, _bottom, _top, near(), far());
}
