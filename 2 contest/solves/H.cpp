#include <cmath>
#include <iostream>

double Length(double x1, double y1, double x2, double y2) {
  return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
  double x1;
  double y1;
  double x2;
  double y2;
  double x3;
  double y3;
  std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
  double ans = Length(x1, y1, x2, y2) + Length(x2, y2, x3, y3) + Length(x3, y3, x1, y1);
	std::cout << std::fixed;  
	std::cout.precision(6);
  std::cout << ans;

  return 0;
}