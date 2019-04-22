#include <app.hpp>
#include <context.hpp>
#include <shader.hpp>
#include <primitives.hpp>

#include <vector>
#include <glm/gtc/constants.hpp>

#include <complex.hpp>

#include <iostream>

class MandelbrotApp : public App {
public:
  MandelbrotApp(uint32_t maxIterations)
    : _maxIterations(maxIterations)
  {}

protected:
  bool vOnInit(char *argv[], int argc) final override;

  void vOnRender(RenderContext &context) final override;

private:
  void initIterations(const ComplexNumber &constant);

  uint32_t _maxIterations;
  std::vector<Object> _coordinates;
  ShaderPtr _shader;
  Object _line;
};

App *allocateApplication() {
  return new MandelbrotApp(25);
}

bool MandelbrotApp::vOnInit(char *argv[], int argc) {
  _shader = ShaderBuilder()
    .addVertexShader("resources/simple.vertexshader")
    .addFragmentShader("resources/simple.fragmentshader")
    .build();


  initIterations(ComplexNumber(-0.5f, 0.5f));

  return true;
}

void MandelbrotApp::vOnRender(RenderContext &context) {
  context.useShader(_shader);


  _shader->drawMode(DrawMode::LineStrip);
  context.renderGeometry(_line.geometry, glm::mat4(1.0f));
  _shader->drawMode(DrawMode::Triangles);


  for(int i=0; i<_coordinates.size(); ++i)
    context.renderGeometry(_coordinates[i].geometry,
                           _coordinates[i].transform.calculateWorld());
}

void MandelbrotApp::initIterations(const ComplexNumber &constant) {
  _coordinates.clear();
  auto circleGeometry = createCircle(8, 0.02f);

  std::vector<glm::vec3> _linePoints;
  std::vector<unsigned short> _lineIndices;

  auto c = constant;
  for(int i=0; i<_maxIterations; ++i) {
    auto pos = glm::vec3(c.re, c.im, 0.0f);
    _linePoints.push_back(pos);
    _lineIndices.push_back(static_cast<unsigned short>(i));

    _coordinates.push_back({circleGeometry, Transform(pos)});
    c = c * c + constant;
  }

  _line = Object(Geometry::create(_linePoints, _lineIndices), Transform());
}
