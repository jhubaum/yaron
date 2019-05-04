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

struct Object {
  GeometryPtr geometry;
  Transform transform;

  Object(GeometryPtr geometry, Transform transform)
    : geometry(nullptr), transform(transform)
  {}

  Object(GeometryPtr geometry)
    : Object(geometry, Transform())
  {}

  Object()
    : Object(nullptr, Transform())
  {}
};

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
  std::shared_ptr<Transform> _transform;

  std::vector<Object> _seeds;
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

  renderContext()->clearColor(Color::green);

  _camera = std::make_shared<PerspectiveCamera>(glm::radians(45.0f), renderContext()->aspectRatio());
  auto t = _camera->transform().lock();
  t->position = glm::vec3(-5.0f, 5.0f, -5.0f);
  t->rotation = glm::quatLookAt(glm::normalize(t->position),
                                glm::vec3(0.0f, 1.0f, 0.0f));

  _light.transform->position = glm::vec3(-5.0f, 2.0f, 5.0f);

  _transform = std::make_shared<Transform>();
  _controller = Controller(_transform,
                           renderContext()->window());

  _light.transform->scale *= 0.1f;

  auto geometry = createCircle(8, _radius);

  for(int i=0; i<_seeds.size(); ++i)
    _seeds[i].geometry = geometry;

  return true;
}

void FlowerApp::vOnDeinit() {
  _shader = nullptr;
}

void FlowerApp::vOnUpdate(float dt) {
  _currentRotation += 0.01f * dt;
  updateRotation(_currentRotation);

  _controller.update(dt);
}

void FlowerApp::vOnRender() {
  renderContext()->beginFrame(_camera);
  renderContext()->useShader(_shader);

  _shader->set<Color>("diffuseColor", Color(0.3f, 0.3f, 0.3f));
  _shader->set<glm::vec3>("cameraPos", _camera->transform().lock()->position);
  _shader->set("light", _light);

  static auto geo = createSphere();
  renderContext()->renderGeometry(geo, _transform->calculateWorld());

  renderContext()->endFrame();
  return;

  for(int i=0; i<_seeds.size(); ++i)
    renderContext()->renderGeometry(_seeds[i].geometry, _seeds[i].transform);

  renderContext()->endFrame();
}

void FlowerApp::updateRotation(float value) {
  float angle = value * 2.0f * glm::pi<float>();
  for(int i=0; i<_seeds.size(); ++i) {
    float rad = 0.5f * i * _radius;
    _seeds[i].transform.position.x = rad * glm::cos(angle*i);
    _seeds[i].transform.position.y = rad * glm::sin(angle*i);
  }
}
