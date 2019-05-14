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

using namespace yaron;
using namespace yaron::graphics;

class VoxelLandscape : public App  {
public:
  VoxelLandscape(uint32_t xCount, uint32_t yCount)
    : _xCount(xCount), _yCount(yCount), _voxels(xCount*yCount)
  { }

protected:
  bool vOnInit(const std::vector<std::string>&) final override;

  void vOnUpdate(float dt) final override;
  void vOnRender() final override;

private:
  GeometryPtr _geometry;
  ShaderPtr _shader;
  std::shared_ptr<PerspectiveCamera> _camera;
  Controller _controller;

  uint32_t _xCount, _yCount;
  std::vector<glm::vec3> _voxels;
};

App *yaron::allocateApplication() {
  return new VoxelLandscape(100, 100);
}

bool VoxelLandscape::vOnInit(const std::vector<std::string> &args) {
  for (int i=0; i<_xCount; ++i) {
    for (int j=0; j<_yCount; ++j) {
      _voxels[i*_xCount+j] = glm::vec3(i, 0.0f, j);
    }
  }

  _shader = ShaderBuilder()
    .addVertexShader(resourcePath("shaders/simple.vertexshader"))
    .addFragmentShader(resourcePath("shaders/simple.fragmentshader"))
    .build();

  _camera = std::make_shared<PerspectiveCamera>(glm::radians(45.0f), renderContext()->aspectRatio());
  _controller = Controller(_camera->transform(), renderContext()->window());

  _geometry = createCube();

  renderContext()->enableDepthTest(DepthTest::Less);
  renderContext()->setCulling(CullFace::Back);
  renderContext()->setCamera(_camera);

  return true;
}

void VoxelLandscape::vOnUpdate(float dt) {
  _controller.update(dt);
}

void VoxelLandscape::vOnRender() {
  renderContext()->useShader(_shader);
  _shader->set<Color>("mainColor", Color::green);

  for(int i=0; i<_voxels.size(); ++i) {
    auto world = glm::translate(glm::mat4(1.0f), _voxels[i]);
    renderContext()->renderGeometry(_geometry, world);
  }
}
