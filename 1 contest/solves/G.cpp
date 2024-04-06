#include <iostream>

int main() {
  int a;
  int b;
  int c;
  int d;
  std::cin >> a >> b >> c >> d;

  if (a == 0) {
    if (b == 0) {
      std::cout << "INF";
    } else {
      std::cout << "NO";
    }
  } else {
    if (b % a == 0) {
      int m = -b / a;
      if (c * m + d == 0) {
        std::cout << "NO";
      } else {
        std::cout << m;
      }
    } else {
      std::cout << "NO";
    }
  }

  return 0;
}
