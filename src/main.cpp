#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <cstring>
#include <time.h>
#include "util.h"




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