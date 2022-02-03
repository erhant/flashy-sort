#include "util.hpp"

/**
 * @brief Creates a new array of given type with values in range [min, max]
 *
 * @tparam T: type of array
 * @param size: size of the array
 * @param min lower bound for random value
 * @param max upper bound for random value
 * @return array pointer
 */
template <typename T>
T* create_array(const int size, const double min, const double max) {
  T* arr = new T[size];
  for (int i = 0; i < size; i++) {
    arr[i] = T((((double)rand() / RAND_MAX) * (max - min)) + min);
  }
  return arr;
}

/**
 * @brief Checks if an array is sorted in ascending order.
 *
 * @tparam T: type of array
 * @param arr: array pointer
 * @param size: size of the array
 * @return true if sorted, false otherwise
 */
template <typename T>
bool isSorted(T* arr, int size) {
  for (int i = 0; i < size - 1; i++)
    if (arr[i] > arr[i + 1]) return false;
  return true;
}

/**
 * @brief Print contents of an array
 *
 * @tparam T: type of array
 * @param arr: array pointer
 * @param size: size of the array
 * @param title extra title for the printing
 */
template <typename T>
void print_array(T* arr, int size, const char* title) {
  cout << title << endl;
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}
