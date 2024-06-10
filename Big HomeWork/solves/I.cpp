#include <algorithm>
#include <iostream>
#include <set>
#include <string>

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::multiset<std::string> m;

  std::string s;
  while (std::cin >> s) {
    std::cout << m.count(s) << ' ';
    m.insert(s);
  }

  return 0;
}