#include <iostream>
#include <string>
#include <unordered_map>

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;

  std::unordered_map<std::string, int> bank_data;
  for (int it = 0; it < n; ++it) {
    int op_t = 0;
    std::string name;
    std::cin >> op_t >> name;

    if (op_t == 1) {
      int to_add = 0;
      std::cin >> to_add;
      bank_data[name] += to_add;
    } else {
      if (!bank_data.count(name)) {
        std::cout << "ERROR" << '\n';
      } else {
        std::cout << bank_data[name] << '\n';
      }
    }
  }

  return 0;
}