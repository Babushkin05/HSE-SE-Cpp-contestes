#include <iostream>

int main() {
  size_t n = 0;

  std::cin >> n;

  int **arr = new int *[n];
  for (size_t i = 0; i != n; ++i) {
    arr[i] = new int[n];
  }

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      if (i == n - j - 1) {
        arr[i][j] = 1;
      } else if (i < n - j - 1) {
        arr[i][j] = 0;
      } else {
        arr[i][j] = 2;
      }
    }
  }

  for (size_t i = 0; i != n; ++i) {
    for (size_t j = 0; j != n; ++j) {
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }

  for (size_t i = 0; i != n; ++i) {
    delete[] arr[i];
  }

  delete[] arr;

  return 0;
}