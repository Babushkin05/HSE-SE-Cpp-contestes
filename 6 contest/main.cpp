#include <algorithm>
#include <iostream>
#include <map>

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;
  std::map<std::string, std::map<std::string, int>> database;

  std::string name_of_consumer;
  std::string product;
  int count = 0;

  while (std::cin >> name_of_consumer) {
    std::cin >> product >> count;
    std::cout << name_of_consumer << '\n';
    database[name_of_consumer][product] += count;
  }

  for (auto iter1 = database.begin(); iter1 != database.end(); ++iter1) {
    std::string key = iter1->first;
    std::cout << key << ':' << '\n';
    for (auto iter2 = database[key].begin(); iter2 != database[key].begin();
         ++iter2) {
      std::cout << iter2->first << ' ' << iter2->second << '\n';
    }
  }

  return 0;
}