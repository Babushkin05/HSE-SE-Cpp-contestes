#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t m = 0;
  std::cin >> m;
  std::queue<int> q;
  std::list<int> l;
  std::unordered_map<int, std::list<int>::iterator> map;

  int a = 0;
  while (std::cin >> a) {
    if (map.count(a)) {
      l.erase(map[a]);
      l.push_front(a);
      map[a] = l.begin();
      std::cout << 0 << ' ';
    } else {
      l.push_front(a);
      map[a] = l.begin();
      std::cout << 1 << ' ';
    }
    if (l.size() > m) {
      map.erase(l.back());
      l.pop_back();
    }
  }

  return 0;
}