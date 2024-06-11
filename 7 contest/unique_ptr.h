#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <utility>

template <typename T> class UniquePtr {
private:
  T *data_{};

public:
  UniquePtr() : data_(nullptr) {}
  explicit UniquePtr(T *ptr) : data_(ptr) {}
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr(UniquePtr &&moved) noexcept : data_(std::move(moved.data_)) {
    moved.data_ = nullptr;
  }
  UniquePtr &operator=(const UniquePtr&) = delete;
  UniquePtr &operator=(UniquePtr &&moved) noexcept {
    if (&moved != this) {
      delete data_;
      data_ = std::move(moved.data_);
      moved.data_ = nullptr;
    }
    return *this;
  }
  T *Release() {
    T *to_return = data_;
    data_ = nullptr;
    return to_return;
  }
  UniquePtr &Reset(T *ptr = nullptr) {
    delete data_;
    data_ = ptr;
    return *this;
  }
  void Swap(UniquePtr &other) {
    UniquePtr temp{std::move(other)};
    other = std::move(*this);
    *this = std::move(temp);
  }
  T *Get() const { return data_; }
  T &operator*() const { return *data_; }
  T *operator->() const { return data_; }
  explicit operator bool() const { return data_ != nullptr; }
  ~UniquePtr() {
    delete data_;
  }
};

#endif