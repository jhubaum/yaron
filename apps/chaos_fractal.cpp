#include <vector>

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <app.hpp>
#include <camera.hpp>
#include <color.hpp>
#include <transform.hpp>
#include <random.hpp>
#include <graphics/context.hpp>
#include <graphics/primitives.hpp>
#include <graphics/shader.hpp>

using namespace yaron;
using namespace yaron::graphics;

template<>
glm::vec3 yaron::Random::rand<glm::vec3>() {
  return glm::vec3(rand<float>(), rand<float>(), 0.0f);
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

App *yaron::allocateApplication() {
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

  auto r = Random();
  glm::vec3 gen = r.rand<glm::vec3>();
  for(int i=0; i<_points.size(); ++i) {
    gen = 0.5f * (gen + _anchor[r.randInt(0, _anchor.size())]);
    _points[i] = gen;
  }

  renderContext()->setCamera(_camera);

  return true;
}

void ChaosPointFractal::vOnRender() {
  renderContext()->useShader(_shader);

  glm::mat4 identity(1.0f);
  _shader->set<Color>("mainColor", Color::green);
  for (int i=0; i<_points.size(); ++i)
    renderContext()->renderGeometry(_geometry, glm::translate(identity, _points[i]));

  _shader->set<Color>("mainColor", Color::blue);
  for (int i=0; i<_anchor.size(); ++i)
    renderContext()->renderGeometry(_geometry, glm::translate(identity, _anchor[i]));
}
