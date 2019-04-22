#include <camera.hpp>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float near, float far)
  : _near(near), _far(far)
{}

Camera::~Camera()
{}

float Camera::near() const { return _near; }
float Camera::far() const { return _far; }

void Camera::near(float value) { _near = value; }
void Camera::far(float value) { _far = value; }


PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
  : Camera(near, far), _fov(fov), _aspect(aspect), _transform(Transform())
{}

float PerspectiveCamera::fov() const { return _fov; }
float PerspectiveCamera::aspect() const { return _aspect; }

void PerspectiveCamera::fov(float value) { _fov = value; }
void PerspectiveCamera::aspect(float value) { _aspect = value; }


Transform& PerspectiveCamera::transform() { return _transform; }

glm::mat4 PerspectiveCamera::calculateViewProjectionMatrix() const {
  auto rot = glm::mat3_cast(_transform.rotation);

  return glm::perspective(_fov, _aspect, near(), far()) *
    glm::lookAt(_transform.position, glm::vec3(0.0f, 0.0f, 1.0f) * rot,
                glm::vec3(0.0f, 1.0f, 0.0f) * rot);
}

