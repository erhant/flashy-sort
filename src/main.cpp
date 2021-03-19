#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <cstring>
#include <assert.h>
#include <time.h>
#include "util.h"
#include "flashier.h"
#include "flash.h"


template<typename T>
void test_array(int N, bool print = false) { 
  T* init_arr = create_array<T>(N, 1.0, 6.0);
  T* arr = (T *)malloc(N * sizeof(T)); 
  if (print) { 
    print_array(init_arr, N, "Before: "); 
  }
    
  std::memcpy(arr, init_arr, N * sizeof(T));
  flash_sort<T>(arr, N);
  if (print) { 
    print_array(arr, N, "\nAfter Flash Sort: "); 
  }
  printf("\nIs Sorted: %s\n", (isSorted<T>(arr, N) ? "True" : "False"));

  std::memcpy(arr, init_arr, N * sizeof(T));
  flashier_sort_optim<T>(arr, N);
  if (print) { 
    print_array(arr, N, "\nAfter Flashier Sort: "); 
  }
  printf("\nIs Sorted: %s\n", (isSorted<T>(arr, N) ? "True" : "False"));

  free(arr);
  free(init_arr);
}

int main(int argc, char *argv[]) {
  int N = 50;
  bool print = false;
  for(int ac = 1; ac < argc; ac++) {
    if      (MATCH_INPUT("-n"))       { N = atoi(argv[++ac]); }     // size of array
    else if (MATCH_INPUT("-p"))       { print = true; }             // print arrays
    else    {printf("Usage: %s -n <size>\n", argv[0]); return -1;}
  }
  printf("Running with N: %d\n", N);
  assert(N >= 10); // TODO: below 10 is bug?
  test_array<float>(N, print);

  return 0;
}