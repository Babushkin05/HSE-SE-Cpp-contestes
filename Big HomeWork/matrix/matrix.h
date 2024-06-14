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

template <typename T, const size_t Row, const size_t Column> class Matrix {
public:
  T matrix_[Row][Column];
  size_t RowsNumber() const { return Row; }
  size_t ColumnsNumber() const { return Column; }

  T &operator()(size_t i, size_t j) { return matrix_[i][j]; }
  T operator()(size_t i, size_t j) const { return matrix_[i][j]; }

  T &At(size_t i, size_t j) {
    if (i >= Row || j >= Column) {
      throw MatrixOutOfRange{};
    }
    return matrix_[i][j];
  }
  T At(size_t i, size_t j) const {
    if (i >= Row || j >= Column) {
      throw MatrixOutOfRange{};
    }
    return matrix_[i][j];
  }

  Matrix operator+(const Matrix &mat) const {
    Matrix<T, Row, Column> temp;
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < ColumnsNumber(); ++j) {
        temp(i, j) = matrix_[i][j] + mat(i, j);
      }
    }
    return temp;
  }
  Matrix operator-(const Matrix &mat) const {
    Matrix<T, Row, Column> temp;
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < ColumnsNumber(); ++j) {
        temp(i, j) = matrix_[i][j] - mat(i, j);
      }
    }
    return temp;
  }

  template <const size_t Col2>
  const Matrix<T, Row, Col2>
  operator*(const Matrix<T, Column, Col2> &mat) const {
    Matrix<T, Row, Col2> temp;
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < mat.ColumnsNumber(); ++j) {
        temp(i, j) = 0;
        for (size_t k = 0; k < ColumnsNumber(); ++k) {
          temp(i, j) += matrix_[i][k] * mat(k, j);
        }
      }
    }
    return temp;
  }

  Matrix &operator+=(const Matrix &mat) {
    *this = *this + mat;
    return *this;
  }

  Matrix &operator-=(const Matrix &mat) {
    *this = *this - mat;
    return *this;
  }
  Matrix &operator*=(const Matrix<T, Column, Column> &mat) {
    *this = *this * mat;
    return *this;
  }
  Matrix operator*(int num) const {
    Matrix<T, Row, Column> temp;
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < ColumnsNumber(); ++j) {
        temp(i, j) = num * matrix_[i][j];
      }
    }
    return temp;
  }

  Matrix &operator*=(int num) {
    *this = *this * num;
    return *this;
  }

  Matrix operator/(int num) const {
    Matrix<T, Row, Column> temp;
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < ColumnsNumber(); ++j) {
        temp(i, j) = matrix_[i][j] / num;
      }
    }
    return temp;
  }
  Matrix &operator/=(int num) {
    *this = *this / num;
    return *this;
  }
  bool operator==(const Matrix &mat) const {
    bool f = true;
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < ColumnsNumber(); ++j) {
        f &= matrix_[i][j] == mat(i, j);
      }
    }
    return f;
  }
  bool operator!=(const Matrix &mat) const { return !(*this == mat); }
};

template <typename T, const size_t Row, const size_t Col>
Matrix<T, Row, Col> operator*(int num, const Matrix<T, Row, Col> mat) {
  return mat * num;
}

template <typename T, const size_t Row, const size_t Col>
std::ostream &operator<<(std::ostream &sout, const Matrix<T, Row, Col> &mat) {
  for (size_t i = 0; i < Row; ++i) {
    for (size_t j = 0; j + 1 < Col; ++j) {
      sout << mat(i, j) << ' ';
    }
    sout << mat(i, Col - 1) << '\n';
  }
  return sout;
}

template <typename T, const size_t Row, const size_t Col>
std::istream &operator>>(std::istream &sin, Matrix<T, Row, Col> &mat) {
  for (size_t i = 0; i < Row; ++i) {
    for (size_t j = 0; j < Col; ++j) {
      T a;
      sin >> a;
      mat(i, j) = a;
    }
  }
  return sin;
}
template <typename T, const size_t Row, const size_t Column>
Matrix<T, Column, Row> GetTransposed(const Matrix<T, Row, Column> &mat) {
  const size_t col = mat.ColumnsNumber();
  const size_t row = mat.RowsNumber();
  Matrix<T, Column, Row> temp;
  for (size_t i = 0; i < col; ++i) {
    for (size_t j = 0; j < row; ++j) {
      temp(i, j) = mat(j, i);
    }
  }
  return temp;
}
#endif