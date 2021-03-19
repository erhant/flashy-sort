#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// used for command line arguments
#ifndef MATCH_INPUT
#define MATCH_INPUT(s) (!strcmp(argv[ac], (s))) 
#endif

template <typename T>
T* create_array(int size, double min, double max) {
  T* arr = (T *) malloc(size * sizeof(T)); 
  for (int i = 0; i<size; i++) {
    arr[i] = T((((double)rand() / RAND_MAX) * (max - min)) + min);
  }
  return arr;
}
 
template <typename T>
bool isSorted(T* arr, int size) {
  for (int i = 0; i<size-1; i++)
    if (arr[i] > arr[i+1]) 
      return false;  
  return true;
}

void print_array(double* arr, int size, const char * title="Array") {
  printf("%s:\n", title);
  for (int i = 0; i<size; i++) {
    printf("%lf ", arr[i]);
  }
}
void print_array(float* arr, int size, const char * title="Array") {
  printf("%s:\n", title);
  for (int i = 0; i<size; i++) {
    printf("%f ", arr[i]);
  }
}
void print_array(int* arr, int size, const char * title="Array") {
  printf("%s:\n", title);
  for (int i = 0; i<size; i++) {
    printf("%d ", arr[i]);
  }
}
