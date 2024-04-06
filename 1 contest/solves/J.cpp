#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int64_t sum = 0;
  while (n--) {
    int a;
    std::cin >> a;
    sum += a;
  }
  std::cout << sum;

  return 0;
}