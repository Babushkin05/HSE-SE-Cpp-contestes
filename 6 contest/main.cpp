#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

bool Comp(std::pair<std::string, int> a, std::pair<std::string, int> b) {
  if (a.second > b.second) {
    return true;
  }
  if (a.second == b.second && a.first > b.first) {
    return true;
  }
  return false;
}

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::unordered_map<std::string, int> words;

  std::string word;

  while (std::cin >> word) {
    ++words[word];
  }

  std::vector<std::pair<std::string, int>> v(words.begin(), words.end());

  sort(v.rbegin(), v.rend(), Comp);

  for (auto word : v) {
    std::cout << word.first << '\n';
  }

  return 0;
}