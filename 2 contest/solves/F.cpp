#include <algorithm>
#include <iostream>

size_t Evklid(size_t a, size_t b) {
  if (a == 0) {
    return b;
  }
  return Evklid(b % a, a);
}

int main() {
  size_t cnt;
  std::cin >> cnt;

  size_t gcd;
  std::cin >> gcd;
  cnt--;
  while (cnt--) {
    size_t a;
    std::cin >> a;
    if (a > gcd) {
      std::swap(a, gcd);
    }
    gcd = Evklid(gcd, a);
  }

  std::cout << gcd;
  return 0;
}