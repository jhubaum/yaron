#include <camera.hpp>

#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far)
  : _position(0.0f, 0.0f, 0.0f), _forward(0.0f, 0.0f, 1.0f),
    _up(0.0f, 1.0f, 0.0f), _fov(fov), _aspect(aspect),
    _near(near), _far(far)
{}

float PerspectiveCamera::fov() const { return _fov; }
float PerspectiveCamera::aspect() const { return _aspect; }
float PerspectiveCamera::near() const { return _near; }
float PerspectiveCamera::far() const {return _far; }

const glm::vec3& PerspectiveCamera::position() const { return _position; }
const glm::vec3& PerspectiveCamera::forward() const { return _forward; }
const glm::vec3& PerspectiveCamera::up() const { return _up; }

void PerspectiveCamera::fov(float value) { _fov = value; }
void PerspectiveCamera::aspect(float value) { _aspect = value; }
void PerspectiveCamera::near(float value) { _near = value; }
void PerspectiveCamera::far(float value) { _far = value; }

void PerspectiveCamera::position(const glm::vec3& value) { _position = value; }
void PerspectiveCamera::forward(const glm::vec3& value) { _forward = value; }
void PerspectiveCamera::up(const glm::vec3& value) { _up = value; }

glm::mat4 PerspectiveCamera::calculateViewProjectionMatrix() const {
  return glm::perspective(_fov, _aspect, _near, _far) *
    glm::lookAt(_position, _position+_forward, _up);
}

