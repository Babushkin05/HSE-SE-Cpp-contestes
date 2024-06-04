#include <iostream>
#include <unordered_map>

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;
  std::unordered_map<int, int> zoo;
  for (int it = 0; it < n; ++it) {
    int a = 0;
    std::cin >> a;
    ++zoo[a];
  }

  int req = 0;
  std::cin >> req;

  for (int it = 0; it < req; ++it) {
    int a = 0;
    std::cin >> a;
    std::cout << zoo[a] << '\n';
  }

  return 0;
}