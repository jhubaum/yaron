#pragma once
#include <fwd.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <color.hpp>

namespace yaron {
  namespace graphics {
    struct RenderSettings {
      uint32_t width, height;
      std::string windowName;
      Color clearColor;

      RenderSettings();
    };

    enum class DepthTest : GLenum {
      Never = GL_NEVER,
      Less = GL_LESS,
      Equal = GL_EQUAL,
      Lequal = GL_LEQUAL,
      Greater = GL_GREATER,
      NotEqual = GL_NOTEQUAL,
      Gequal = GL_GEQUAL,
      Always = GL_ALWAYS
    };

    enum class CullFace {
      None  = 0,
      Front = 1 << 0,
      Back  = 1 << 1
    };

    CullFace operator &(CullFace a, CullFace b);
    CullFace operator |(CullFace a, CullFace b);

    enum class BlendFunc : GLenum {
      Zero = GL_ZERO,
      One = GL_ONE,
      SrcColor = GL_SRC_COLOR,
      OneMinusSrcColor = GL_ONE_MINUS_SRC_COLOR,
      DstColor = GL_DST_COLOR,
      OneMinusDstColor = GL_ONE_MINUS_DST_COLOR,
      SrcAlpha = GL_SRC_ALPHA,
      OneMinusSrcAlpha = GL_ONE_MINUS_SRC_ALPHA,
      DstAlpha = GL_DST_ALPHA,
      OneMinusDstAlpha = GL_ONE_MINUS_DST_ALPHA,
      ConstantColor = GL_CONSTANT_COLOR,
      OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
      ConstantAlpha = GL_CONSTANT_ALPHA,
      OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA,
      SrcAlphaSaturate = GL_SRC_ALPHA_SATURATE,
      Src1Color = GL_SRC1_COLOR,
      OneMinusSrc1Color = GL_ONE_MINUS_SRC1_COLOR,
      Src1Alpha = GL_SRC1_ALPHA,
      OneMinusSrc1Alpha = GL_ONE_MINUS_SRC1_ALPHA
    };

    enum class PolygonMode : GLenum {
      Point = GL_POINT,
      Line = GL_LINE,
      Fill = GL_FILL
    };

    class RenderContext {
    public:
      ~RenderContext();
      static RenderContextPtr create(const RenderSettings&);

      void beginFrame();
      void endFrame();

      void setCamera(std::weak_ptr<Camera> camera);
      void useShader(std::weak_ptr<Shader> shader);
      void renderGeometry(GeometryPtr, const glm::mat4 &world);
      void renderGeometry(GeometryPtr, const Transform &transform);

      void enableBlending(BlendFunc sfactor=BlendFunc::One,
                          BlendFunc dfactor=BlendFunc::Zero);
      void disableBlending();

      void enableDepthTest(DepthTest);
      void disableDepthTest();

      void setCulling(CullFace);
      void setPolygonMode(PolygonMode);


      float aspectRatio() const;
      void clearColor(const Color &c);
      GLFWwindow* window();
      bool exitRequest() const;

    private:
      RenderContext();
      bool init(const RenderSettings &settings);

      GLFWwindow *_window;
      float _aspect;

      std::weak_ptr<Shader> _shader;
      std::weak_ptr<Camera> _camera;
    };
  }
}
