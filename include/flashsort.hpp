/* Translation of Neubert's algorithm into C by Michael Sahota
- Sorts array a with n elements by use of the index vector l of dimension
scaleFactor * n. Recommended value for scaleFactor = 0.1
- The routine runs fastest with a uniform distribution of elements.
- The vector l is declared dynamically using the calloc function.

Code modified by Erhan Tezcan.

Taken from
http://www.yendor.com/programming/sort/Jann/SortLibrary/SortLibrary/flashsort.c
and modified to not use recursion.
*/

#pragma once

using namespace std;
#include <cstring>

template <typename T>
void flash_sort(T *a, const int n, const double scaleFactor = 0.1);

#include "flashsort.tpp"