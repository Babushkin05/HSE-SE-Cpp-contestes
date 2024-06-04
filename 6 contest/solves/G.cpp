#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n = 0;
  std::cin >> n;
  std::unordered_map<std::string, std::string> dict;

  std::string first_word;
  std::string second_word;

  for (size_t i = 0; i < n; ++i) {
    std::cin >> first_word >> second_word;

    dict[first_word] = second_word;
    dict[second_word] = first_word;
  }

  size_t q = 0;
  std::cin >> q;

  for (size_t i = 0; i < q; ++i) {
    std::cin >> first_word;

    std::cout << dict[first_word] << '\n';
  }

  return 0;
}