#pragma once
#include <algorithm>

namespace yaron {
  template<typename T>
  T lerp(const T &from, const T&to, float t) {
    return from + (to - from) * std::clamp(t, 0.0f, 1.0f);
  }
}
