#include <iostream>
#include <vector>

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;
  std::vector<int> v(2002, 0);
  for (int i = 0; i < 2000; ++i) {
    v[i] = 0;
  }
  int a = 0;
  for (int it = 0; it < n; ++it) {
    std::cin >> a;
    ++v[1000 + a];
  }
  std::cin >> a;
  std::cout << v[1000 + a];

  return 0;
}