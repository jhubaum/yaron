#include <app.hpp>
#include <iostream>

#include <graphics/context.hpp>

namespace yaron {
  App::App()
  { }

  App::~App()
  { }

  bool App::init(char *argv[], int argc) {
    std::string baseName(argv[0]);

    std::cout << baseName << std::endl;

    graphics::RenderSettings settings;
    _renderContext = graphics::RenderContext::create(settings);

    if (nullptr == _renderContext)
      return false;

    _lastTime = glfwGetTime();
    return vOnInit(argv, argc);
  }

  void App::deinit() {
    vOnDeinit();
  }

  void App::update() {
    float time = glfwGetTime();
    vOnUpdate(time-_lastTime);
    _lastTime = time;
  }

  void App::render() {
    _renderContext->beginFrame();
    vOnRender();
    _renderContext->endFrame();
  }

  bool App::exitRequest() {
    return _renderContext->exitRequest();
  }

  std::string App::resourcePath(const std::string &name) const {
    return name;
  }

  bool App::vOnInit(char *argv[], int argc) {
    return true;
  }

  void App::vOnDeinit() { }

  void App::vOnUpdate(float dt) { }
  void App::vOnRender() { }

  graphics::RenderContextPtr App::renderContext() {
    return _renderContext;
  }
}
