#include <context.hpp>
#include <shader.hpp>

#include <primitives.hpp>

#include <glm/glm.hpp>

#include <app.hpp>

class FlowerApp : public App {
protected:
  bool vOnInit(char *argv[], int argc) final override;
  void vOnDeinit() final override;

  void vOnRender(RenderContext &context) final override;

private:
  ShaderPtr _shader;
  GeometryPtr _circle;
};

App *allocateApplication() {
  return new FlowerApp();
}

bool FlowerApp::vOnInit(char *argv[], int argc) {
  _shader = ShaderBuilder()
    .addVertexShader("resources/simple.vertexshader")
    .addFragmentShader("resources/simple.fragmentshader")
    .build();

  _circle = createCircle(8);

  return true;
}

void FlowerApp::vOnDeinit() {
  _circle = nullptr;
  _shader = nullptr;
}

void FlowerApp::vOnRender(RenderContext &context) {
  context.useShader(_shader);
  context.renderGeometry(_circle, glm::mat4(1.0f));
}
