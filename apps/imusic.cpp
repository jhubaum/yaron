#include <iostream>
#include <vector>

#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <app.hpp>
#include <transform.hpp>
#include <camera.hpp>
#include <graphics/context.hpp>
#include <graphics/shader.hpp>
#include <graphics/primitives.hpp>

using namespace yaron;
using namespace yaron::graphics;

class InteractiveMusicApp : public App {
public:
  struct Particle {
    float distance;
    float angle;
  };
  InteractiveMusicApp(float particleSize)
    : _camera(nullptr), _particleSize(particleSize)
  { }

protected:
  bool vOnInit(const std::vector<std::string>&) final override;

  void vOnUpdate(float dt) final override;
  void vOnRender() final override;

private:
  ShaderPtr _shader;
  std::shared_ptr<PerspectiveCamera> _camera;
  GeometryPtr _geometry;

  std::vector<InteractiveMusicApp::Particle> _particles;
  float _particleSize;
  float _curCenterDistance = 0.1f;
  float _rotationSpeed = 1.0f;
};

App *yaron::allocateApplication() {
  return new InteractiveMusicApp(0.05f);
}

bool InteractiveMusicApp::vOnInit(const std::vector<std::string> &args) {
  _shader = ShaderBuilder()
    .addVertexShader(resourcePath("shaders/simple.vertexshader"))
    .addFragmentShader(resourcePath("shaders/simple.fragmentshader"))
    .build();

  // Initialize Camera
  _camera = std::make_shared<PerspectiveCamera>(glm::radians(45.0f), renderContext()->aspectRatio());
  auto t = _camera->transform().lock();
  t->position = glm::vec3(0.0f, 0.0f, -5.0f);

  _geometry = createCircle(16, _particleSize);

  renderContext()->enableDepthTest(DepthTest::Less);
  renderContext()->setCulling(CullFace::Back);
  renderContext()->clearColor(Color::green);
  renderContext()->setCamera(_camera);

  return true;
}

void InteractiveMusicApp::vOnUpdate(float dt) {
  if (input().getKeyPressed(GLFW_KEY_SPACE)) {
    _particles.push_back({ _curCenterDistance, 0.0f});
    _curCenterDistance += 2 * _particleSize;
  }

  for (int i=0; i<_particles.size(); ++i)
    _particles[i].angle += dt * _rotationSpeed;
}

void InteractiveMusicApp::vOnRender() {
  renderContext()->useShader(_shader);

  _shader->set<Color>("mainColor", Color(0.3f, 0.3f, 0.3f));

  for (int i=0; i<_particles.size(); ++i) {
    const Particle &p = _particles[i];
    auto world = glm::translate(glm::mat4(1.0f),
                                glm::vec3(p.distance * cos(p.angle),
                                          p.distance * sin(p.angle),
                                          0.0f));
    renderContext()->renderGeometry(_geometry, world);
  }
}
