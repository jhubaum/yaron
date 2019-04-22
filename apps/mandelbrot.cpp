#include <app.hpp>
#include <context.hpp>
#include <shader.hpp>
#include <primitives.hpp>

#include <vector>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <complex.hpp>

#include <iostream>

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
  bool vOnInit(char *argv[], int argc) final override;
  void vOnRender() final override;

private:
  void initIterations(const ComplexNumber &constant);

  uint32_t _maxIterations;
  GeometryPtr _geometry;
  std::vector<IterationStep> _coordinates;
  ShaderPtr _shader;
  Object _line;

  std::shared_ptr<PerspectiveCamera> _camera;
};

App *allocateApplication() {
  return new MandelbrotApp(25);
}

bool MandelbrotApp::vOnInit(char *argv[], int argc) {
  _shader = ShaderBuilder()
    .addVertexShader("resources/simple.vertexshader")
    .addFragmentShader("resources/simple.fragmentshader")
    .build();

  _camera = std::make_shared<PerspectiveCamera>(glm::radians(45.0f), renderContext()->aspectRatio());
  _camera->transform().position.z = -5.0f;

  _geometry = createCircle(8, 0.02f);

  initIterations(-0.5f + 0.5f * ComplexNumber::i);

  return true;
}

void MandelbrotApp::vOnRender() {
  renderContext()->beginFrame(_camera);
  renderContext()->useShader(_shader);

  _shader->setColor("mainColor", Color::grey);
  _shader->drawMode(DrawMode::LineStrip);
  renderContext()->renderGeometry(_line.geometry, glm::mat4(1.0f));
  _shader->drawMode(DrawMode::Triangles);


  for(int i=0; i<_coordinates.size(); ++i) {
    _shader->setColor("mainColor", _coordinates[i].col);
    renderContext()->renderGeometry(_geometry, _coordinates[i].worldMatrix);
  }

  renderContext()->endFrame();
}

void MandelbrotApp::initIterations(const ComplexNumber &constant) {
  _coordinates.clear();

  std::vector<glm::vec3> _linePoints;
  std::vector<unsigned short> _lineIndices;

  auto c = constant;
  for(int i=0; i<_maxIterations; ++i) {
    auto pos = glm::vec3(c.re, c.im, 0.0f);
    _linePoints.push_back(pos);
    _lineIndices.push_back(static_cast<unsigned short>(i));
    bool stable = isStable(c);
    _coordinates.push_back(IterationStep(pos, stable));

    if (!stable)
      break;

    c = c * c + constant;
  }
  _line = Object(Geometry::create(_linePoints, _lineIndices), Transform());
}
