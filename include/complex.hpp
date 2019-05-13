#pragma once

namespace yaron {
  struct ComplexNumber {
    ComplexNumber(float re, float im)
      : re(re), im(im)
    {}

    float re, im;

    static const ComplexNumber i;

    ComplexNumber operator+(const ComplexNumber &other) const;
    ComplexNumber operator+(float real) const;

    ComplexNumber operator-(const ComplexNumber &other) const;
    ComplexNumber operator-(float real) const;

    ComplexNumber operator*(const ComplexNumber &other) const;
    ComplexNumber operator*(float real) const;

    ComplexNumber operator/(const ComplexNumber &other) const;
    ComplexNumber operator/(float real) const;

    ComplexNumber conjugate() const;
  };

  ComplexNumber operator+(float real, const ComplexNumber &c);
  ComplexNumber operator-(float real, const ComplexNumber &c);
  ComplexNumber operator*(float real, const ComplexNumber &c);
  ComplexNumber operator/(float real, const ComplexNumber &c);
}
