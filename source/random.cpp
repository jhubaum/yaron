#include <random.hpp>

#include <cstdlib>
#include <ctime>

namespace yaron {
  Random::Random()
    : Random(static_cast<uint32_t>(std::time(0)))
  {}

  Random::Random(uint32_t seed) {
    std::srand(seed);
  }

  int Random::randInt() {
    return std::rand();
  }

  int Random::randInt(int from, int to) {
    return (randInt() % (to - from)) + from;
  }

  float Random::randFloat() {
    return static_cast<float>(randInt()) / RAND_MAX;
  }

  float Random::randFloat(float from, float to) {
    return randFloat() * (to-from) + from;
  }

  template<>
  float Random::rand<float>() {
    return randFloat();
  }

  template<>
  int Random::rand<int>() {
    return randInt();
  }
}
