#pragma once

namespace yaron {
  struct Color {
    Color(float r, float g, float b, float a=1.0f)
      : r(r), g(g), b(b), a(a)
    {}

    float r, b, g, a;

    static const Color black;
    static const Color grey;
    static const Color red;
    static const Color green;
    static const Color yellow;
    static const Color blue;
    static const Color purple;
    static const Color cyan;
    static const Color white;
  };
}
