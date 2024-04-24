#ifndef IS_SORTED_UNTIL
#define IS_SORTED_UNTIL

template <class T> 
T IsSortedUntil(T begin, T end) {
  for (T i = begin + 1; i < end; ++i) {
    if (*i < *(i - 1)) {
      return i;
    }
  }
  return end;
}
#endif