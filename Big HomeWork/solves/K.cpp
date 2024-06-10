#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;
  std::vector<std::string> v(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> v[i];
  }
  int ans = 0;
  for (const auto &i : v) {
    for (const auto &j : v) {
      if (&i == &j) {
        continue;
      }
      if (i.find(j) != std::string::npos) {
        ++ans;
      }
    }
  }

  std::cout << ans;

  return 0;
}