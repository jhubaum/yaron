#include <app.hpp>
#include <primitives.hpp>
#include <camera.hpp>

#include <vector>

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdlib>
#include <ctime>

float generateRandomFloat(float minV=0.0f, float maxV=1.0f) {
  return (static_cast<float>(std::rand()) / RAND_MAX) * (maxV-minV) + minV;
}

int generateRandomInt(int minV, int maxV) {
  return (std::rand() % (maxV - minV)) + minV;
}

int generateRandomInt(int maxV) {
  return generateRandomInt(0, maxV);
}

glm::vec3 generateRandomVec(float min=0.0f, float max=1.0f) {
  return glm::vec3(generateRandomFloat(min, max),
                   generateRandomFloat(min, max), 0.0f);
}

class ChaosPointFractal : public App {
public:
  ChaosPointFractal(uint32_t count, uint32_t anchorCount)
    : _points(count*anchorCount), _anchor(anchorCount)
  {}

protected:
  bool vOnInit(char *argv[], int argc) final override;
  void vOnRender() final override;

private:
  ShaderPtr _shader;
  GeometryPtr _geometry;
  std::shared_ptr<OrthographicCamera> _camera;

  std::vector<glm::vec3> _points;
  std::vector<glm::vec3> _anchor;
};

App *allocateApplication() {
  return new ChaosPointFractal(7500, 3);
}

bool ChaosPointFractal::vOnInit(char *argv[], int argc) {
  _shader = ShaderBuilder()
    .addVertexShader("resources/simple.vertexshader")
    .addFragmentShader("resources/simple.fragmentshader")
    .build();

  _camera = std::make_shared<OrthographicCamera>(-1.2f, 1.2f, -1.2f, 1.2f);
  _camera->transform().lock()->position.z = -5.0f;
  _geometry = createCircle(12, 0.002f);

  for (int i=0; i<_anchor.size(); ++i) {
    float angle = 2.0f * glm::pi<float>() * i / _anchor.size();
    _anchor[i] = glm::vec3(cos(angle), sin(angle), 0.0f);
  }

  std::srand(std::time(nullptr));
  glm::vec3 gen = generateRandomVec();
  for(int i=0; i<_points.size(); ++i) {
    gen = 0.5f * (gen + _anchor[generateRandomInt(_anchor.size())]);
    _points[i] = gen;
  }

  return true;
}

void ChaosPointFractal::vOnRender() {
  renderContext()->beginFrame(_camera);
  renderContext()->useShader(_shader);

  glm::mat4 identity(1.0f);
  _shader->set<Color>("mainColor", Color::green);
  for (int i=0; i<_points.size(); ++i)
    renderContext()->renderGeometry(_geometry, glm::translate(identity, _points[i]));

  _shader->set<Color>("mainColor", Color::blue);
  for (int i=0; i<_anchor.size(); ++i)
    renderContext()->renderGeometry(_geometry, glm::translate(identity, _anchor[i]));

  renderContext()->endFrame();
}
