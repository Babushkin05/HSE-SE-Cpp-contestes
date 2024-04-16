#include <algorithm>
#include <iostream>

bool IsDigit(unsigned char c) {
	return c <= '9' && c >= '0'; 
}

int main() {
  unsigned char c;
  std::cin >> c;
  IsDigit(c) ? std::cout << "yes" : std::cout << "no";
  return 0;
}