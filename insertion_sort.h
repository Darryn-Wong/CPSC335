//
//  insertion_sort.h
//  stacks_queues_bags
//
//  Created by William McCarthy on 108//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef insertion_sort_h
#define insertion_sort_h

#include <cassert>
#include "utils.h"


template <typename T>
class insertion_sort {
public:                       // 2 3 6 5 4 
  static void sort(T* arr, size_t low, size_t high, const comparator<T>& comp=fwd_comparator<T>()) {
    for (size_t i = low; i < high; ++i) {
      for (size_t j = i; j > 0; --j) {
        if (less(arr[j], arr[j - 1], comp)) { exchange(arr, j, j - 1); }
        else { break; }
      }
    }
    assert(is_sorted(arr, low, high, comp));
  }
  static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()) { sort(arr, 0, n - 1, comp); }


//  static void sort(T* arr, size_t n, const comparator<T>& comp=comparator<T>()) { sort(arr, n - 1, comp); }
//    for (size_t i = 0; i < n; ++i) {
//      for (size_t j = i; j > 0; --j) {
//        if (less(arr[j], arr[j - 1], comp)) { exchange(arr, j, j - 1); }
//        else { break; }
//      }
//    }
//    assert(is_sorted(arr, n, comp));
//  }

//  static void sort(T* arr, size_t n) {
//    for (size_t i = 0; i < n; ++i) {
//      for (size_t j = i; j > 0; --j) {
//        if (less(arr[j], arr[j - 1])) { exchange(arr, j, j - 1); }
//        else { break; }
//      }
//    }
//    assert(is_sorted(arr, n));
//  }
};


#endif /* insertion_sort_h */
