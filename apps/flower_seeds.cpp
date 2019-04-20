#include <app.hpp>
#include <context.hpp>
#include <shader.hpp>
#include <primitives.hpp>
#include <transform.hpp>

#include <vector>

#include <glm/gtc/constants.hpp>

class FlowerApp : public App {
public:
  FlowerApp(uint32_t seedCount, float radius)
    : _seeds(seedCount), _radius(radius), _currentRotation(0.0f)
  { }

protected:
  bool vOnInit(char *argv[], int argc) final override;
  void vOnDeinit() final override;

  void vOnUpdate(float dt) final override;
  void vOnRender(RenderContext &context) final override;

private:
  void updateRotation(float value);

  ShaderPtr _shader;
  std::vector<Object> _seeds;
  float _radius;
  float _currentRotation;
};

App *allocateApplication() {
  return new FlowerApp(1000, 0.02f);
}

bool FlowerApp::vOnInit(char *argv[], int argc) {
  _shader = ShaderBuilder()
    .addVertexShader("resources/simple.vertexshader")
    .addFragmentShader("resources/simple.fragmentshader")
    .build();

  auto circleGeometry = createCircle(8, _radius);

  for(int i=0; i<_seeds.size(); ++i)
    _seeds[i].geometry = circleGeometry;

  return true;
}

void FlowerApp::vOnDeinit() {
  _shader = nullptr;
}

void FlowerApp::vOnUpdate(float dt) {
  _currentRotation += 0.01f * dt;
  updateRotation(_currentRotation);
}

void FlowerApp::vOnRender(RenderContext &context) {
  context.useShader(_shader);

  for(int i=0; i<_seeds.size(); ++i)
    context.renderGeometry(_seeds[i].geometry, _seeds[i].transform.calculateWorld());
}

void FlowerApp::updateRotation(float value) {
  float angle = value * 2.0f * glm::pi<float>();
  for(int i=0; i<_seeds.size(); ++i) {
    float rad = 0.5f * i * _radius;
    _seeds[i].transform.position.x = rad * glm::cos(angle*i);
    _seeds[i].transform.position.y = rad * glm::sin(angle*i);
  }
}
