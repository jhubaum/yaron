#include <light.hpp>

template<>
void Shader::set<PointLight>(const std::string &name, const PointLight &light) {
  set(name + "Pos", light.transform->position);
  set(name + "Color", light.color);
  set(name + "Strength", light.strength);
}


PointLight::PointLight(const Color &c, float strength)
  : transform(std::make_shared<Transform>()),
    color(c), strength(strength)
{}
