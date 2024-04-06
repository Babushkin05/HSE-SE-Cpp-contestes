#include <cmath>
#include <iostream>

int main() {
  int a;
  int b;
  std::cin >> a >> b;
  double c = std::sqrt(double(a) * a + b * b);
  std::cout << c << '\n';
  return 0;
}