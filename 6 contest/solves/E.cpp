#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

bool Compare(std::tuple<int, int, int> a, std::tuple<int, int, int> b) {
  if (std::get<0>(a) < std::get<0>(b)) {
    return true;
  }
  if (std::get<1>(a) > std::get<1>(b) && std::get<0>(a) == std::get<0>(b)) {
    return true;
  }
  if (std::get<2>(a) > std::get<2>(b) && std::get<1>(a) == std::get<1>(b) && std::get<0>(a) == std::get<0>(b)) {
    return true;
  }
  return false;
}

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;
  std::vector<std::tuple<int, int, int>> table(n);

  for (int i = 0; i < n; ++i) {
    int s = 0;
    int t = 0;
    std::cin >> s >> t;
    table[i] = std::make_tuple(s, t, i + 1);
  }

  std::sort(table.rbegin(), table.rend(), Compare);

  for (int i = 0; i < n; i++) {
    std::cout << std::get<2>(table[i]) << '\n';
  }

  return 0;
}