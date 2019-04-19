#pragma once

#include <context.hpp>
#include <string>

class App {
public:
  App();
  virtual ~App() = 0;

  bool init(char *argv[], int argc);
  void deinit();

  void update();
  void render();
  
  bool exitRequest();

  const std::string& applicationName() const;
  std::string resourcePath(const std::string &name) const;

protected:
  virtual bool vOnInit(char *argv[], int argc) { return true; }
  virtual void vOnDeinit() { }

  virtual void vOnUpdate(float dt, float time) { }
  virtual void vOnRender(RenderContext &context) { }

private:
  RenderContext _renderContext;
  PerspectiveCamera _camera;
};

App *allocateApplication();
