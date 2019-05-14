#pragma once
#include <fwd.hpp>

namespace yaron {
  /// The central class of yaron
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
    virtual bool vOnInit(char *argv[], int argc);
    virtual void vOnDeinit();

    virtual void vOnUpdate(float dt);
    virtual void vOnRender();

    graphics::RenderContextPtr renderContext();

private:
    graphics::RenderContextPtr _renderContext;
    float _lastTime;
  };

  App *allocateApplication();
}
