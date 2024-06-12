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
  const size_t RowsNumber() const { return Row; }
  const size_t ColumnsNumber() const { return Column; }

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

  const Matrix operator+(const Matrix &mat) const {
    T temp[RowsNumber()][ColumnsNumber()];
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < ColumnsNumber(); ++j) {
        temp[i][j] = matrix_[i][j] + mat(i, j);
      }
    }
    return Matrix<T, Row, Column>{std::move(temp)};
  }
  Matrix operator-(const Matrix &mat) const {
    T temp[RowsNumber()][ColumnsNumber()];
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < ColumnsNumber(); ++j) {
        temp[i][j] = matrix_[i][j] - mat(i, j);
      }
    }
    return Matrix<T, Row, Column>{std::move(temp)};
  }

  template <const size_t Col2>
  const Matrix<T, Row, Col2>
  operator*(const Matrix<T, Column, Col2> &mat) const {
    T temp[RowsNumber()][Col2];
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < mat.ColumnsNumber(); ++j) {
        int s = 0;
        for (size_t k = 0; k < ColumnsNumber(); ++k) {
          s += matrix_[i][k] * mat(k, j);
        }
        temp[i][j] = s;
      }
    }
    return Matrix<T, Row, Col2>{std::move(temp)};
  }

  Matrix &operator+=(const Matrix &mat) {
    *this = *this + mat;
    return *this;
  }

  Matrix &operator-=(const Matrix &mat) {
    *this = *this - mat;
    return *this;
  }
  template <const size_t Col2>
  Matrix &operator*=(const Matrix<T, Column, Col2> &mat) {
    *this = *this * mat;
    return *this;
  }
  Matrix operator*(const T num) const {
    T temp[RowsNumber()][ColumnsNumber()];
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < ColumnsNumber(); ++j) {
        temp[i][j] = num * matrix_[i][j];
      }
    }
    return Matrix<T, Row, Column>{std::move(temp)};
  }

  Matrix &operator*=(const T num) {
    *this = *this * num;
    return *this;
  }

  Matrix operator/(const T num) {
    T temp[RowsNumber()][ColumnsNumber()];
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < ColumnsNumber(); ++j) {
        temp[i][j] = matrix_[i][j] / num;
      }
    }
    return Matrix<T, Row, Column>{std::move(temp)};
  }
  Matrix &operator/=(const T num) {
    *this = *this / num;
    return *this;
  }
  bool operator==(const Matrix &mat) {
    if (RowsNumber() != mat.RowsNumber() ||
        ColumnsNumber() != mat.ColumnsNumber()) {
      throw MatrixOutOfRange{};
    }
    bool f = true;
    for (size_t i = 0; i < RowsNumber(); ++i) {
      for (size_t j = 0; j < ColumnsNumber(); ++j) {
        f &= matrix_[i][j] == mat(i, j);
      }
    }
    return f;
  }
  bool operator!=(const Matrix &mat) { return !(this == mat); }
};

template <typename T, const size_t Row, const size_t Col>
Matrix<T, Row, Col> &operator*(const T num, const Matrix<T, Row, Col> mat) {
  return mat * num;
}

template <typename T, const size_t Row, const size_t Col>
std::ostream &operator<<(std::ostream &sout, const Matrix<T, Row, Col> &mat) {
  for (size_t i = 0; i < Row; ++i) {
    for (size_t j = 0; j < Col; ++j) {
      sout << mat(i, j) << ' ';
    }
    sout << '\n';
  }
  return sout;
}

template <typename T, const size_t Row, const size_t Col>
std::istream &operator>>(std::istream &sin, const Matrix<T, Row, Col> &mat) {
  for (size_t i = 0; i < Row; ++i) {
    for (size_t j = 0; j < Col; ++j) {
      sin >> mat(i, j);
    }
  }
}
template <typename T, const size_t Row, const size_t Column>
Matrix<T, Column, Row> GetTransposed(const Matrix<T, Row, Column> &mat) {
  const size_t col = mat.ColumnsNumber();
  const size_t row = mat.RowsNumber();
  T temp[col][row];
  for (size_t i = 0; i < col; ++i) {
    for (size_t j = 0; j < row; ++j) {
      temp[i][j] = mat(j, i);
    }
  }
  return Matrix<T, col, row>{std::move(temp)};
}
#endif