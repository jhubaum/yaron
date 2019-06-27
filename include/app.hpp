#pragma once
#include <fwd.hpp>

#include <input.hpp>

namespace yaron {
  /// The central class of yaron
  class App {
  public:
    App();
    virtual ~App() = 0;

    bool init(int argc, char *argv[]);
    void deinit();

    void update();
    void render();

    bool exitRequest();

    std::string resourcePath(const std::string &name) const;

  protected:
    virtual bool vOnInit(const std::vector<std::string> &arguments);
    virtual void vOnDeinit();

    virtual void vOnUpdate(float dt);
    virtual void vOnRender();

    graphics::RenderContextPtr renderContext();
    InputManager &input();

private:
    graphics::RenderContextPtr _renderContext;
    InputManager _input;
    std::string _resourceFolder;
    float _lastTime;
  };

  App *allocateApplication();
}
