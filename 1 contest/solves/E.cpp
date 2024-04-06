#include <iostream>

int main() {
  int a;
  std::cin >> a;
  (a % 4 == 0 && a % 100) || a % 400 == 0 ? std::cout << "YES" : std::cout << "NO";
  return 0;
}