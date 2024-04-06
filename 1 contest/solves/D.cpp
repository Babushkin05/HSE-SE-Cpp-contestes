#include <iostream>

int main() {
  int a;
  std::cin >> a;
  a % 2 ? std::cout << "NO" : std::cout << "YES";
  return 0;
}