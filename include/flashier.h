/**
 * Flashier Sort.
 * 
 * Independently written by Erhan Tezcan. It uses a similar logic to Flash Sort.
 * 
 * Note: the first version had newCollisions array, but it is easily possible to use collisions only!
 */


#include <stdio.h> 
#include <math.h> 
#include <assert.h>

// This is the initial implementation from years ago
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

  // 4 - Update collisions with regard to offsets [ O(n) time O(n) space ] TODO: maybe we dont need newCollisions array here
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


///
// This is the newer version, with some improvements
// Does not use newCollisions array
// Does not use maxPlacer
// Places maxs at the beginning (eliminates maxPlacer need)
// Places mins at the beginning NOTE: maybe we dont need this 
// Denominator for pos is calculated once
// Remove redundant casts from pos calculation
template <typename T>
void flashier_sort_optim(T* arr, int n) { 
  // Variables
  int pos, i, j, offset;
  int *collisions, *offsets;
  T *newArr; 

  // 1 - Find min and max [ O(n) time, O(1) space ], while placing maxes to the end and mins to the start 
  T arrmin, arrmax, tmp;
  arrmin = arr[0];
  arrmax = arr[n-1];
  int maxCount = 1, minCount = 1;
  for (i = 1; i < n-1; i++) {
    if (arr[i] < arrmin) { // new min found, put to start
      arrmin = arr[i]; 
      tmp = arr[0];
      arr[0] = arr[i];
      arr[i] = tmp;
      minCount = 1; // reset counter
    } else if (arr[i] == arrmin) {
      tmp = arr[0 + minCount];
      arr[0 + minCount] = arr[i];
      arr[i] = tmp;
      minCount++;
    }     
    
    if (arr[i] > arrmax) { // new max found, put to end
      arrmax = arr[i];
      tmp = arr[n - 1];
      arr[n - 1] = arr[i];
      arr[i] = tmp;
      maxCount = 1; // reset counter
    } else if (arr[i] == arrmax) { // other max's found, put to next position
      tmp = arr[n - 1 - maxCount];
      arr[n - 1 - maxCount] = arr[i];
      arr[i] = tmp;
      maxCount++;
    }
  }
  
  // 2 - Calculate collisions [ O(n) time O(n) space ]
  collisions = (int *)calloc(n, sizeof(int)); // initially zeros
  const double posDenom = double(arrmax-arrmin)*double(n-1);
  for (i = 0; i<n; i++) 
    collisions[int(double((arr[i]-arrmin))/posDenom)]++;

  // 3 - Calculate offsets [ O(n) time O(n) space ]
  offsets = (int *)calloc(n, sizeof(int)); // initially zeros
  offset = 0;
  for (i = 0; i<n; i++) {
    if (collisions[i]==0) offset--; // there is an empty slot, decrease offset
    offsets[i] = offset;
    if (collisions[i]>1) offset += collisions[i]-1; // there are collisions, increase offset
  }

  // 4 - Place numbers to the new array
  newArr = (T *)calloc(n, sizeof(T));
  for (i = 0; i<n-maxCount; i++) {
    // Calculate position
    pos = double((arr[i]-arrmin))/posDenom;
    // Place in new array
    newArr[pos + offsets[pos] + collisions[pos] - 1] = arr[i];
    // Update collisions again
    collisions[pos]--;
  }

  // 6 - Transfer back
  for (i = 0; i<n-maxCount; i++) {
    arr[i] = newArr[i];
  }

  // 5 - Do modified insertion sort on the array [ O(n^2) time O(1) space, but insertion sort is working on a nearly sorted array ]
  // TODO: needs work here...
  i = 0;
  j = i+1;
  while (j<n) {
    while (j<n && double((arr[j]-arrmin))/posDenom != 0) 
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
  free(collisions);
  free(offsets); 
}
