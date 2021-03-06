#include <iostream>
#include <vector>

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <app.hpp>
#include <complex.hpp>
#include <camera.hpp>
#include <transform.hpp>

#include <graphics/context.hpp>
#include <graphics/shader.hpp>
#include <graphics/primitives.hpp>
#include <graphics/geometry.hpp>

using namespace yaron;
using namespace yaron::graphics;

bool isStable(const ComplexNumber &c) {
  return c.re * c.re + c.im * c.im < 4.0f;
}

struct IterationStep {
  IterationStep(const glm::vec3 position, bool stable)
    : worldMatrix(glm::translate(glm::mat4(1.0f), position)),
      col(stable ? stableColor : unstableColor) {
  }

  glm::mat4 worldMatrix;
  Color col;

  static const Color stableColor;
  static const Color unstableColor;
};

const Color IterationStep::stableColor = Color::cyan;
const Color IterationStep::unstableColor = Color::blue;

class MandelbrotApp : public App {
public:
  MandelbrotApp(uint32_t maxIterations)
    : _maxIterations(maxIterations)
  {}

protected:
  bool vOnInit(const std::vector<std::string>&) final override;
  void vOnUpdate(float dt) final override;
  void vOnRender() final override;

private:
  void initIterations(const ComplexNumber &constant);

  uint32_t _maxIterations;
  GeometryPtr _geometry;
  std::vector<IterationStep> _coordinates;
  ShaderPtr _shader;
  GeometryPtr _line;

  std::shared_ptr<OrthographicCamera> _camera;
};

App *yaron::allocateApplication() {
  return new MandelbrotApp(25);
}

bool MandelbrotApp::vOnInit(const std::vector<std::string> &args) {
  _shader = ShaderBuilder()
    .addVertexShader(resourcePath("shaders/simple.vertexshader"))
    .addFragmentShader(resourcePath("shaders/simple.fragmentshader"))
    .build();

  _camera = std::make_shared<OrthographicCamera>(-4.0f, 2.0f, -1.6f, 1.6f);
  _camera->transform().lock()->position.z = -5.0f;

  _geometry = createCircle(8, 0.02f);

  renderContext()->setCamera(_camera);

  return true;
}

void MandelbrotApp::vOnUpdate(float dt) {
  glm::vec2 pos = input().mousePosition();
  float re = _camera->left() + pos[0] * (_camera->right() - _camera->left());
  float im = _camera->bottom() + pos[1] * (_camera->top() - _camera->bottom());

  initIterations(ComplexNumber(-re, im));
}

void MandelbrotApp::vOnRender() {
  renderContext()->useShader(_shader);

  _shader->set<Color>("mainColor", Color::grey);
  _shader->drawMode(DrawMode::LineStrip);
  renderContext()->renderGeometry(_line, glm::mat4(1.0f));
  _shader->drawMode(DrawMode::Triangles);


  for(int i=0; i<_coordinates.size(); ++i) {
    _shader->set<Color>("mainColor", _coordinates[i].col);
    renderContext()->renderGeometry(_geometry, _coordinates[i].worldMatrix);
  }
}

void MandelbrotApp::initIterations(const ComplexNumber &constant) {
  _coordinates.clear();

  std::vector<VertexP> _linePoints;
  std::vector<unsigned short> _lineIndices;

  auto c = constant;
  for(int i=0; i<_maxIterations; ++i) {
    auto pos = glm::vec3(c.re, c.im, 0.0f);
    _linePoints.push_back({pos});
    _lineIndices.push_back(static_cast<unsigned short>(i));
    bool stable = isStable(c);
    _coordinates.push_back(IterationStep(pos, stable));

    if (!stable)
      break;

    c = c * c + constant;
  }
  _line = Geometry<VertexP>::create(_linePoints, _lineIndices);
}
