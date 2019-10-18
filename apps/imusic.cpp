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

#include <random.hpp>

using namespace yaron;
using namespace yaron::graphics;

class InteractiveMusicApp : public App {
public:
  struct Particle {
    float distance;
    float angle;
    Color color;

    static constexpr float trail = 5;
    static constexpr float size = 0.05f;
    static GeometryPtr geometry;

    void render(ShaderPtr shader, RenderContextPtr context) {
      for (int i=0; i<trail; ++i) {
        shader->set<Color>("mainColor",
                           lerp(color,
                                Color::white,
                                static_cast<float>(i) / trail));

        float a = angle - 4.0f * glm::pi<float>() * i * size / distance;
        auto world = glm::translate(glm::mat4(1.0f),
                                    glm::vec3(distance * cos(a),
                                              distance * sin(a),
                                              0.0f));

        context->renderGeometry(geometry, world);
      }

    };
  };

protected:
  bool vOnInit(const std::vector<std::string>&) final override;

  void vOnUpdate(float dt) final override;
  void vOnRender() final override;

private:
  ShaderPtr _shader;
  std::shared_ptr<PerspectiveCamera> _camera;
  Random _randomizer;

  std::vector<InteractiveMusicApp::Particle> _particles;
  float _curCenterDistance = Particle::size;
  float _rotationSpeed = 1.0f;
};

App *yaron::allocateApplication() {
  return new InteractiveMusicApp();
}

GeometryPtr InteractiveMusicApp::Particle::geometry = nullptr;


bool InteractiveMusicApp::vOnInit(const std::vector<std::string> &args) {
  Particle::geometry = createCircle(16, Particle::size);

  _shader = ShaderBuilder()
    .addVertexShader(resourcePath("shaders/simple.vertexshader"))
    .addFragmentShader(resourcePath("shaders/simple.fragmentshader"))
    .build();

  // Initialize Camera
  _camera = std::make_shared<PerspectiveCamera>(glm::radians(45.0f), renderContext()->aspectRatio());
  auto t = _camera->transform().lock();
  t->position = glm::vec3(0.0f, 0.0f, -5.0f);


  renderContext()->enableDepthTest(DepthTest::Less);
  renderContext()->setCulling(CullFace::Back);
  renderContext()->clearColor(Color::green);
  renderContext()->setCamera(_camera);

  return true;
}

void InteractiveMusicApp::vOnUpdate(float dt) {
  if (input().getKeyPressed(GLFW_KEY_SPACE)) {
    _particles.push_back({ _curCenterDistance, 0.0f,
                           _randomizer.rand<Color>() });
    _curCenterDistance += 2 * Particle::size;
  }

  for (int i=0; i<_particles.size(); ++i)
    _particles[i].angle += dt * _rotationSpeed;
}

void InteractiveMusicApp::vOnRender() {
  renderContext()->useShader(_shader);
  for (int i=0; i<_particles.size(); ++i)
    _particles[i].render(_shader, renderContext());
}
