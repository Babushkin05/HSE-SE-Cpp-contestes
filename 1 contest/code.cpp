#include <cmath>
#include <iostream>

int main() {
  bool is_reapet = true;
  int max_el = 0;
  int after_max = 0;

  while (is_reapet) {
    int a;
    std::cin >> a;
    if (a) {
      if (a >= max_el) {
        after_max = max_el;
        max_el = a;
      } else if (a > after_max) {
        after_max = a;
      }
    } else {
      is_reapet = false;
    }
  }

  std::cout << after_max;
  return 0;
}