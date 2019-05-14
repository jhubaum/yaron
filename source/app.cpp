#include <app.hpp>
#include <iostream>

#include <graphics/context.hpp>

namespace yaron {
  App::App()
    : _resourceFolder("")
  { }

  App::~App()
  { }

  bool App::init(int argc, char *argv[]) {
    std::string baseName(argv[0]);
    std::string::size_type execDir = baseName.find_last_of("/\\");
    if (std::string::npos != execDir)
      _resourceFolder =  baseName.substr(0, execDir + 1);
    _resourceFolder.append("../resources/");

    std::vector<std::string> args(argc-1);
    for (int i=1; i<argc; ++i)
      args[i-1] = argv[i];

    graphics::RenderSettings settings;
    _renderContext = graphics::RenderContext::create(settings);

    if (nullptr == _renderContext)
      return false;

    _lastTime = glfwGetTime();
    return vOnInit(args);
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
    return _resourceFolder + name;
  }

  bool App::vOnInit(const std::vector<std::string> &args) {
    return true;
  }

  void App::vOnDeinit() { }

  void App::vOnUpdate(float dt) { }
  void App::vOnRender() { }

  graphics::RenderContextPtr App::renderContext() {
    return _renderContext;
  }
}
