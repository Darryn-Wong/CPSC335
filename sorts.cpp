//
//  sorts.cpp
//
//  Created by William McCarthy on 267//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "utils.h"

#include "selection_sort.h"
#include "insertion_sort.h"
#include "shell_sort.h"

#include "merge_sort.h"
#include "quick_sort.h"
#include "heap_sort.h"

#include "random.h"

// #include "students.h"


#define ARGC_ERROR  1
#define FILE_ERROR 2
#define STRING_NUMBER_ERROR 3


void get_input(const std::string& msg, std::string& input) {
  char c;

  std::cout << msg;
  while (std::cin >> c) {
    if (isprint(c)) {
      input += c;
    }
  }
}

template <typename T>
void single_issorted_test(T* arr, size_t low, size_t high) {
  print("arr is: ", arr, low, high);
  std::cout << " -- is sorted: " << yes_or_no(is_sorted(arr, low, high)) << "\n";
}

template <typename T>
void single_issorted_test(T* arr, size_t n) { single_issorted_test(arr, 0, n); }

// template <typename T>
// void test_selection_sort(const std::string& msg, T* arr, size_t n) {
//   selection_sort<T> select_sort;
//   select_sort.sort(arr, n);
//   print(msg, arr, n);
//   std::cout << "\n";
// }

template <typename T, typename S>
void test_sort(const std::string& msg, T* arr, size_t n,
               const comparator<T>& comp, const S& sort) {
  sort.sort(arr, n, comp);
  print(msg, arr, n + 1);   // for heap_sort only
  std::cout << "\n";
}


void test_sorting_utilities() {
  std::cout << "beginning test_sorted()..........................................\n";
  int test1[] = { 72, 3, 25, 4, 26, 47 };
  int test2[] = { 18, 37, 44, 5, 12, 99 };
  int test3[] = { 86, 85, 74, 53, 36, 27 };

  std::string test_str1[] = { "three", "rings", "for", "the", "elven", "kings" };
  std::string test_str2[] = { "seven", "for", "the", "dwarf", "lords", "in", "their", "halls", "of", "stone" };
  std::string test_str3[] = { "nine", "for", "mortal", "men", "doomed", "to", "die" };


  single_issorted_test(test1, std::size(test1));                // NB: C++17 +
  single_issorted_test(test2, std::size(test2));
  single_issorted_test(test3, std::size(test3));
  std::cout << "\n";
  single_issorted_test(test_str1, std::size(test_str1));
  single_issorted_test(test_str2, std::size(test_str2));
  single_issorted_test(test_str3, std::size(test_str3));

  std::cout << "\n";
  single_issorted_test(test2, 2, std::size(test2));
  single_issorted_test(test_str2, 2, std::size(test_str2));

  std::cout << "\nsorting unsorted arrays now with selection_sort.........\n";
  fwd_comparator<int> fwd_comp_int;
  selection_sort<int> sel_sort;
  test_sort("test1 is now: ", test1, std::size(test1), fwd_comp_int, sel_sort);
  test_sort("test2 is now: ", test2, std::size(test2), fwd_comp_int, sel_sort);
  test_sort("test3 is now: ", test3, std::size(test3), fwd_comp_int, sel_sort);

  std::cout << "\nsorting unsorted arrays now with insertion_sort.........\n";
  rev_comparator<std::string> rev_str;
  insertion_sort<std::string> ins_sort;
  test_sort("\ntest_str1 is now: ", test_str1, std::size(test_str1), rev_str, ins_sort);
  test_sort("test_str2 is now: ", test_str2, std::size(test_str2), rev_str, ins_sort);
  test_sort("test_str3 is now: ", test_str3, std::size(test_str3), rev_str, ins_sort);

  std::cout << "..........................................ending test_sorted()\n\n";
}

template <typename T, typename S>
void test_sort_from_file(const std::string& msg, const std::string& filename,
                         const comparator<T>& comp, const S& sort) {
  std::ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw new std::invalid_argument("Could not open file ");
  }
  const size_t BUFFER_SIZE = 1000;
  std::string words[BUFFER_SIZE];
  std::fill(words, words + BUFFER_SIZE, "");
  size_t n = 0;

  std::string s = "";
  while (ifs >> s) {
    if (s != " ") { words[n++] = s; }
  }
  ifs.close();
  test_sort("\n\nAfter " + msg + " sorting, words is now: \n\n", words, n, comp, sort);

  std::cout << "\n\n";
}

void test_elementary_sorts(const std::string& filename) {
    test_sorting_utilities();

  test_sort_from_file("selection", filename, fwd_comparator<std::string>(), selection_sort<std::string>());
  test_sort_from_file("insertion", filename, fwd_comparator<std::string>(), insertion_sort<std::string>());
  test_sort_from_file("shell_sort", filename, fwd_comparator<std::string>(), shell_sort<std::string>());
}

void test_shuffle() {
    const int TINY = 10;
    int low = 30, high = 50;
    int buf[TINY];
    std::fill(buf, buf + TINY, 0);
    std_random<int>::generate_uniform_int(buf, TINY, low, high);
    test_sort("random buffer: ", buf, TINY, fwd_comparator<int>(), shell_sort<int>());

    for (int i = 0; i < TINY; ++i) {
      buf[i] = i;
    }
    print("\nunshuffled: ", buf, TINY);
//    std_random<int>::shuffle(buf, TINY);
    std_random<int>::shuffle_alternate(buf, TINY);

    print("\n  shuffled: ", buf, TINY);
    std::cout << "\n\n";

  freopen("words3.txt", "r", stdin);
  std::string s;
  int len = 0;
  std::string cards[100];

  while (std::cin >> s) {
    cards[len++] = s;
    std::cout << s << " ";
  }
  print("\nunshuffled: ", cards, len);
  std_random<std::string>::shuffle(cards, len);
  print("\n\n  shuffled: ", cards, len);
  std::cout << "\n\n";
}

#include <cstdio>

//------------------------------------------------------------------------------
int main(int argc, const char * argv[]) {
  // test_elementary_sorts("words3.txt");
//  test_shuffle();

  // test_sort_from_file("merge", "words3.txt", fwd_comparator<std::string>(), merge_sort<std::string>());
  //
  // test_sort_from_file("merge_bottom_up -- reversed", "words3.txt", rev_comparator<std::string>(), merge_bu_sort<std::string>());
 // test_sort_from_file("merge_bottom_up -- reversed", "words3.txt", rev_comparator<std::string>(), merge_bu_sort<std::string>());
 // test_sort_from_file("quick_sort_3way", "words3.txt", fwd_comparator<std::string>(), quick_sort_3way<std::string>());
 // test_sort_from_file("quick_sort", "words3.txt", fwd_comparator<std::string>(), quick_sort<std::string>());


  //  student::run_tests();

 test_sort_from_file("heap_sort", "sort_example.txt", fwd_comparator<std::string>(), heap<std::string>());

 test_sort_from_file("heap_sort", "words3.txt", fwd_comparator<std::string>(), heap<std::string>());
 // test_sort_from_file("heap_sort", "words3.txt", fwd_comparator<std::string>(), max_pq_heap<std::string>());
  return 0;
}
