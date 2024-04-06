#include <iostream>
#include <string>

int main() {
  std::string number;
  std::cin >> number;

  int ans = 0;

  for (uint64_t i = 0; i < number.size(); i++) {
    ans += number[i] - '0';
  }

  std::cout << ans;
  return 0;
}