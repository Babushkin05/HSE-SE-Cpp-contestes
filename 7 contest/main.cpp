#include <cmath>
#include <iostream>
#include "unique_ptr.h"



int main() {
    UniquePtr ptr(new int(10));
    std::cout<<*ptr;
}