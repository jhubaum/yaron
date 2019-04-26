#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <geometry.hpp>
#include <camera.hpp>
#include <shader.hpp>

#include <memory>

class RenderContext;
typedef std::shared_ptr<RenderContext> RenderContextPtr;

struct RenderSettings {
  RenderSettings();

  uint32_t width, height;
  std::string windowName;
  Color clearColor;
};

class RenderContext {
public:
  ~RenderContext();
  static RenderContextPtr create(const RenderSettings&);

  void beginFrame(std::weak_ptr<Camera> camera);
  void endFrame();

  void useShader(std::weak_ptr<Shader> shader);
  void renderGeometry(GeometryPtr, const glm::mat4 &world);
  void renderGeometry(GeometryPtr, const Transform &transform);

  bool exitRequest() const;

  float aspectRatio() const { return _aspect; }

  void clearColor(const Color &c);

  GLFWwindow* window() { return _window; }

private:
  RenderContext();
  bool init(const RenderSettings &settings);

  GLFWwindow *_window;

  std::weak_ptr<Shader> _shader;
  std::weak_ptr<Camera> _camera;

  float _aspect;
};
