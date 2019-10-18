#pragma once

struct Rect {
  Rect(float left, float right, float bottom, float top)
    : left(left), right(right), bottom(bottom), top(top)
  { }

  float left, right, bottom, top;
};
