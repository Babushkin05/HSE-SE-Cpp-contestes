#include <iostream>

void Solve(int n) {
  int x;
  std::cin >> x;
  if (n == 0) {
    std::cout << x << ' ';
    return;
  }
  Solve(n - 1);
  std::cout << x << ' ';
}

int main() {
  int n;
  std::cin >> n;
  Solve(n - 1);

  return 0;
}