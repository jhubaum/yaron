#include <complex.hpp>

const ComplexNumber ComplexNumber::i = ComplexNumber(0.0f, 1.0f);

ComplexNumber ComplexNumber::operator+(const ComplexNumber &other) const {
  return ComplexNumber(re + other.re, im + other.im);
}

ComplexNumber ComplexNumber::operator+(float real) const {
  return ComplexNumber(re + real, im);
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber &other) const {
  return ComplexNumber(re - other.re, im - other.im);
}

ComplexNumber ComplexNumber::operator-(float real) const {
  return ComplexNumber(re-real, im);
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber &other) const {
  return ComplexNumber(re*other.re - im*other.im,
                       re*other.im + im*other.re);
}

ComplexNumber ComplexNumber::operator*(float real) const {
  return ComplexNumber(real*re, real*im);
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber &other) const {
  float div = other.re * other.re + other.im * other.im;
  return *this * other.conjugate() / div;
}

ComplexNumber ComplexNumber::operator/(float real) const {
  return ComplexNumber(re / real, im / real);
}

ComplexNumber ComplexNumber::conjugate() const {
  return ComplexNumber(re, -im);
}

ComplexNumber operator+(float real, const ComplexNumber &c) {
  return c + real;
}

ComplexNumber operator-(float real, const ComplexNumber &c) {
  return ComplexNumber(real - c.re, -c.im);
}

ComplexNumber operator*(float real, const ComplexNumber &c) {
  return c * real;
}

ComplexNumber operator/(float real, const ComplexNumber &c) {
  return (real / (c.re * c.re + c.im * c.im)) * c.conjugate();
}
