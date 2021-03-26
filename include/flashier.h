/**
 * Flashier Sort.
 * 
 * Independently written by Erhan Tezcan. It uses a similar logic to Flash Sort.
 */


#include <stdio.h> 
#include <math.h> 
#include <assert.h>

// This is the initial code from years ago (2016-ish)! It has A LOT OF redundant code in it.
template <typename T>
void flashier_sort(T* arr, int n) { 
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
  collisions = (int *)calloc(n, sizeof(int)); // initially zeros
  for (i = 0; i<n; i++) {
    pos = int(double((arr[i]-arrmin))/(double(arrmax-arrmin))*double((n-1)));
    collisions[pos]++;
  }

  // 3 - Calculate offsets [ O(n) time O(n) space ]
  offsets = (int *)calloc(n, sizeof(int)); // initially zeros
  offset = 0;
  for (i = 0; i<n; i++) {
    if (collisions[i]==0) offset--; // there is an empty slot, decrease offset
    offsets[i] = offset;
    if (collisions[i]>1) offset += collisions[i]-1; // there are collisions, increase offset
  }

  // 4 - Update collisions with regard to offsets [ O(n) time O(n) space ] 
  newCollisions = (int *)calloc(n, sizeof(int)); // initially zeros
  for(i = 0; i<n; i++)
    if (collisions[i]!=0)
      newCollisions[i + offsets[i]] = collisions[i];

  // 5 - Place numbers to new array [ O(n) time O(n) space ]
  newArr = (T *)calloc(n, sizeof(T));
  maxPlacer = 0; // Offsets are positive, but if the number is maximum it needs a negative offset, therefore we use this variable
  for (i = 0; i<n; i++) {
    // Calculate position
    pos = int(double((arr[i]-arrmin))/(double(arrmax-arrmin))*double((n-1)));
    
    // Place in new array
    if (arr[i] != arrmax) {
      printf("Placing %d at %d\n",i,pos + offsets[pos] + newCollisions[pos + offsets[pos]] - 1);
      newArr[pos + offsets[pos] + newCollisions[pos + offsets[pos]] - 1] = arr[i];
    } else {
      printf("Placing %d at %d\n",i,pos - maxPlacer);
      newArr[pos - maxPlacer++] = arr[i];
    }
      
    // Update collisions again
    newCollisions[pos + offsets[pos]]--;
  }

  // 6 - Assign back to the original array [ O(n) time O(1) space ] 
  std::memcpy(arr, newArr, n * sizeof(T));

  // 7 - Do modified insertion sort on the array [ O(n^2) time O(1) space, but insertion sort is working on a nearly sorted array ]
  int curPosVal = 0; // NOTE: i think this was forgot to be used
  i = 0;
  j = i+1;
  while (j<n) {
    while (j<n && int(double((arr[j]-arrmin))/(double(arrmax-arrmin))*double((n-1))) != curPosVal) 
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
}

 