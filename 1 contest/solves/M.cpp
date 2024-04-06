#include <iostream>

int main() {
  int n;
  std::cin >> n;
  if (n == 0) {
    std::cout << 0;
  } else if (n < 3) {
    std::cout << 1;
  } else if (n == 3) {
    std::cout << 2;
  } else {
    int a = 1;
    int b = 1;
    int c = 1;
    for (int i = 3; i <= n; i++) {
      a = b;
      b = c;
      c = a + b;
    }
    std::cout << c;
  }
  return 0;
}