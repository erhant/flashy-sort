#include "flashysort.hpp"

/**
 * @brief Sort an array of numeric values using Flashier Sort.
 * Uses an extra array to calculate collisions, and uses one more array to write
 * the nearly-sorted array. Then, that array is copied back to go into insertion
 * sort.
 *
 * @tparam T: type of the array
 * @param arr: array pointer
 * @param n: size of the array
 */
template <typename T>
void flashy_sort(T *arr, const int n) {
  int pos, i, j;
  T tmp;

  // 1 - Find min and max, place max values at the end [ O(n) time, O(1) space ]
  T arrmin = arr[0];
  T arrmax = arr[0];
  int maxctr = 0;
  for (i = 1; i < n; ++i) {
    if (arr[i] > arrmax) arrmax = arr[i];
    if (arr[i] < arrmin) arrmin = arr[i];
  }
  if (arrmin == arrmax) return;  // max=min means sorted already
  for (i = 0; i < n - maxctr; ++i) {
    if (arr[i] == arrmax) {
      maxctr++;
      tmp = arr[i];
      arr[i] = arr[n - maxctr];
      arr[n - maxctr] = tmp;
    }
  }

  const size_t m = n - maxctr;
  const double pos_const = double(n - 1) / double(arrmax - arrmin);

  // 2 - Calculate collisions [ O(n) time O(n) space ]
  int *collisions = new int[m]{0};
  for (i = 0; i < m; ++i) collisions[int(double(arr[i] - arrmin) * pos_const)]++;

  // 3 - Calculate offsets [ O(n) time O(1) space ]
  int c_i;
  int offset = 0;
  for (i = 0; i < m; ++i) {
    c_i = collisions[i];
    if (c_i == 0) offset--;  // there is an empty slot, decrease offset
    collisions[i] += offset;
    if (c_i > 1) offset += c_i - 1;  // there are collisions, increase offset
  }

  // 4 - Placements [ O(n) time O(n) space ]
  T *newArr = new T[m]{0};
  for (i = 0; i < m; ++i) {
    // Calculate position
    pos = int(double(arr[i] - arrmin) * pos_const);
    collisions[pos]--;
    newArr[pos + collisions[pos]] = arr[i];
  }
  memcpy(arr, newArr, m * sizeof(T));  // back to original array

  // 5 - Insertion Sort [ O(n^2) time worst, but is working on a nearly sorted
  // array ]
  for (i = 1; i < n - maxctr; ++i) {
    tmp = arr[i];
    j = i - 1;
    while (j >= 0 && tmp < arr[j]) {
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j + 1] = tmp;
  }

  delete[] collisions;
  delete[] newArr;
}

/**
 * @brief This is the initial code from 2016, just for the record.
 * It is badly written, and has lots of redundant complexity in it.
 * Kind of my "baby-steps" in programming I guess.
 *
 * @tparam T: type of the array
 * @param arr: input array
 * @param n: size of the array
 */
template <typename T>
void flashy_sort_old(T *arr, int n) {
  // Variables
  int pos, i, j, offset, maxPlacer;
  int *collisions, *offsets, *newCollisions;
  T *newArr;

  // 1 - Find min and max [ O(n) time, O(1) space ]
  T arrmin, arrmax;
  arrmin = arr[0];
  arrmax = arr[0];
  for (i = 1; i < n; i++) {
    if (arr[i] < arrmin) arrmin = arr[i];
    if (arr[i] > arrmax) arrmax = arr[i];
  }

  // 2 - Calculate collisions [ O(n) time O(n) space ]
  collisions = new int[n]{0};
  for (i = 0; i < n; i++) {
    pos = int(double((arr[i] - arrmin)) / (double(arrmax - arrmin)) * double((n - 1)));
    collisions[pos]++;
  }

  // 3 - Calculate offsets [ O(n) time O(n) space ]
  offsets = new int[n]{0};
  offset = 0;
  for (i = 0; i < n; i++) {
    if (collisions[i] == 0) offset--;  // there is an empty slot, decrease offset
    offsets[i] = offset;
    if (collisions[i] > 1) offset += collisions[i] - 1;  // there are collisions, increase offset
  }

  // 4 - Update collisions with regard to offsets [ O(n) time O(n) space ]
  newCollisions = new int[n]{0};
  for (i = 0; i < n; i++)
    if (collisions[i] != 0) newCollisions[i + offsets[i]] = collisions[i];

  // 5 - Place numbers to new array [ O(n) time O(n) space ]
  newArr = new T[n]{0};
  maxPlacer = 0;  // Offsets are positive, but if the number is maximum it needs
                  // a negative offset, therefore we use this variable
  for (i = 0; i < n; i++) {
    // Calculate position
    pos = int(double((arr[i] - arrmin)) / (double(arrmax - arrmin)) * double((n - 1)));

    // Place in new array
    if (arr[i] != arrmax) {
      cout << "Placing " << i << " at " << pos + offsets[pos] + newCollisions[pos + offsets[pos]] - 1 << endl;
      newArr[pos + offsets[pos] + newCollisions[pos + offsets[pos]] - 1] = arr[i];
    } else {
      cout << "Placing " << i << " at " << pos - maxPlacer << endl;
      newArr[pos - maxPlacer++] = arr[i];
    }

    // Update collisions again
    newCollisions[pos + offsets[pos]]--;
  }

  // 6 - Assign back to the original array [ O(n) time O(1) space ]
  memcpy(arr, newArr, n * sizeof(T));

  // 7 - Do modified insertion sort on the array [ O(n^2) time O(1) space, but
  // insertion sort is working on a nearly sorted array ]
  int curPosVal = 0;  // NOTE: i think this was forgot to be used
  i = 0;
  j = i + 1;
  while (j < n) {
    while (j < n && int(double((arr[j] - arrmin)) / (double(arrmax - arrmin)) * double((n - 1))) != curPosVal) j++;

    // Do insertion sort between [i, j) so j excluded i included
    for (int ii = i; ii < j; ++ii) {
      double key = arr[ii];
      int jj = ii - 1;
      // Move element of arr[0...i-1], that are greater than key, one position
      // ahead of their current position
      while (jj >= 0 && arr[jj] > key) {
        arr[jj + 1] = arr[jj];
        jj = jj - 1;
      }
      arr[jj + 1] = key;
    }

    i = j;
    j = i + 1;
  }

  delete[] newArr;
  delete[] newCollisions;
  delete[] collisions;
  delete[] offsets;
}