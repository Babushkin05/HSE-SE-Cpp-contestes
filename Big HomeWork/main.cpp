#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "range.h"

int main() {

  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  Range c(5);

  for(const auto& i : Range(5,10,2)){
    std::cout<<i<<' ';
  }


  return 0;
}