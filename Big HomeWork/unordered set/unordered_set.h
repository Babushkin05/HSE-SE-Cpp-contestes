#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#include <functional>
#include <iterator>
#include <list>
#include <type_traits>
#include <utility>
#include <vector>

template <typename T>
class UnorderedSet {
 private:
  std::vector<std::list<T>> data_;
  size_t cnt_;

 public:
  UnorderedSet() : cnt_(0) {
  }

  explicit UnorderedSet(size_t size) : data_(size), cnt_(0) {
  }

  UnorderedSet(const UnorderedSet &other) = default;

  UnorderedSet(UnorderedSet &&other) : data_(std::move(other.data_)), cnt_(other.cnt_) {
    other.data_.clear();
    other.cnt_ = 0;
  }

  UnorderedSet &operator=(const UnorderedSet &other) = default;

  UnorderedSet<T> &operator=(UnorderedSet &&other) {
    data_ = std::move(other.data_);
    cnt_ = other.cnt_;
    other.cnt_ = 0;
    return *this;
  }

  bool Find(const T &val) const {
    if (data_.empty()) {
      return false;
    }
    size_t index = 0;
    std::hash<T> hasher;
    index = hasher(val) % data_.size();
    for (auto it = data_[index].begin(); it != data_[index].end(); it++) {
      if (*it == val) {
        return true;
      }
    }
    return false;
  }

  void Insert(T &&val) {
    if (Find(val)) {
      return;
    }
    if (cnt_ + 1 > data_.size()) {
      std::vector<std::list<T>> new_data;
      if (data_.empty()) {
        new_data.resize(1);
      } else {
        new_data.resize(data_.size() * 2);
      }
      std::hash<T> hasher;
      for (size_t i = 0; i < data_.size(); i++) {
        while (!data_[i].empty()) {
          auto it = data_[i].begin();
          size_t vs = hasher(*it) % new_data.size();
          new_data[vs].splice(new_data[vs].begin(), data_[i], it);
        }
      }
      data_ = std::move(new_data);
    }
    std::hash<T> hasher;
    data_[hasher(val) % data_.size()].push_front(val);
    cnt_++;
  }

  void Insert(const T &val) {
    if (Find(val)) {
      return;
    }
    if (cnt_ + 1 > data_.size()) {
      std::vector<std::list<T>> new_data;
      if (data_.empty()) {
        new_data.resize(1);
      } else {
        new_data.resize(data_.size() * 2);
      }
      std::hash<T> hasher;
      for (size_t i = 0; i < data_.size(); i++) {
        while (!data_[i].empty()) {
          auto it = data_[i].begin();
          size_t vs = hasher(*it) % new_data.size();
          new_data[vs].splice(new_data[vs].begin(), data_[i], it);
        }
      }
      data_ = std::move(new_data);
    }
    std::hash<T> hasher;
    data_[hasher(val) % data_.size()].push_front(val);
    cnt_++;
  }

  template <class Iterator,
            class = std::enable_if_t<std::is_base_of_v<typename std::forward_iterator_tag,
                                                       typename std::iterator_traits<Iterator>::iterator_category>>>
  UnorderedSet(Iterator begin, Iterator end) : UnorderedSet() {
    for (auto it = begin; it != end; it++) {
      Insert(*it);
    }
  }

  void Erase(const T &val) {
    size_t index = 0;
    std::hash<T> hasher;
    index = hasher(val) % data_.size();
    for (auto it = data_[index].begin(); it != data_[index].end(); it++) {
      if (*it == val) {
        data_[index].erase(it);
        cnt_--;
        break;
      }
    }
  }

  size_t Size() const {
    return cnt_;
  }

  size_t BucketCount() const {
    return data_.size();
  }

  size_t BucketSize(size_t id) const {
    if (id >= data_.size()) {
      return 0;
    }
    return data_[id].size();
  }

  size_t Bucket(const T &val) const {
    if (data_.empty()) {
      return 0;
    }
    std::hash<T> hasher;
    size_t index = hasher(val) % data_.size();
    return index;
  }

  double LoadFactor() const {
    if (data_.empty()) {
      return 0;
    }
    return static_cast<double>(cnt_) / data_.size();
  }

  void Rehash(size_t new_bucket_count) {
    if (new_bucket_count == data_.size() || new_bucket_count < cnt_) {
      return;
    }
    std::vector<std::list<T>> new_data(new_bucket_count);
    std::hash<T> hasher;
    if (new_bucket_count == 0) {
      data_ = std::move(new_data);
      return;
    }
    for (auto &bucket : data_) {
      while (!bucket.empty()) {
        auto it = bucket.begin();
        size_t new_index = hasher(*it) % new_data.size();
        new_data[new_index].splice(new_data[new_index].begin(), bucket, it);
      }
    }
    data_ = std::move(new_data);
  }

  void Reserve(size_t new_bucket_count) {
    if (new_bucket_count > data_.size()) {
      Rehash(new_bucket_count);
    }
  }

  bool Empty() const {
    return cnt_ == 0;
  }

  void Clear() {
    for (auto &it : data_) {
      it.clear();
    }
    cnt_ = 0;
  }
};

#endif