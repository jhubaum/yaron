#include <light.hpp>

#include <transform.hpp>
#include <graphics/shader.hpp>

namespace yaron {
  PointLight::PointLight(const Color &c, float strength)
    : transform(std::make_shared<Transform>()),
      color(c), strength(strength)
  {}

  namespace graphics {
    template<>
    void Shader::set<PointLight>(const std::string &name, const PointLight &light) {
      set(name + "Pos", light.transform->position);
      set(name + "Color", light.color);
      set(name + "Strength", light.strength);
    }
  }
}
