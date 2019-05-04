#include <app.hpp>
#include <context.hpp>
#include <shader.hpp>
#include <primitives.hpp>
#include <transform.hpp>

#include <light.hpp>


#include <iostream>

#include <vector>

#include <glm/gtc/constants.hpp>

#include <controls.hpp>

class FlowerApp : public App {
public:
  FlowerApp(uint32_t seedCount, float radius)
    : _camera(nullptr), _seeds(seedCount), _radius(radius),
      _currentRotation(0.0f), _light(Color::white)
  { }

protected:
  bool vOnInit(char *argv[], int argc) final override;
  void vOnDeinit() final override;

  void vOnUpdate(float dt) final override;
  void vOnRender() final override;

private:
  void updateRotation(float value);

  ShaderPtr _shader;
  std::shared_ptr<PerspectiveCamera> _camera;

  std::vector<glm::vec3> _seeds;
  GeometryPtr _geometry;
  float _radius;
  float _currentRotation;
  Controller _controller;

  PointLight _light;
};

App *allocateApplication() {
  return new FlowerApp(1000, 0.02f);
}

bool FlowerApp::vOnInit(char *argv[], int argc) {
  _shader = ShaderBuilder()
    .addVertexShader("resources/light.vertexshader")
    .addFragmentShader("resources/light.fragmentshader")
    .build();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

  renderContext()->clearColor(Color::green);

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

  updateRotation(0.25f);

  return true;
}

void FlowerApp::vOnDeinit() {
  _shader = nullptr;
}

void FlowerApp::vOnUpdate(float dt) {
  //_currentRotation += 0.001f * dt;
  //updateRotation(_currentRotation);

  _controller.update(dt);
}

void FlowerApp::vOnRender() {
  renderContext()->beginFrame(_camera);
  renderContext()->useShader(_shader);

  _shader->set<Color>("diffuseColor", Color(0.3f, 0.3f, 0.3f));
  _shader->set<glm::vec3>("cameraPos", _camera->transform().lock()->position);
  _shader->set("light", _light);

  for(int i=0; i<_seeds.size(); ++i) {
    auto world = glm::translate(glm::mat4(1.0f), _seeds[i]);
    renderContext()->renderGeometry(_geometry, world);
  }

  renderContext()->endFrame();
}

void FlowerApp::updateRotation(float value) {
  float angle = value * 2.0f * glm::pi<float>();
  for(int i=0; i<_seeds.size(); ++i) {
    float rad = 0.5f * i * _radius;
    _seeds[i].x = rad * glm::cos(angle*i);
    _seeds[i].y = rad * glm::sin(angle*i);
  }
}
