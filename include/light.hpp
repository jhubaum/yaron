#pragma once
#include <fwd.hpp>

#include <color.hpp>

namespace yaron {
  struct PointLight {
    PointLight(const Color &c, float strength=100.0f);

    std::shared_ptr<Transform> transform;
    Color color;
    float strength;
  };
}
