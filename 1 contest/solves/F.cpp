#include <iostream>

int main() {
  int n;
  int m;
  int k;
  std::cin >> n >> m >> k;
  bool f = false;
  for (int i = 1; i < n; i++) {
    if (i * m == k) {
      f = true;
    }
  }
  for (int i = 1; i < m; i++) {
    if (i * n == k) {
      f = true;
    }
  }
  f ? std::cout << "YES" : std::cout << "NO";
  return 0;
}