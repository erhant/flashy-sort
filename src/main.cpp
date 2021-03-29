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
void test_array(int N, T min, T max, bool print = false) { 
  T* init_arr = create_array<T>(N, min, max);
  T* arr = (T *)malloc(N * sizeof(T));  
    
  std::memcpy(arr, init_arr, N * sizeof(T));
  if (print) { 
    print_array(arr, N, "Before: "); 
  }
  flash_sort<T>(arr, N);
  if (print) {  
    print_array(arr, N, "\nAfter Flash Sort: "); 
  }
  printf("\nIs Sorted: %s\n\n", (isSorted<T>(arr, N) ? "True" : "False"));

  std::memcpy(arr, init_arr, N * sizeof(T));
  if (print) { 
    print_array(arr, N, "Before: ");  
  }
  flashier_sort<T>(arr, N);
  if (print) {  
    print_array(arr, N, "\nAfter Flashier Sort: "); 
  }
  printf("\nIs Sorted: %s\n", (isSorted<T>(arr, N) ? "True" : "False"));

  free(arr);
  free(init_arr);
}

typedef enum {
  INTEGER = 0,
  DOUBLE,
  FLOAT
} datatype_e;

int main(int argc, char *argv[]) {
  int N = 50;
  bool print = false;
  double min = 1.0, max=10.0;
  datatype_e type = INTEGER;
  for(int ac = 1; ac < argc; ac++) {
    if      (MATCH_INPUT("-n"))       { N = atoi(argv[++ac]); }     // size of array
    else if (MATCH_INPUT("-p"))       { print = true; }             // print arrays
    else if (MATCH_INPUT("--min"))    { min = atof(argv[++ac]); }   // min value
    else if (MATCH_INPUT("--max"))    { max = atof(argv[++ac]); }   // max value
    else if (MATCH_INPUT("--int"))    { type = INTEGER; }           // int array
    else if (MATCH_INPUT("--float"))  { type = FLOAT; }             // float array
    else if (MATCH_INPUT("--double")) { type = DOUBLE; }            // double array
    else    {printf("Usage: %s -n <size> -p --min <num> --max <num> --int --float --double\n", argv[0]); return -1;}
  }
  printf("Running with N: %d\n", N); 
  if (type == INTEGER) {
    test_array<int>(N, min, max, print);
  } else if (type == FLOAT) {
    test_array<float>(N, min, max, print);
  } else if (type == DOUBLE) {
    test_array<double>(N, min, max, print);
  }
  

  return 0;
}