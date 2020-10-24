#define MIN_CAPACITY 3
#include "array.h"
#include "utils.h"
template <typename T>
class heap {
private:
  Heap();
  static bool less(T* pq, int i, int j, const comparator<T>& comp) {
      return pq[i-1] < pq[j-1];
  }

  static void exch(T* pq, int i, int j) {
      T swap = pq[i-1];
      pq[i-1] = pq[j-1];
      pq[j-1] = swap;
  }
  static void sink(T* pq, int k, int n,const comparator<T>& comp) {
      while (2*k <= n) {
          int j = 2*k;
          // if (j < n && less(pq, j, j+1)) j++;
          // if (!less(pq, k, j)) break;
          // exch(pq, k, j);
          // k = j;
          if (j < n && less(pq, j, j+1,comp)) j++;
          if (!less(pq, k, j,comp)) break;
          exch(pq, k, j);
          k = j;
      }
  }
  // print array to standard output
  static void show(T* a, size_t n) {
      for (size_t i = 0; i < n; i++) {
          std::cout << a[i];
      }
  }
public:
  static void sort(T* pq, size_t n,const comparator<T>& comp=fwd_comparator<T>()) {
      for (int k = n/2; k >= 1; k--)
          sink(pq, k, n,comp);
      int k = n;
      while (k > 1) {
          exch(pq, 1, k--);
          sink(pq, 1, k,comp);
      }
  }
};

template <typename T>
class max_pq_heap {
public:
  max_pq_heap() : max_pq_heap(MIN_CAPACITY_) { }
  max_pq_heap(const comparator<T>& compar) : max_pq_heap(MIN_CAPACITY, compar) { }
  max_pq_heap(size_t capacity, const comparator<T>& compar)
  : pq_(capacity + 1), comp(compar) { pq_.push_back(T()); }  // make space for skipped-over 0 entry

  max_pq_heap(const std::initializer_list<T>& li, const comparator<T>& compar)
  : max_pq_heap(li.size(), compar) {
    for (const T& el : li) {
      if (el != "-") { insert(el);
      } else { std::cout << del_max() << " "; }
    }
    std::cout << "\t(" << size() << " left on the heap)\n\n";\
  }
  bool empty() const { return pq_.size() == 1; }   // leaves 0 index empty
  size_t size() const { return pq_.size() - 1; }   // ditto
  void insert(const T& value) {
    pq_.push_back(value);
    swim(size());
  }
  T del_max() {
    T maximum = pq_[1];
    size_t n = size();

    exchange(1, n);
    pq_.pop_back();
    sink(1);
    pq_[n] = T();
    return maximum;
  }
  void swim(size_t k) {
    while (k > 1 && less(k / 2, k)) {
      exchange(k, k / 2);
      k /= 2;
    }
  }
  void sink(size_t k) {
    size_t n = size();

    while (2 * k <= n) {
      size_t j = 2 * k;
      if (j < n && less(j, j + 1)) { ++j; }
      if (!less(k, j)) { break; }

      exchange(k, j);
      k = j;
    }
  }
  friend std::ostream& operator<<(std::ostream& os, const max_pq_heap& maxpq) {
    if (maxpq.empty()) { return os << "max_pq_heap is empty\n"; }
    return os << maxpq.pq_ << "\n";
  }
private:
  static const size_t MIN_CAPACITY_;
  void exchange(size_t i, size_t j) {
    T temp = pq_[i];
    pq_[i] = pq_[j];
    pq_[j] = temp;
  }
  bool less(size_t i, size_t j) {
    return ::less(pq_[i], pq_[j], comp);
  }
  array_<T> pq_;                // uses expandable array from array.h, not std::array<T>
  const comparator<T>& comp;
};
