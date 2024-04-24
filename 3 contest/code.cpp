#include <iostream>
#include <string>

int main() {
  int n;
  std::cin >> n;
  auto *m = new int[n + 3];
  int curind = -1;
  while (n--) {
    std::string command;
    std::cin >> command;
    if (command == "push") {
      int a;
      std::cin >> a;
      ++curind;
      m[curind] = a;
      std::cout << "ok\n";
    } else if (command == "pop") {
      std::cout << m[curind] << '\n';
      --curind;
    } else if (command == "back") {
      std::cout << m[curind] << '\n';
    } else if (command == "size") {
      std::cout << curind + 1 << '\n';
    } else if (command == "clear") {
      std::cout << "ok\n";
      curind = -1;
    } else if (command == "exit") {
      std::cout << "bye\n";
      break;
    }
  }
  delete[] m;
  return 0;
}