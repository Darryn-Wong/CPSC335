template <typename T>
class merge_sort {
public:
 // comp=fwd_comparator<T>()
 static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
   T* aux = new T[n];
   sort(arr, aux, 0, n - 1, comp);
 }

private:
 static const int CUTOFF = 7;
 static void sort(T* arr, T* aux, size_t low, size_t high, const comparator<T>& comp) {
   if (high <= low) return;
   int mid = low + (high - low)/2;
   sort(arr,aux, low, mid,comp);
   sort(arr,aux, mid+1, high,comp);
   merge(arr,aux, low, mid, high,comp);
 }
 static void merge(T* arr, T* aux, size_t low, size_t mid, size_t high, const comparator<T>& comp) {
  int i = low, j = mid+1;
  for (int k = low; k <= high; ++k) // Copy a[lo..hi] to aux[lo..hi].
    aux[k] = arr[k];
  for (int k = low; k <= high; ++k) { // Merge back to a[lo..hi].
    if (i > mid) arr[k] = aux[j++];
    else if (j > high ) arr[k] = aux[i++];
    else if (aux[j] < aux[i]) arr[k] = aux[j++];
    else arr[k] = aux[i++];
  }
 }
};
template <typename T>
class merge_bu_sort {
public:
    static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
      T* aux = new T[n];
      for(size_t subsize = 1; subsize < n; subsize = subsize + subsize) {
        for(size_t low = 0; low < n - subsize; low += subsize + subsize) {
            merge(arr, aux, low, low + subsize - 1, std::min(low + subsize + subsize - 1, n - 1), comp);
        }
      }
    }
private:
    static void merge(T* arr, T* aux, size_t low, size_t mid, size_t high, const comparator<T>& comp) {
      size_t i = low;
      size_t j = mid + 1;

      for(size_t k = low; k <= high; ++k)
        aux[k] = arr[k];
      for(size_t k = low; k <= high; ++k) {
        if(i > mid) arr[k] = aux[j++];
        else if(j > high) arr[k] = aux[i++];
        else if(aux[j] > aux[i]) arr[k] = aux[j++];
        else arr[k] = aux[i++];
      }
    }
};
