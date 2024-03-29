#include "flashsort.hpp"
#include "flashysort.hpp"
#include "util.hpp"

using namespace std;
#include <chrono>
#include <cstring>
#include <iostream>
#include <memory>

#define DEFAULT_MIN_VAL -10.0
#define DEFAULT_MAX_VAL 10.0
#define DEFAULT_SIZE 50

using namespace std;
typedef chrono::high_resolution_clock Time;
typedef chrono::milliseconds ms;

bool scripted = false;
bool print = false;

/**
 * @brief Evaluate the sorting algorithms.
 *
 * Prints the milliseconds for each sorting algorithm.
 *
 * @tparam T: type of the array
 * @param N: size of the array
 * @param min: minimum value in the array
 * @param max: maximum value in the array
 * @param print: print the array contents?
 */
template <typename T>
void evaluate(int N, T min, T max) {
  // Timers
  auto start = Time::now();
  auto end = Time::now();
  ms duration;

  // Create base random array
  T* init_arr = create_array<T>(N, min, max);
  if (print) print_array(init_arr, N, "Initial Array:");

  // have an auxillary mutable array
  T* arr = new T[N];

  // Sort using flash sort
  memcpy(&arr[0], &init_arr[0], N * sizeof(T));
  start = Time::now();
  flash_sort<T>(arr, N);
  end = Time::now();
  duration = std::chrono::duration_cast<ms>(end - start);
  if (scripted) {
    cout << "1||" << (isSorted<T>(arr, N) ? '1' : '0') << "||" << duration.count() << endl;
  } else {
    if (print) print_array(arr, N, "\nAfter Flash Sort:");
    cout << "Flash Sort " << (isSorted<T>(arr, N) ? "sorted" : "did not sort") << " in " << duration.count() << " ms\n";
  }

  // Sort using flashy sort
  memcpy(&arr[0], &init_arr[0], N * sizeof(T));
  start = Time::now();
  flashy_sort<T>(arr, N);
  end = Time::now();
  duration = std::chrono::duration_cast<ms>(end - start);
  if (scripted) {
    cout << "2||" << (isSorted<T>(arr, N) ? '1' : '0') << "||" << duration.count() << endl;
  } else {
    if (print) print_array(arr, N, "\nAfter Flashy Sort:");
    cout << "Flashy Sort " << (isSorted<T>(arr, N) ? "sorted" : "did not sort") << " in " << duration.count()
         << " ms\n";
  }

  delete[] arr;
  delete[] init_arr;
}

int main(int argc, char* argv[]) {
  int N = DEFAULT_SIZE;
  double min = DEFAULT_MIN_VAL, max = DEFAULT_MAX_VAL;
  datatype_e type = INTEGER;
  for (int ac = 1; ac < argc; ac++) {
    if (MATCH_INPUT("-n")) {
      N = atoi(argv[++ac]);
    }  // size of array
    else if (MATCH_INPUT("-p")) {
      print = true;
    }  // print arrays
    else if (MATCH_INPUT("-s")) {
      scripted = true;
    }  // output should be script friendly (for eval.ipynb)
    else if (MATCH_INPUT("--min")) {
      min = atof(argv[++ac]);
    }  // min value
    else if (MATCH_INPUT("--max")) {
      max = atof(argv[++ac]);
    }  // max value
    else if (MATCH_INPUT("--int")) {
      type = INTEGER;
    }  // use int array
    else if (MATCH_INPUT("--float")) {
      type = FLOAT;
    }  // use float array
    else if (MATCH_INPUT("--double")) {
      type = DOUBLE;
    }  // use double array
    else {
      cout << "Usage: " << argv[0] << "[-n <size>] [-p] [--min <num>] [--max <num>] [--int | --float | --double]\n";
      exit(-1);
    }
  }
  if (N <= 0) {
    cout << "Please enter a positive integer for size!\n";
    exit(-1);
  }

  if (!scripted) cout << "Generating array of size " << N << " with values in range [" << min << "," << max << "]\n\n";
  if (type == INTEGER)
    evaluate<int>(N, min, max);
  else if (type == FLOAT)
    evaluate<float>(N, min, max);
  else if (type == DOUBLE)
    evaluate<double>(N, min, max);
}
