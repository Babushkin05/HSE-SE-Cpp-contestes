#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  int balance = 0;
  int ans = 0;
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] == '(') {
      ++balance;
    } else {
      --balance;
    }
    if (balance < 0) {
      ++ans;
      balance = 0;
    }
  }

  std::cout << ans + abs(balance);
}