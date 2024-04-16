#include <iostream>

void Sort(int *begin, int *end) {
  for (int *i = begin; i < end; i++) {
    for (int *j = i; j < end; j++) {
      if (*i > *j) {
        std::swap(*i, *j);
      }
    }
  }
}

int main() {
  int len;
  std::cin >> len;

  int *arr = new int[len];

  for (int i = 0; i < len; i++) {
    std::cin >> arr[i];
  }

  Sort(arr, arr + len);

  for (int i = 0; i < len; i++) {
    std::cout << arr[i] << ' ';
  }

  delete[] arr;
  return 0;
}