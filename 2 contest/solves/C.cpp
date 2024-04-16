#include <iostream>

int main() {
  size_t n = 0;
  size_t m = 0;

  std::cin >> n >> m;

  int **arr = new int *[n];
  for (size_t i = 0; i != n; ++i) {
    arr[i] = new int[m];
  }

  int elem = 0;

  for (size_t col = 0; col != m; ++col) {
    size_t c = col;
    for (size_t row = 0; row != n; ++row) {
      arr[row][c] = elem++;
      if (c == 0) {
        break;
      } else {
        c--;
      }
    }
  }

  for (size_t row = 1; row != n; ++row) {
    size_t r = row;
    for (size_t col = m; col--;) {
      arr[r++][col] = elem++;
      if (r >= n) {
        break;
      }
    }
  }

  for (size_t i = 0; i != n; ++i) {
    for (size_t j = 0; j != m; ++j) {
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