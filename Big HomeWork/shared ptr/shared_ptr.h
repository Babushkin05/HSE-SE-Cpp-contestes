#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#define WEAK_PTR_IMPLEMENTED

#include <algorithm>
#include <cstddef>

class BadWeakPtr {};

template <typename T> class WeakPtr;

template <typename T> class SharedPtr {
  template <typename V> friend class WeakPtr;

private:
  size_t *cnt_;
  size_t *wcnt_;
  T *obj_;
  void Disjoined() {
    if (cnt_ == nullptr) {
      return;
    }
    *cnt_ = *cnt_ - 1;
    if (*cnt_ == 0) {
      if (*wcnt_ == 0) {
        delete cnt_;
        delete wcnt_;
      }
      delete obj_;
    }
  }

public:
  SharedPtr() : cnt_(nullptr), wcnt_(nullptr), obj_(nullptr) {}

  ~SharedPtr() { Disjoined(); }

  SharedPtr(const WeakPtr<T> &other) // NOLINT
      : cnt_(other.cnt_), wcnt_(other.wcnt_), obj_(other.obj_) {
    if (other.Expired()) {
      throw BadWeakPtr{};
    }
    *cnt_ = *cnt_ + 1;
  }

  SharedPtr(std::nullptr_t) : SharedPtr() {} // NOLINT

  SharedPtr(T *obj) // NOLINT
      : cnt_(new size_t(1)), wcnt_(new size_t(0)), obj_(obj) {}

  SharedPtr(const SharedPtr &other)
      : cnt_(other.cnt_), wcnt_(other.wcnt_), obj_(other.obj_) {
    if (cnt_ != nullptr) {
      *cnt_ = *cnt_ + 1;
    }
  }

  SharedPtr(SharedPtr &&other) noexcept
      : cnt_(other.cnt_), wcnt_(other.wcnt_), obj_(other.obj_) {
    other.cnt_ = nullptr;
    other.wcnt_ = nullptr;
    other.obj_ = nullptr;
  }

  SharedPtr &operator=(const SharedPtr &other) {
    if (other.obj_ == obj_) {
      return *this;
    }
    Disjoined();
    cnt_ = other.cnt_;
    wcnt_ = other.wcnt_;
    obj_ = other.obj_;
    if (cnt_ != nullptr) {
      *cnt_ = *cnt_ + 1;
    }
    return *this;
  }

  SharedPtr<T> &operator=(SharedPtr &&other) noexcept {
    if (&other == this) {
      return *this;
    }
    if (other.obj_ == obj_) {
      *cnt_ = *cnt_ - 1;
      other.cnt_ = nullptr;
      other.wcnt_ = nullptr;
      other.obj_ = nullptr;
      return *this;
    }

    Disjoined();
    cnt_ = other.cnt_;
    wcnt_ = other.wcnt_;
    obj_ = other.obj_;
    other.cnt_ = nullptr;
    other.wcnt_ = nullptr;
    other.obj_ = nullptr;
    return *this;
  }

  T &operator*() const { return *obj_; }

  T *operator->() const { return obj_; }

  explicit operator bool() const { return obj_ != nullptr; }

  void Reset(T *ptr = nullptr) {
    Disjoined();
    obj_ = ptr;
    if (ptr != nullptr) {
      cnt_ = new size_t(1);
      wcnt_ = new size_t(0);
    } else {
      cnt_ = nullptr;
      wcnt_ = nullptr;
    }
  }

  void Swap(SharedPtr &other) noexcept {
    std::swap(cnt_, other.cnt_);
    std::swap(wcnt_, other.wcnt_);
    std::swap(obj_, other.obj_);
  }

  T *Get() const { return obj_; }

  size_t UseCount() const {
    if (cnt_ == nullptr) {
      return 0;
    }
    return *cnt_;
  }

  SharedPtr<T> &operator=(T *obj) {
    Disjoined();
    obj_ = obj;
    if (obj_ != nullptr) {
      cnt_ = new size_t(1);
      wcnt_ = new size_t(0);
    } else {
      cnt_ = nullptr;
      wcnt_ = nullptr;
    }
    return *this;
  }
};

template <typename T> class WeakPtr {
  template <typename V> friend class SharedPtr;

private:
  size_t *cnt_;
  size_t *wcnt_;
  T *obj_;
  void Disjoined() {
    if (cnt_ == nullptr) {
      return;
    }
    *wcnt_ = *wcnt_ - 1;
    if (*cnt_ == 0 && *wcnt_ == 0) {
      delete cnt_;
      delete wcnt_;
    }
  }

public:
  WeakPtr() : cnt_(nullptr), wcnt_(nullptr), obj_(nullptr) {}

  ~WeakPtr() { Disjoined(); }

  WeakPtr(const SharedPtr<T> &other) // NOLINT
      : cnt_(other.cnt_), wcnt_(other.wcnt_), obj_(other.obj_) {
    if (cnt_ == nullptr) {
      return;
    }
    *wcnt_ = *wcnt_ + 1;
  }

  WeakPtr(const WeakPtr &other)
      : cnt_(other.cnt_), wcnt_(other.wcnt_), obj_(other.obj_) {
    if (cnt_ == nullptr) {
      return;
    }
    *wcnt_ = *wcnt_ + 1;
  }

  WeakPtr(WeakPtr &&other) noexcept
      : cnt_(other.cnt_), wcnt_(other.wcnt_), obj_(other.obj_) {
    other.cnt_ = nullptr;
    other.wcnt_ = nullptr;
    other.obj_ = nullptr;
  }

  WeakPtr<T> &operator=(const WeakPtr &other) {
    if (other.obj_ == obj_) {
      return *this;
    }
    Disjoined();
    cnt_ = other.cnt_;
    wcnt_ = other.wcnt_;
    obj_ = other.obj_;
    if (cnt_ != nullptr) {
      *wcnt_ = *wcnt_ + 1;
    }
    return *this;
  }

  WeakPtr<T> &operator=(WeakPtr &&other) {
    if (&other == this) {
      return *this;
    }
    if (other.obj_ == obj_) {
      *wcnt_ = *wcnt_ - 1;
      other.cnt_ = nullptr;
      other.wcnt_ = nullptr;
      other.obj_ = nullptr;
      return *this;
    }
    Disjoined();
    cnt_ = other.cnt_;
    wcnt_ = other.wcnt_;
    obj_ = other.obj_;
    other.cnt_ = nullptr;
    other.wcnt_ = nullptr;
    other.obj_ = nullptr;
    return *this;
  }

  void Swap(WeakPtr<T> &other) {
    std::swap(cnt_, other.cnt_);
    std::swap(wcnt_, other.wcnt_);
    std::swap(obj_, other.obj_);
  }

  void Reset() {
    Disjoined();
    cnt_ = nullptr;
    wcnt_ = nullptr;
    obj_ = nullptr;
  }

  size_t UseCount() const {
    if (cnt_ == nullptr) {
      return 0;
    }
    return *cnt_;
  }

  bool Expired() const {
    if (cnt_ == nullptr) {
      return true;
    }
    return *cnt_ == 0;
  }

  SharedPtr<T> Lock() const {
    if (Expired()) {
      return {};
    }
    return {*this};
  }
};

template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args &&...args) {
  return {new T(std::forward<Args>(args)...)};
}

#endif