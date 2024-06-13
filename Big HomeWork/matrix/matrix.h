#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>

class MatrixOutOfRange : public std::runtime_error {
public:
  MatrixOutOfRange() : std::runtime_error("Index out of range") {}
};
template<typename T, size_t N, size_t M>
class Matrix {
 public:
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix<T, M, M>& other);
  Matrix& operator*=(int other);
  Matrix& operator/=(int other);
  size_t RowsNumber() const;
  size_t ColumnsNumber() const;
  T& operator()(size_t i, size_t j);
  const T& operator()(size_t i, size_t j) const;
  T& At(size_t i, size_t j);
  const T& At(size_t i, size_t j) const;
  T data_[N][M];
};

template<typename T, size_t N, size_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator+=(const Matrix& other) {
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            operator()(i,j) += other(i, j);
        }
    }
    return *this;
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator-=(const Matrix& other) {
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            operator()(i,j) -= other(i, j);
        }
    }
    return *this;
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator*=(const Matrix<T, M, M>& other) {
    Matrix<T,N,M> result;
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            result(i, j) = 0;
            for(size_t k = 0; k < M; ++k) {
                result(i, j) += operator()(i,k) * other(k,j);
            }
        }
    }
    return *this = result;
}

template<typename T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T,N,M>::operator*=(int other) {
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            operator()(i,j) *= other;
        }
    }
    return *this;
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M>& Matrix<T,N,M>::operator/=(int other) {
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            operator()(i,j) /= other;
        }
    }
    return *this;
}

template<typename T, size_t N, size_t M>
size_t Matrix<T,N,M>::RowsNumber() const {
    return N;
}

template<typename T, size_t N, size_t M>
size_t Matrix<T,N,M>::ColumnsNumber() const {
    return M;
}

template<typename T, size_t N, size_t M>
T& Matrix<T,N,M>::operator()(size_t i, size_t j) {
    return data_[i][j];
}

template<typename T, size_t N, size_t M>
const T& Matrix<T,N,M>::operator()(size_t i, size_t j) const {
    return data_[i][j];
}

template<typename T, size_t N, size_t M>
T& Matrix<T,N,M>::At(size_t i, size_t j) {
    if(i >= N || j >= M) {
        throw MatrixOutOfRange{};
    }
    return data_[i][j];
}

template<typename T, size_t N, size_t M>
const T& Matrix<T,N,M>::At(size_t i, size_t j) const {
    if(i >= N || j >= M) {
        throw MatrixOutOfRange{};
    }
    return data_[i][j];
}

template<typename T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(const Matrix<T, N, M>& matrix) {
    Matrix<T, M, N> result;
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            result(j, i) = matrix(i, j);
        }
    }
    return result;
}

template<typename T, size_t N>
void Transpose(Matrix<T, N, N>& matrix) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i + 1; j < N; ++j) {
            std::swap(matrix(i, j), matrix(j, i));
        }
    }
}

template<typename T, size_t N>
T Trace(const Matrix<T, N, N>& matrix) {
    T sum = 0;
    for (size_t i = 0; i < N; ++i) {
        sum += matrix(i, i);
    }
    return sum;
}

template<typename T, size_t N, size_t M>
bool operator==(const Matrix<T, N, M>& lhs, const Matrix<T, N, M>& rhs) {
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            if(lhs(i,j) != rhs(i,j)) {
                return false;
            }
        }
    }
    return true;
}

template<typename T, size_t N, size_t M>
bool operator!=(const Matrix<T, N, M>& lhs, const Matrix<T, N, M>& rhs) {
    return !(lhs == rhs);
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M> operator+(const Matrix<T, N, M>& lhs, const Matrix<T, N, M>& rhs) {
    return Matrix<T,N,M>(lhs) += rhs;
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M> operator-(const Matrix<T, N, M>& lhs, const Matrix<T, N, M>& rhs) {
    return Matrix<T,N,M>(lhs) -= rhs;
}

template<typename T, size_t N, size_t M, size_t K>
Matrix<T,N,K> operator*(const Matrix<T, N, M>& lhs, const Matrix<T, M, K>& rhs) {
    Matrix<T,N,K> result;
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < K; ++j) {
            result(i, j) = 0;
            for(size_t k = 0; k < M; ++k) {
                result(i, j) += lhs(i,k) * rhs(k,j);
            }
        }
    }
    return result;
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M> operator*(const Matrix<T, N, M>& lhs, int rhs) {
    return Matrix<T,N,M>(lhs) *= rhs;
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M> operator*(int lhs, const Matrix<T, N, M>& rhs) {
    return Matrix<T,N,M>(rhs) *= lhs;
}

template<typename T, size_t N, size_t M>
Matrix<T,N,M> operator/(const Matrix<T, N, M>& lhs, int rhs) {
    return Matrix<T,N,M>(lhs) /= rhs;
}

template<typename T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& stream, const Matrix<T,N,M>& other) {
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j + 1 < M; ++j) {
            stream << other(i,j) << " ";
        }
        stream << other(i, M - 1) << std::endl;
    } 
    return stream;
}

template<typename T, size_t N, size_t M>
std::istream& operator>>(std::istream& stream, Matrix<T,N,M>& other) {
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < M; ++j) {
            stream >> other(i,j);
        }
    } 
    return stream;
}
#endif