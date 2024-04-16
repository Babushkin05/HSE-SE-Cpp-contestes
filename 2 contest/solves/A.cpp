#include <iostream>

void WriteArr(bool m[], size_t n) {
  for (size_t i = 0; i < n * n; i++) {
    if (i % n == 0 && i != 0) {
      std::cout << '\n';
    }
    std::cout << m[i];
  }
}

int main() {
  size_t n;
  std::cin >> n;

  if (n == 1) {
    std::cout << "1";
    return 0;
  }
  if (n == 3) {
    std::cout << "111\n001\n111";
    return 0;
  }

  bool *m = new bool[n * n];

  for (size_t i = 0; i < n * n; i++) {
    m[i] = false;
  }

  m[0] = true;

  int rot = 0;
  size_t cur_ind = 1;

  bool to_repeat = true;
  while (to_repeat) {
    m[cur_ind] = true;

    size_t cnt = 0;

    if (cur_ind > 1 && !m[cur_ind - 1]) {
      cnt += m[cur_ind - 2];
    }
    if (cur_ind >= 2 * n && !m[cur_ind - n]) {
      cnt += m[cur_ind - 2 * n];
    }
    if (cur_ind < n * n - 2 && !m[cur_ind + 1]) {
      cnt += m[cur_ind + 2];
    }
    if (cur_ind < n * n - 2 * n && !m[cur_ind + n]) {
      cnt += m[cur_ind + 2 * n];
    }

    if (cnt == 3) {
      to_repeat = false;
      return 0;
    }

    if (rot == 0) {
      if (cur_ind % n == n - 1 || m[cur_ind + 2] == 1) {
        cur_ind += n;
        rot = 1;
      } else {
        cur_ind++;
      }
    } else if (rot == 1) {
      if (cur_ind == n * n - 1 || m[cur_ind + 2 * n] == 1) {
        cur_ind--;
        rot = 2;
      } else {
        cur_ind += n;
      }
    } else if (rot == 2) {
      if (cur_ind % n == 0 || (m[cur_ind - 2] == 1 && cur_ind % n != 1)) {
        cur_ind -= n;
        rot = 3;
      } else {
        cur_ind--;
      }
    } else {
      if (cur_ind == 0 || m[cur_ind - 2 * n] == 1) {
        cur_ind++;
        rot = 0;
      } else {
        cur_ind -= n;
      }
    }
  }

  WriteArr(m, n);

  delete[] m;

  return 0;
}