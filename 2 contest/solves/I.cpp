#include <cmath>
#include <iostream>

int main() {
  size_t num;
  std::cin >> num;
  for (size_t i = 2; i * i <= num; i++) {
    if (num % i == 0) {
      std::cout << "composite";
      return 0;
    }
  }
  std::cout << "prime";

  return 0;
}