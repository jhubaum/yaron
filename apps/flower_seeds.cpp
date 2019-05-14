#include <iostream>
#include <vector>

#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <app.hpp>
#include <transform.hpp>
#include <light.hpp>
#include <controls.hpp>
#include <camera.hpp>
#include <graphics/context.hpp>
#include <graphics/shader.hpp>
#include <graphics/primitives.hpp>
#include <graphics/text.hpp>

using namespace yaron;
using namespace yaron::graphics;

class FlowerApp : public App {
public:
  FlowerApp(uint32_t seedCount, float radius)
    : _camera(nullptr), _seeds(seedCount), _radius(radius),
      _currentRotation(0.0f), _light(Color::white)
  { }

protected:
  bool vOnInit(const std::vector<std::string>&) final override;

  void vOnUpdate(float dt) final override;
  void vOnRender() final override;

private:
  void updateRotation(float value);

  ShaderPtr _shader;
  std::shared_ptr<PerspectiveCamera> _camera;
  std::shared_ptr<TextRenderer> _textRenderer;

  std::vector<glm::vec3> _seeds;
  GeometryPtr _geometry;
  float _radius;
  float _currentRotation;
  Controller _controller;

  PointLight _light;
};

App *yaron::allocateApplication() {
  return new FlowerApp(1000, 0.02f);
}

bool FlowerApp::vOnInit(const std::vector<std::string> &args) {
  _shader = ShaderBuilder()
    .addVertexShader(resourcePath("shaders/light.vertexshader"))
    .addFragmentShader(resourcePath("shaders/light.fragmentshader"))
    .build();

  // Initialize light
  _light.transform->position = glm::vec3(-5.0f, 2.0f, 5.0f);
  _light.transform->scale *= 0.1f;

  // Initialize Camera and controller
  _camera = std::make_shared<PerspectiveCamera>(glm::radians(45.0f), renderContext()->aspectRatio());
  auto t = _camera->transform().lock();
  t->position = glm::vec3(0.0f, 0.0f, -5.0f);//glm::vec3(-5.0f, 5.0f, -5.0f);
  //t->rotation = glm::quatLookAt(glm::normalize(t->position),
  //                              glm::vec3(0.0f, 1.0f, 0.0f));

  _controller = Controller(_camera->transform(),
                           renderContext()->window());

  _geometry = createSphere(8, 8, _radius);
  _textRenderer = TextRenderer::create("resources/fonts/TIMESR.ttf", 32);

  renderContext()->enableDepthTest(DepthTest::Less);
  renderContext()->setCulling(CullFace::Back);
  renderContext()->clearColor(Color::green);
  renderContext()->setCamera(_camera);

  return true;
}

void FlowerApp::vOnUpdate(float dt) {
  _currentRotation += 0.001f * dt;
  updateRotation(_currentRotation);

  _controller.update(dt);
}

void FlowerApp::vOnRender() {
  renderContext()->useShader(_shader);

  _shader->set<Color>("diffuseColor", Color(0.3f, 0.3f, 0.3f));
  _shader->set<glm::vec3>("cameraPos", _camera->transform().lock()->position);
  _shader->set("light", _light);

  for(int i=0; i<_seeds.size(); ++i) {
    auto world = glm::translate(glm::mat4(1.0f), _seeds[i]);
    renderContext()->renderGeometry(_geometry, world);
  }

  Text text("This is a test", glm::vec2(0.0f, 0.0f), Color::purple);
  _textRenderer->renderText(renderContext(), text);
}

void FlowerApp::updateRotation(float value) {
  float angle = 2 * glm::pi<float>() * value;

  for (int i=0; i<_seeds.size(); ++i) {
    float rad = 0.5f * i * _radius;
    _seeds[i] = /*glm::rotate(*/glm::vec3(rad * cos(i * angle), rad * sin(i * angle), 0.0f);/*,
                            i * angle,
                            glm::vec3(1.0f, 1.0f, 0.0f));*/
  }
}
