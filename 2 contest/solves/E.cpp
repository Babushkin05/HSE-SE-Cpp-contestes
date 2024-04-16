#include <iostream>

size_t BombsAround(size_t i, size_t j, char **arr, size_t n, size_t m) {
  size_t res = 0;
  if (i > 0) {
    res += arr[i - 1][j] == '*';
  }
  if (j > 0) {
    res += arr[i][j - 1] == '*';
  }
  if (i > 0 && j > 0) {
    res += arr[i - 1][j - 1] == '*';
  }
  if (i < n - 1) {
    res += arr[i + 1][j] == '*';
  }
  if (j < m - 1) {
    res += arr[i][j + 1] == '*';
  }
  if (i < n - 1 && j < m - 1) {
    res += arr[i + 1][j + 1] == '*';
  }
  if (i > 0 && j < m - 1) {
    res += arr[i - 1][j + 1] == '*';
  }
  if (i < n - 1 && j > 0) {
    res += arr[i + 1][j - 1] == '*';
  }
  return res;
}

int main() {
  size_t n;
  size_t m;

  std::cin >> n >> m;

  char **arr = new char *[n];
  for (size_t i = 0; i < n; ++i) {
    arr[i] = new char[m];
  }

  size_t bombs;
  std::cin >> bombs;

  while (bombs--) {
    size_t i;
    size_t j;
    std::cin >> i >> j;
    arr[i - 1][j - 1] = '*';
  }

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      if (arr[i][j] == '*') {
        continue;
      }
      arr[i][j] = '0' + BombsAround(i, j, arr, n, m);
    }
  }

  for (size_t i = 0; i != n; ++i) {
    for (size_t j = 0; j != m; ++j) {
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }

  for (size_t i = 0; i < n; ++i) {
    delete[] arr[i];
  }

  delete[] arr;

  return 0;
}