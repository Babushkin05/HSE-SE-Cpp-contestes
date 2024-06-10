#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::unordered_map<std::string, int> words;
  std::string word;
  while (std::cin >> word) {
    ++words[word];
  }
  std::vector<std::pair<int, std::string>> v;
  v.reserve(words.size());
  for (const auto &[key, value] : words) {
    v.emplace_back(value, key);
  }
  sort(v.begin(), v.end(), [](const auto &lhs, const auto &rhs) {
    return lhs.first > rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
  });
  for (const auto &word : v) {
    std::cout << word.second << '\n';
  }
  return 0;
}