#include <algorithm>
#include <iostream>
#include <set>

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;
  std::multiset<int> m;

  for (int i = 0; i < n; ++i) {
    int a = 0;
    std::cin >> a;
    m.insert(a);
  }

  int res = 0;

  while (m.size() > 1) {
    int a = *(m.begin());
    m.erase(m.begin());
    int b = *(m.begin());
    m.erase(m.begin());
    res += (a + b);
    m.insert(a + b);
  }

  std::cout << res;
  return 0;
}