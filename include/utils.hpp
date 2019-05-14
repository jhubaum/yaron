#pragma once

namespace yaron {
  template<typename T>
  T lerp(const T &from, const T&to, float t) {
    return from + t * (to - from);
  }
}
