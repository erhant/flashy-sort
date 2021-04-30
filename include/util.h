#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum {
  INTEGER = 0,
  DOUBLE,
  FLOAT
} datatype_e;

// used for command line arguments, the argc and ac names are static
#ifndef MATCH_INPUT
#define MATCH_INPUT(s) (!strcmp(argv[ac], (s))) 
#endif

/**
 * @brief Creates a new array of given type with values in range [min, max]
 * 
 * @tparam T 
 * @param size 
 * @param min 
 * @param max 
 * @return T* 
 */
template <typename T>
T* create_array(int size, double min, double max) {
  assert(min <= max);
  T* arr = (T *) malloc(size * sizeof(T)); 
  for (int i = 0; i<size; i++) {
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
  for (int i = 0; i<size-1; i++)
    if (arr[i] > arr[i+1]) 
      return false;  
  return true;
}

void print_array(double* arr, int size, const char * title="Array:") {
  printf("%s\n", title);
  for (int i = 0; i<size; i++) {
    printf("%lf ", arr[i]);
  }
  printf("\n");
}
void print_array(float* arr, int size, const char * title="Array:") {
  printf("%s\n", title);
  for (int i = 0; i<size; i++) {
    printf("%f ", arr[i]);
  }
  printf("\n");
}
void print_array(int* arr, int size, const char * title="Array:") {
  printf("%s\n", title);
  for (int i = 0; i<size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
