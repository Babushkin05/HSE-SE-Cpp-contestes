#ifndef ARRAY_H
#define ARRAY_H
#include <exception>
#define ARRAY_TRAITS_IMPLEMENTED

class ArrayOutOfRange : std::runtime_error {
public:
  ArrayOutOfRange() : std::runtime_error("Argument out of range") {}
};

template <typename T, size_t N> class Array {
public:
  T data_[N];

  T &operator[](size_t i) { return data_[i]; }
  const T &operator[](size_t i) const { return data_[i]; }
  T &At(size_t i) {
    if (i >= N) {
      throw ArrayOutOfRange{};
    }
    return data_[i];
  }

  T &Front() { return data_[0]; }
  const T &Front() const { return data_[0]; }

  T &Back() { return data_[N - 1]; }

  const T &Back() const { return data_[N - 1]; }

  T *Data() { return &(data_[0]); }

  const T *Data() const { return &(data_[0]); }

  size_t Size() const { return N; }

  bool Empty() const { return N == 0; }

  void Fill(const T &value) {
    for (size_t i = 0; i < N; ++i) {
      data_[i] = value;
    }
  }

  void Swap(Array<T, N> &arr) {
    for (size_t i = 0; i < N; ++i) {
      std::swap(data_[i], arr[i]);
    }
  }
};

template <typename T> size_t GetSize(T) { return 0; }
template <typename T, size_t N> size_t GetSize(T (&)[N]) { return N; }

template <typename T> size_t GetRank(T) { return 0; }
template <typename T, size_t N> size_t GetRank(T (&elem)[N]) {
  return 1 + GetRank(elem[0]);
}

template <typename T> size_t GetNumElements(T) { return 1; }
template <typename T, size_t N> size_t GetNumElements(T (&elem)[N]) {
  return N * GetNumElements(elem[0]);
}

#endif