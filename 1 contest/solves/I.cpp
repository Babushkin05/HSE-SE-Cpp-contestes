#include <iostream>

int main() {
  int a;
  std::cin >> a;
  for (int i = 2; i <= a; i++) {
    if (a % i == 0) {
      std::cout << i;
      return 0;
    }
  }
}