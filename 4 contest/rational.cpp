#include "rational.h"
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>

Rational::Rational() : Rational::Rational(0){};
Rational::Rational(int num) : Rational::Rational(num, 1){};
Rational::Rational(int num, int denom) : numerator_(num), denominator_(denom) {
  this->ReduceNumber();
}
void Rational::ReduceNumber() {
  if (this->denominator_ < 0) {
    this->numerator_ *= -1;
    this->denominator_ *= -1;
  }
  if (this->denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  if (this->numerator_ == 0) {
    this->denominator_ = 1;
  }
  int32_t gcd = std::gcd(this->numerator_, this->denominator_);
  this->numerator_ /= gcd;
  this->denominator_ /= gcd;
}

int32_t Rational::GetNumerator() const { return this->numerator_; }

int32_t Rational::GetDenominator() const { return this->denominator_; }

void Rational::SetNumerator(int num) {
  this->numerator_ = num;
  this->ReduceNumber();
}

void Rational::SetDenominator(int denom) {
  this->denominator_ = denom;
  this->ReduceNumber();
}

Rational Rational::operator+() const {
  return Rational{this->numerator_, this->denominator_};
}
Rational Rational::operator-() const {
  return Rational{-this->numerator_, this->denominator_};
}

Rational Rational::operator+(const Rational &right) const {
  int denom = std::lcm(this->denominator_, right.GetDenominator());
  int num = this->numerator_ * denom / this->denominator_ +
            right.GetNumerator() * denom / right.GetDenominator();
  return Rational{num, denom};
}

Rational Rational::operator-(const Rational &right) const {
  return *this + -right;
}

Rational Rational::operator*(const Rational &right) const {
  return Rational{this->numerator_ * right.GetNumerator(),
                  this->denominator_ * right.GetDenominator()};
}

Rational Rational::operator/(const Rational &right) const {
  return Rational{this->numerator_ * right.GetDenominator(),
                  this->denominator_ * right.GetNumerator()};
}

Rational &Rational::operator+=(const Rational &right) {
  *this = *this + right;
  return *this;
}

Rational &Rational::operator-=(const Rational &right) {
  *this = *this - right;
  return *this;
}

Rational &Rational::operator*=(const Rational &right) {
  *this = *this * right;
  return *this;
}

Rational &Rational::operator/=(const Rational &right) {
  *this = *this / right;
  return *this;
}

Rational &Rational::operator++() {
  this->numerator_ += this->denominator_;
  return *this;
}

Rational Rational::operator++(int) {
  Rational temp = *this;
  ++*this;
  return temp;
}

Rational &Rational::operator--() {
  this->numerator_ -= this->denominator_;
  return *this;
}

Rational Rational::operator--(int) {
  Rational temp = *this;
  --*this;
  return temp;
}

bool Rational::operator==(const Rational &right) const {
  return this->numerator_ == right.GetNumerator() &&
         this->denominator_ == right.GetDenominator();
}

bool Rational::operator!=(const Rational &right) const {
  return this->numerator_ != right.GetNumerator() ||
         this->denominator_ != right.GetDenominator();
}

bool Rational::operator<(const Rational &right) const {
  return this->numerator_ * right.GetDenominator() <
         this->denominator_ * right.GetNumerator();
}

bool Rational::operator>(const Rational &right) const { return right < *this; }

bool operator<(int left, const Rational &right) {
  return Rational(left) < right;
}

bool operator>(int left, const Rational &right) {
  return Rational(left) > right;
}

bool Rational::operator<=(const Rational &right) const {
  return !(*this > right);
}

bool Rational::operator>=(const Rational &right) const {
  return !(*this < right);
}

std::ostream &operator<<(std::ostream &sout, const Rational &object) {
  if (object.GetDenominator() == 1) {
    sout << object.GetNumerator();
  } else {
    sout << object.GetNumerator() << '/' << object.GetDenominator();
  }
  return sout;
}

std::istream &operator>>(std::istream &sin, Rational &object) {
  std::string temp;
  sin >> temp;
  size_t pos = temp.find('/');
  int num = 0;
  int denom = 1;
  if (pos != static_cast<size_t>(-1)) {
    num = std::stoi(temp.substr(0, pos));
    denom = std::stoi(temp.substr(pos + 1));
  } else {
    num = std::stoi(temp);
  }
  object = Rational(num, denom);
  return sin;
}
