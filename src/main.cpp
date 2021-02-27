#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <cstring>
#include <time.h>
#include "util.h"
#include "flashier.h"
#include "flash.h"


template<typename T>
void test_array(int N, bool print = false) { 
  T* init_arr = create_array<T>(N, 1.0, 6.0);
  T* arr = (T *)malloc(N * sizeof(T)); 
  if (print) {
    printf("Before: ");
    print_array(init_arr, N);
    printf("\n");
  }
    
  std::memcpy(arr, init_arr, N * sizeof(T));
  flash_sort<T>(arr, N);
  if (print) {
    printf("After Flash Sort: ");
    print_array(arr, N);
    printf("\n");
  }
  printf("Is Sorted: %s\n", (isSorted<T>(arr, N) ? "True" : "False"));

  std::memcpy(arr, init_arr, N * sizeof(T));
  flashier_sort<T>(arr, N);
  if (print) {
    printf("After Flashier Sort: ");
    print_array(arr, N);
    printf("\n"); 
  }
  printf("Is Sorted: %s\n", (isSorted<T>(arr, N) ? "True" : "False"));

  free(arr);
  free(init_arr);
}

int main() {
  test_array<float>(15, true);
}