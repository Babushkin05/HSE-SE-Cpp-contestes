#include <iostream>

int main() {
  int a;
  std::cin >> a;
  a % 2 ? std::cout << a + 1 : std::cout << a + 2;
  return 0;
}