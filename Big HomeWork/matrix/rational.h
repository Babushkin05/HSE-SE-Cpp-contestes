#ifndef RATIONAL_H
#define RATIONAL_H

#include <cstdint>
#include <stdexcept>

class Rational {
private:
  int numerator_;
  int denominator_;
  void ReduceNumber();

public:
  Rational();
  Rational(int); // NOLINT
  Rational(int, int);
  int32_t GetNumerator() const;
  int32_t GetDenominator() const;
  void SetNumerator(int32_t num);
  void SetDenominator(int32_t denom);
  Rational operator+() const;
  Rational operator-() const;
  Rational operator+(const Rational &) const;
  Rational operator-(const Rational &) const;
  Rational operator*(const Rational &) const;
  Rational operator/(const Rational &) const;
  Rational &operator++();
  Rational operator++(int);
  Rational &operator--();
  Rational operator--(int);
  Rational &operator+=(const Rational &);
  Rational &operator-=(const Rational &);
  Rational &operator*=(const Rational &);
  Rational &operator/=(const Rational &);
  bool operator==(const Rational &) const;
  bool operator!=(const Rational &) const;
  bool operator<(const Rational &) const;
  bool operator>(const Rational &) const;
  bool operator<=(const Rational &) const;
  bool operator>=(const Rational &) const;
  friend std::ostream &operator<<(std::ostream &sout, const Rational &object);
  friend std::istream &operator>>(std::istream &sin, Rational &object);
  friend bool operator<(int left, const Rational &right);
  friend bool operator>(int left, const Rational &right);
};

class RationalDivisionByZero : public std::runtime_error {
public:
  RationalDivisionByZero() : std::runtime_error("Division by zero") {}
};

#endif