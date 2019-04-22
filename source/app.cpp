#include <app.hpp>
#include <iostream>

App::App()
{ }

App::~App()
{ }

bool App::init(char *argv[], int argc) {
  std::string baseName(argv[0]);

  std::cout << baseName << std::endl;

  RenderSettings settings;
  _renderContext = RenderContext::create(settings);

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
  vOnRender();
}

bool App::exitRequest() {
  return _renderContext->exitRequest();
}

std::string App::resourcePath(const std::string &name) const {
  return name;
}
