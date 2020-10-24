//
//  quick_sort.h
//  sorts
//
//  Created by William McCarthy on 138//20.
//

#ifndef quick_sort_h
#define quick_sort_h

#include <cassert>
#include "utils.h"

#include "random.h"

//-----------------------------------------------------------------------
template <typename T>
class quick_sort {
public:
  static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
    std_random<T>::shuffle(arr, n);
    sort(arr, 0, n - 1, comp);
  }

  static T select(T* arr, size_t n, size_t k, const comparator<T>& comp=fwd_comparator<T>()) {
    std_random<T>::shuffle(arr, n);
    size_t low = 0, high = n - 1;
    while (high > low) {
      size_t j = partition(arr, low, high, comp);
      if (j < k)      { low = j + 1; }
      else if (j > k) { high = (j == 0 ? 0 : j - 1); }
      else            { return arr[k]; }
    }
    return arr[k];
  }

private:
  static const int CUTOFF_ = 10;

  static void sort(T* arr, size_t low, size_t high, const comparator<T>& comp) {
    if (high <= low) { return; }
    size_t j = partition(arr, low, high, comp);
    sort(arr, low, (j == 0 ? 0 : j - 1), comp);
    sort(arr, j + 1, high, comp);
  }

  static size_t partition(T* arr, size_t low, size_t high, const comparator<T>& comp) {
    size_t i = low, j = high + 1;
    while (true) {
      while (less(arr[++i], arr[low], comp)) {
        if (i == high) { break; }
      }
      while (less(arr[low], arr[--j], comp)) {
        if (j == low) { break; }
      }
      if (i >= j) { break; }
      exchange(arr, i, j);
    }
    exchange(arr, low, j);
    return  j;
  }
};

//-----------------------------------------------------------------------
template <typename T>
class quick_sort_3way {
  static const int CUTOFF_ = 7;

public:
  static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
    std_random<T>::shuffle(arr, n);
    sort(arr, 0, n - 1, comp);
  }

private:
  static void sort(T* arr, size_t low, size_t high, const comparator<T>& comp) {
    if (high <= low) { return; }
    insertion_sort<T> insert;
    if (high <= low + CUTOFF_ - 1) {
      insert.sort(arr, low, high, comp);
      return;
    }
    size_t lt = low, i = low + 1, greater = high;
    T value = arr[low];
    while (i <= greater) {
      if (less(arr[i], value, comp)) {
        exchange(arr, lt++, i++);
      }
      else if (less(value, arr[i], comp)) {
        exchange(arr, i, greater);  if (greater != 0) { --greater; }  }
      else { ++i; }
    }
    sort(arr, low, (lt == 0 ? 0 : lt - 1), comp);
    sort(arr, greater + 1, high, comp);
  }
};

#endif /* quick_sort_h */
