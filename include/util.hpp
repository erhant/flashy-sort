#pragma once

using namespace std;
#include <cstring>
#include <iostream>

// data type enum
typedef enum { INTEGER, DOUBLE, FLOAT } datatype_e;

// used for command line arguments, the argc and ac names are static
#ifndef MATCH_INPUT
#define MATCH_INPUT(s) (!strcmp(argv[ac], (s)))
#else
#warning "MATCH_INPUT is defined already!"
#endif

template <typename T>
T* create_array(const int size, const double min, const double max);

template <typename T>
bool isSorted(T* arr, int size);

template <typename T>
void print_array(T* arr, int size, const char* title = "Array:");

#include "util.tpp"