#include <iostream>

void Hanoi(int n, int cur_tower, int to_tower) {
  if (n == 1) {
    std::cout << 1 << ' ' << cur_tower << ' ' << to_tower << '\n';
    return;
  }
  Hanoi(n - 1, cur_tower, cur_tower ^ to_tower);
  std::cout << n << ' ' << cur_tower << ' ' << to_tower << '\n';
  Hanoi(n - 1, cur_tower ^ to_tower, to_tower);
}

int main() {
  int n;
  std::cin >> n;
  Hanoi(n, 1, 3);
}