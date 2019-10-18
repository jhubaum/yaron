#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <app.hpp>
#include <light.hpp>
#include <controls.hpp>
#include <camera.hpp>
#include <graphics/context.hpp>
#include <graphics/shader.hpp>
#include <graphics/primitives.hpp>

#include <transform.hpp>

using namespace yaron;
using namespace yaron::graphics;

class ShaderTestApp : public App {
protected:
  bool vOnInit(const std::vector<std::string>&) final override;

  void vOnUpdate(float dt) final override;
  void vOnRender() final override;

private:
  GeometryPtr _geometry;
  ShaderPtr _shader;
  std::shared_ptr<OrthographicCamera> _camera;
  //std::shared_ptr<PerspectiveCamera> _camera;
};

App *yaron::allocateApplication() {
  return new ShaderTestApp();
}

bool ShaderTestApp::vOnInit(const std::vector<std::string> &args) {
  _shader = ShaderBuilder()
    .addVertexShader(resourcePath("shaders/simple.vertexshader"))
    .addFragmentShader(resourcePath("shaders/bookofshaders.fragmentshader"))
    .build();

  _camera = std::make_shared<OrthographicCamera>(-1.0f, 0.0f, 0.0f, 1.0f);
  //_camera = std::make_shared<PerspectiveCamera>(glm::radians(45.0f), renderContext()->aspectRatio());
  _camera->transform().lock()->position.z = -1.0f;

  _geometry = createPlane(Rect(0.0f, 1.0f, 0.0f, 1.0f));

  renderContext()->enableDepthTest(DepthTest::Less);
  renderContext()->setCulling(CullFace::Back);
  renderContext()->setCamera(_camera);

  return true;
}

void ShaderTestApp::vOnUpdate(float dt) {
}

void ShaderTestApp::vOnRender() {
  renderContext()->useShader(_shader);
  _shader->set<glm::vec2>("u_resolution", renderContext()->resolution());
  _shader->set<float>("u_time", time());

  renderContext()->renderGeometry(_geometry, glm::mat4(1.0f));
}
