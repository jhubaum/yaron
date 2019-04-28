#pragma once

#include <memory>

#include <shader.hpp>
#include <transform.hpp>

struct PointLight {
  PointLight(const Color &c, float strength=100.0f);

  std::shared_ptr<Transform> transform;
  Color color;
  float strength;
};
