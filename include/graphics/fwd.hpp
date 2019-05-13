#pragma once

namespace yaron {
  namespace graphics {
    // shader.hpp
    class ShaderBuilder;

    class Shader;
    typedef std::shared_ptr<Shader> ShaderPtr;

    // context.hpp
    struct RenderSettings;

    class RenderContext;
    typedef std::shared_ptr<RenderContext> RenderContextPtr;

    // geometry.hpp
    class Geometry_B;
    typedef std::shared_ptr<Geometry_B> GeometryPtr;

    // text.hpp
    struct Text;
    struct TextRenderer;
  }
}
