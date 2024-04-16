#include <iostream>

int main() {
  size_t n;
  size_t m;

  std::cin >> n >> m;

  size_t **arr = new size_t *[n];

  for (size_t i = 0; i < n; i++) {
    arr[i] = new size_t[m];
  }

  for (size_t i = 0; i < n; i++) {
    arr[i][0] = 1;
  }

  for (size_t i = 0; i < m; i++) {
    arr[0][i] = 1;
  }

  for (size_t i = 1; i < n; i++) {
    for (size_t j = 1; j < m; j++) {
      arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
    }
  }

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      std::cout << arr[i][j] << ' ';
    }
    std::cout << '\n';
  }

  for (size_t i = 0; i != n; ++i) {
    delete[] arr[i];
  }

  delete[] arr;

  return 0;
}