#include <iostream>

int main() {
  int a;
  int b;
  std::cin >> a >> b;
  int ans = 0;
  while (a != b) {
    if (a > b) {
      ans += a / b;
      a %= b;
    } else {
      ans += b / a;
      b %= a;
    }
    if (a == 0 || b == 0) {
      break;
    }
  }

  std::cout << std::max(ans, 1);
  return 0;
}