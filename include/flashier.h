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
void flashier_sort_old(T* arr, int n) { 
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

 /**
  * @brief Sort an array of numeric values using Flashier Sort.
  * 
  * Comparing to the old code:  
  * Denominator of pos is memoized.
  * Does not use newArr, newCollisions or offsets. Uses an extra placements array (TODO optimize)
  * 
  * @tparam T: type of the array
  * @param arr: array pointer
  * @param n: size of the array 
  */
template <typename T>
void flashier_sort(T* arr, int n) { 
  // Variables
  int pos, i, j, offset, maxctr = 1;
  int *collisions, *placements, c_i, p_i; 
  T arrmin, arrmax, tmp;

  // 1 - Find min and max, place max values at the end [ O(n) time, O(1) space ]
  arrmin = arr[0];
  arrmax = arr[n-1];
  for (i = 1; i < n-1; ++i) {
    if (arr[i] > arrmax) { // new max found
      arrmax = arr[i]; 
      tmp = arr[n-1]; arr[n-1] = arr[i]; arr[i] = tmp;
      maxctr=1;
    } else if (arr[i] == arrmax) { // another equal max found
      tmp = arr[n-maxctr-1]; arr[n-maxctr-1] = arr[i]; arr[i] = tmp;      
      maxctr++;
    }

    if (arr[i] < arrmin) arrmin = arr[i]; 
    
  }
  if (arrmin == arrmax) return; // max=min means sorted already

  const double pos_const = double(arrmax-arrmin) / double(n-1);
  // 2 - Calculate collisions [ O(n) time O(n) space ]
  collisions = (int *)calloc(n - maxctr, sizeof(int)); // initially zeros
  for (i = 0; i < n - maxctr; ++i) 
    collisions[int(double(arr[i]-arrmin)/double(arrmax-arrmin)*double(n-1))]++;

  // 3 - Calculate offsets [ O(n) time O(1) space ] 
  offset = 0;
  for (i = 0; i < n - maxctr; ++i) {
    c_i = collisions[i];
    if (c_i==0) offset--; // there is an empty slot, decrease offset
    collisions[i] += offset;
    if (c_i>1) offset += c_i-1; // there are collisions, increase offset
  } 

  // 4 - Calculate placements [ O(n) time O(n) space ]
  placements = (int *)malloc((n - maxctr) * sizeof(int)); // initially zeros
  for (i = 0; i < n - maxctr; ++i) {
    // Calculate position
    pos = int(double(arr[i]-arrmin)/double(arrmax-arrmin)*double(n-1));
    placements[i] = pos + collisions[pos] - 1;
    collisions[pos]--;
  } 

  // 5 - In-line placing [ O(n) time O(1) space ]
  for (i = 0; i<n - maxctr; ++i) { 
    p_i = placements[i];
    // Check index if it has already been swapped before
    while (p_i < i) p_i = placements[p_i];
    // Swap the position of elements
    tmp = arr[i]; arr[i] = arr[p_i]; arr[p_i] = tmp;
  } 

  // 6 - Insertion Sort [ O(n^2) time worst, but is working on a nearly sorted array ]
  for (i = 1; i<n - maxctr; ++i) { 
    tmp = arr[i];
    j = i-1;
    while (j >= 0 && tmp < arr[j]) {
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j + 1] = tmp;
  }
   
  free(collisions);
  free(placements); 
}