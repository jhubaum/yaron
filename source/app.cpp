#include <app.hpp>

App::App()
  : _camera(0.0f, 0.0f)
{ }

App::~App()
{ }


bool App::init(char *argv[], int argc) {
  //std::string baseName(argv[0]);

  if (!_renderContext.init(1366, 768))
    return false;

  _camera = PerspectiveCamera(glm::radians(45.0f), _renderContext.aspectRatio());
  _camera.position({0.0f, 0.0f, -5.0f});

  return vOnInit(argv, argc);
}


void App::deinit() {
  vOnDeinit();

  _renderContext.deinit();
}


void App::update() {
  vOnUpdate(0.0f, 0.0f);
}


void App::render() {
  _renderContext.beginFrame(_camera.calculateViewProjectionMatrix());
  vOnRender(_renderContext);
  _renderContext.endFrame();
}


bool App::exitRequest() {
  return _renderContext.exitRequest();
}


const std::string& App::applicationName() const {
  return "Blub";
}


std::string App::resourcePath(const std::string &name) const {
  return name;
}
