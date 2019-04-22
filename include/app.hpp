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

  std::string resourcePath(const std::string &name) const;

protected:
  virtual bool vOnInit(char *argv[], int argc) { return true; }
  virtual void vOnDeinit() { }

  virtual void vOnUpdate(float dt) { }
  virtual void vOnRender() { }

  RenderContextPtr renderContext() { return _renderContext; }

private:
  RenderContextPtr _renderContext;
  float _lastTime;
};

App *allocateApplication();
