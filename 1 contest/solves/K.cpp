#include <iostream>
#include <vector>

int main() {
  std::vector<int> v;

  bool is_reapet = true;

  while (is_reapet) {
    int a;
    std::cin >> a;
    if (a) {
      v.push_back(a);
    } else {
      is_reapet = false;
    }
  }

  int max_el = 0;
  for (uint64_t i = 0; i < v.size(); i++) {
    max_el = std::max(max_el, v[i]);
  }
  int ans = 0;

  bool after_max = false;
  for (uint64_t i = 0; i < v.size(); i++) {
    if (v[i] < max_el || after_max) {
      ans = std::max(ans, v[i]);
    } else {
      after_max = true;
    }
  }

  std::cout << ans;
  return 0;
}