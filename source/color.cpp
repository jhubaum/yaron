#include <color.hpp>

#include <random.hpp>

namespace yaron {
  const Color Color::black = Color(0.0f, 0.0f, 0.0f);
  const Color Color::grey = Color(0.5f, 0.5f, 0.5f);
  const Color Color::red = Color(1.0f, 0.0f, 0.0f);
  const Color Color::green = Color(0.0f, 1.0f, 0.0f);
  const Color Color::yellow = Color(1.0f, 1.0f, 0.0f);
  const Color Color::blue = Color(0.0f, 0.0f, 1.0f);
  const Color Color::purple = Color(1.0f, 0.0f, 1.0f);
  const Color Color::cyan = Color(0.0f, 1.0f, 1.0f);
  const Color Color::white = Color(1.0f, 1.0f, 1.0f);

  template<>
  Color Random::rand<Color>() {
    return Color(rand<float>(), rand<float>(), rand<float>(), 1.0f);
  }

  Color Color::operator+(const Color &other) const {
    return Color(this->r + other.r,
                 this->g + other.g,
                 this->b + other.b, 1.0f);
  }

  Color Color::operator-(const Color &other) const {
    return Color(this->r - other.r,
                 this->g - other.g,
                 this->b - other.b, 1.0f);
  }

  Color Color::operator*(float t) const {
    return Color(this->r * t,
                 this->g * t,
                 this->b * t, 1.0f);
  }
}
