#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

class StringView {
private:
  const char *data_;
  size_t size_;

public:
  StringView();
  StringView(const char *); // NOLINT;
  StringView(const char *, size_t);
  char operator[](size_t index) const;
  char At(size_t index) const;
  char Front() const;
  char Back() const;
  size_t Size() const;
  size_t Length() const;
  bool Empty() const;
  const char *Data() const;
  void Swap(StringView &);
  void RemovePrefix(size_t prefix_size);
  void RemoveSuffix(size_t suffix_size);
  StringView Substr(size_t pos, size_t count = -1) const;
};

class StringViewOutOfRange : public std::runtime_error {
public:
  StringViewOutOfRange() : std::runtime_error("Index out of range") {}
};

#endif