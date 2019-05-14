#pragma once

#include <cstdint>

#include <utils.hpp>

namespace yaron {
  class Random {
  public:
    Random();
    Random(uint32_t seed);

    int randInt();

    /**
     * to is exclusive
     **/
    int randInt(int from, int to);

    float randFloat();
    float randFloat(float from, float to);

    template<typename T>
    T rand();

    template<typename T>
    T rand(const T& from, const T& to) {
      return lerp(from, to, randFloat());
    }
  };
}
