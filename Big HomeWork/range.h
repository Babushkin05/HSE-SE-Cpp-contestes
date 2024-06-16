#define REVERSE_RANGE_IMPLEMENTED
#ifndef RANGE_H
#define RANGE_H
#include <cstddef>
#include <exception>
#include <iterator>

class Range {
private:
  int beg_;
  int end_;
  int step_;

public:
  explicit Range(int end) : Range(0, end, 1) {}
  Range(int beg, int end) : Range(beg, end, 1) {}
  Range(int beg, int end, int step) : beg_(beg), end_(end), step_(step) {}

  struct Iterator {
  private:
    int beg_t_;
    int end_t_;
    int step_t_;
    int cur_;

  public:
    Iterator(int beg, int end, int step, int cur)
        : beg_t_(beg), end_t_(end), step_t_(step), cur_(cur) {}

    Iterator &operator++() {
      cur_ += step_t_;
      return *this;
    }

    Iterator &operator--() {
      cur_ -= step_t_;
      return *this;
    }

    int &operator*() { return cur_; }

    int operator*() const { return cur_; }

    friend bool operator!=(const Iterator &a, const Iterator &b) {
      if ((a.end_t_ - a.beg_t_) * a.step_t_ <= 0) {
        return false;
      }
      if (a.beg_t_ < a.end_t_) {
        return a.cur_ < b.cur_;
      }
      return a.cur_ > b.cur_;
    }
  };

  Iterator begin() const { return Iterator{beg_, end_, step_, beg_}; } // NOLINT

  Iterator end() const { return Iterator{beg_, end_, step_, end_}; }   // NOLINT

  Iterator rbegin() const {                                            // NOLINT
    return Iterator{end_, beg_, -step_,
                    beg_ +
                        (std::abs(end_ - beg_) + std::abs(step_) - 1) /
                            std::max(1, std::abs(step_)) * step_ -
                        step_};
  }
  
  Iterator rend() const { // NOLINT
    return Iterator{end_, beg_, -step_, beg_ - step_};
  }
};

#endif