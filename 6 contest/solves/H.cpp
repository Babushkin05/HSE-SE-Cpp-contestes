#include <algorithm>
#include <iostream>
#include <map>

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::map<std::string, std::map<std::string, int64_t>> database;

  std::string name_of_consumer;
  std::string product;
  int count = 0;

  while (std::cin >> name_of_consumer) {
    std::cin >> product >> count;
    database[name_of_consumer][product] += count;
  }

  for (auto user : database) {
    std::cout << user.first << ':' << '\n';
    for (auto product : user.second) {
      std::cout << product.first << ' ' << product.second << '\n';
    }
  }

  return 0;
}