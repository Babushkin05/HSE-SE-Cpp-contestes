#include <iostream>
#include "matrix.h"
#include <type_traits>

int main(){
    Matrix<int,3,2> m{1,2,3,4,5,9};
    Matrix<int,2,2> a{1,2,3,4};
    Matrix<int,2,2> b{1,2,3,4};
    std::cout<<m;
    std::cout<< (m*=a)<<m;
    std::cout<<(7*(GetTransposed(a)-b) == 7 * (GetTransposed(b) - a));
    std::cout<<m.ColumnsNumber()<<' '<<m.RowsNumber();
}