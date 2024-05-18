#include "string_view.h"
#include <string>

StringView::StringView() : data_(nullptr), size_(0) {}

StringView::StringView(const char *data)
    : StringView::StringView(data, std::strlen(data)) {}

StringView::StringView(const char *data, size_t size)
    : data_(data), size_(size) {}

char StringView::operator[](size_t index) const { return this->data_[index]; }

char StringView::At(size_t index) const {
  if (index >= this->size_) {
    throw StringViewOutOfRange{};
  }
  return (*this)[index];
}

char StringView::Front() const {
  if (Empty()) {
    throw StringViewOutOfRange{};
  }
  return (*this)[0];
}

char StringView::Back() const {
  if (Empty()) {
    throw StringViewOutOfRange();
  }
  return (*this)[this->size_ - 1];
}

size_t StringView::Size() const { return this->size_; }

size_t StringView::Length() const { return this->Size(); }

bool StringView::Empty() const { return this->Size() == 0; }

const char *StringView::Data() const { return this->data_; }

void StringView::Swap(StringView &other) {
  std::swap(this->data_, other.data_);
  std::swap(this->size_, other.size_);
}

void StringView::RemovePrefix(size_t prefix_size) {
  this->data_ += prefix_size;
  this->size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  this->size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) const {
  if (pos >= this->size_) {
    throw StringViewOutOfRange{};
  }
  return StringView{this->data_ + pos, std::min(count, this->size_ - pos)};
}
