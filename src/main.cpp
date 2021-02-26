#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <cstring>
#include <time.h>
#include "util.h"


template <typename T>
void flashierSort(T* arr, int n) { 
  clock_t clk = clock(); 
  int pos, i, j;
  // 1 - Find min and max [ O(n) time, O(1) space ]
  T arrmin, arrmax;
  arrmin = arr[0];
  arrmax = arr[0];
  for (i = 1; i < n; i++) {
    if (arr[i] < arrmin) arrmin = arr[i];
    if (arr[i] > arrmax) arrmax = arr[i];
  }

  // 2 - Calculate collisions [ O(n) time O(n) space ]
  int* collisions = (int *)calloc(n, sizeof(int)); // initially zeros
  for (i = 0; i<n; i++) {
    // Calculate position
    pos = int(double((arr[i]-arrmin))/(double(arrmax-arrmin))*double((n-1)));
    // Increment position value
    collisions[pos]++;
  }

  // 3 - Calculate offsets [ O(n) time O(n) space ]
  int* offsets = (int *)calloc(n, sizeof(int)); // initially zeros
  int offset = 0;
  for (i = 0; i<n; i++) {
    if (collisions[i]==0) offset--;
    offsets[i] = offset;
    if (collisions[i]>1) offset += collisions[i]-1;
  }

  // 4 - Update collisions with regard to offsets [ O(n) time O(n) space ]
  int* newCollisions = (int *)calloc(n, sizeof(int)); // initially zeros
  for(i = 0; i<n; i++)
    if (collisions[i]!=0)
      newCollisions[i + offsets[i]] = collisions[i];

  // 5 - Place numbers to new array [ O(n) time O(n) space ]
  T* newArr = (T *)calloc(n, sizeof(T));
  int maxPlacer = 0; // Offsets are positive, but if the number is maximum it needs a negative offset, therefore we use this variable
  for (i = 0; i<n; i++) {
    // Calculate position
    pos = int(double((arr[i]-arrmin))/(double(arrmax-arrmin))*double((n-1)));
    // Place in new array
    if (arr[i] != arrmax)
      newArr[pos + offsets[pos] + newCollisions[pos + offsets[pos]] - 1] = arr[i];
    else
      newArr[pos - maxPlacer++] = arr[i];
    // Update collisions again
    newCollisions[pos + offsets[pos]]--;
  }

  // 6 - Assign back to the original array [ O(n) time O(1) space ] 
  std::memcpy(arr, newArr, n * sizeof(T));

  // 7 - Do modified insertion sort on the array [ O(n^2) time O(1) space, but insertion sort is working on a nearly sorted array ]
  int curPosVal = 0;
  i = 0;
  j = i+1;
  while (j<n) {
    while ( j<n && int(double((arr[j]-arrmin))/(double(arrmax-arrmin))*double((n-1))) != curPosVal ) 
      j++;
      
    // Do insertion sort between [i, j) so j excluded i included
    for (int ii = i; ii < j; ++ii) {
      double key = arr[ii];
      int jj = ii - 1;
      // Move element of arr[0...i-1], that are greater than key, one position ahead of their current position
      while (jj >= 0 && arr[jj] > key) {
        arr[jj + 1] = arr[jj];
        jj = jj - 1;
      }
      arr[jj + 1] = key;
    }

    i = j;
    j = i+1;
  }
  free(newArr);
  free(newCollisions);
  free(collisions);
  free(offsets); 
  clk = clock() - clk;
  printf("\nSorted in: %.20f ms\n",clk); 
}

template<typename T>
void test_array(int N, bool print = false) { 
  T * arr = create_array<T>(N, 1.0, 6.0);
  
  if (print) {
    printf("Before: ");
    print_array(arr, N);
    printf("\n");
  }
    

  flashierSort<T>(arr, N);
  if (print) {
    printf("After: ");
    print_array(arr, N);
    printf("\n");
  }

  printf("Is Sorted: %s", (isSorted<T>(arr, N) ? "True" : "False"));
  free(arr);
}

int main() {
  test_array<double>(100000);
}