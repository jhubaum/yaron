#include <graphics/context.hpp>

#include <iostream>

#include <transform.hpp>
#include <camera.hpp>
#include <graphics/shader.hpp>
#include <graphics/geometry.hpp>

namespace yaron {
  namespace graphics {
    RenderSettings::RenderSettings()
      : width(1366), height(768), windowName("Empty Window Name"),
        clearColor(Color::white)
    {}

    CullFace operator &(CullFace a, CullFace b) {
      return static_cast<CullFace>(static_cast<int>(a) &
                                   static_cast<int>(b));
    }

    CullFace operator |(CullFace a, CullFace b) {
      return static_cast<CullFace>(static_cast<int>(a) |
                                   static_cast<int>(b));
    }

    RenderContext::RenderContext()
    {}

    RenderContextPtr RenderContext::create(const RenderSettings &settings) {
      struct SharedEnabler : public RenderContext { };

      RenderContextPtr ptr = std::make_shared<SharedEnabler>();

      if (ptr->init(settings))
        return ptr;
      return nullptr;
    }

    RenderContext::~RenderContext() {
      glfwTerminate();
    }

    bool RenderContext::init(const RenderSettings &settings) {
      if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n" << std::endl;
        return false;
      }

      _aspect = static_cast<float>(settings.width) / settings.height;

      glfwWindowHint(GLFW_SAMPLES, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

      _window = glfwCreateWindow(settings.width, settings.height,
                                 settings.windowName.c_str(), NULL, NULL);
      if (nullptr == _window) {
        std::cout << "Failed to open GLFW window" << std::endl;
        return false;
      }
      glfwMakeContextCurrent(_window);

      if(GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
      }

      clearColor(settings.clearColor);
      glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

      return true;
    }

    void RenderContext::beginFrame() {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderContext::endFrame() {
      glfwSwapBuffers(_window);
      glfwPollEvents();
    }

    void RenderContext::setCamera(std::weak_ptr<Camera> camera) {
      _camera = camera;
    }

    void RenderContext::useShader(std::weak_ptr<Shader> shader) {
      _shader = shader;
      glUseProgram(_shader.lock()->handle());
    }

    void RenderContext::renderGeometry(GeometryPtr geometry, const Transform &transform) {
      renderGeometry(geometry, transform.calculateWorld());
    }

    void RenderContext::renderGeometry(GeometryPtr geometry, const glm::mat4 &world) {
      if (_camera.expired())
        std::cout << "RenderContext: Camera is expired" << std::endl;
      if (_shader.expired())
        std::cout << "RenderContext: Shader is expired" << std::endl;

      auto shader = _shader.lock();
      shader->set<glm::mat4>("viewMatrix", _camera.lock()->viewMatrix());
      shader->set<glm::mat4>("projectionMatrix", _camera.lock()->projectionMatrix());
      shader->set("worldMatrix", world);

      geometry->vEnableVertexAttributes();

      // Draw Triangles
      glDrawElements(static_cast<GLenum>(shader->drawMode()), geometry->indexCount(), GL_UNSIGNED_SHORT, (void*)0);

      geometry->vDisableVertexAttributes();
    }

    void RenderContext::enableBlending(BlendFunc sfactor, BlendFunc dfactor) {
      glEnable(GL_BLEND);
      glBlendFunc(static_cast<GLenum>(sfactor), static_cast<GLenum>(GL_ONE_MINUS_SRC_ALPHA));
    }

    void RenderContext::disableBlending() {
      glDisable(GL_BLEND);
    }

    void RenderContext::setCulling(CullFace cullface) {
      if (CullFace::None == cullface) {
        glDisable(GL_CULL_FACE);
        return;
      }

      glEnable(GL_CULL_FACE);

      GLenum cf;
      if (CullFace::None != (cullface & CullFace::Front) &&
          CullFace::None != (cullface & CullFace::Back))
        cf = GL_FRONT_AND_BACK;
      else if (CullFace::None != (cullface & CullFace::Front))
        cf = GL_FRONT;
      else
        cf = GL_BACK;

      glCullFace(cf);
    }

    void RenderContext::enableDepthTest(DepthTest depthTest) {
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(static_cast<GLenum>(depthTest));
    }

    void RenderContext::disableDepthTest() {
      glDisable(GL_DEPTH_TEST);
    }

    void RenderContext::setPolygonMode(PolygonMode polygonMode) {
      glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(polygonMode));
    }

    float RenderContext::aspectRatio() const { return _aspect; }

    void RenderContext::clearColor(const Color &c) {
      glClearColor(c.r, c.g, c.b, c.a);
    }

    GLFWwindow* RenderContext::window() { return _window; }

    bool RenderContext::exitRequest() const {
      return GLFW_PRESS == glfwGetKey(_window, GLFW_KEY_ESCAPE ) ||
        glfwWindowShouldClose(_window);
    }
  }
}





