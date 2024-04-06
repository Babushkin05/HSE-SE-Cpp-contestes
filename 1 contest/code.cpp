#include <iostream>

int Gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return Gcd(b, a % b);
}

int main() {
  int a;
  int b;
  std::cin >> a >> b;
  if (a == 0) {
    b = 1;
  } else {
    if (b < 0) {
      a *= -1;
      b *= -1;
    }
    int g = Gcd(abs(a), abs(b));
    a /= g;
    b /= g;
  }

  std::cout << a << ' ' << b;

  return 0;
}