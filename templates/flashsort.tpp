#include "flashsort.hpp"

template <typename T>
void flash_sort(T *a, const int n, const double scaleFactor) {
  int *l, nmin, nmax, i, j, k, nmove;
  const size_t m = int(scaleFactor * n);  // m is usually chosen to be 0.1 * n

  /***** CLASS FORMATION ****/
  l = new int[m]{0};
  nmin = 0;
  nmax = 0;
  for (i = 0; i < n; i++) {
    if (a[i] < a[nmin]) nmin = i;
    if (a[i] > a[nmax]) nmax = i;
  }
  if (a[nmax] == a[nmin]) return;  // array is sorted (max = min)

  T c1 = double(m - 1.0) / double(a[nmax] - a[nmin]);
  T min = a[nmin];

  for (i = 0; i < n; ++i) {
    k = int(c1 * (a[i] - min));
    ++l[k];
  }

  for (k = 1; k < m; ++k) {
    l[k] += l[k - 1];
  }

  T hold = a[nmax];
  a[nmax] = a[0];
  a[0] = hold;

  /**** PERMUTATION *****/
  T flash;
  nmove = 0;
  j = 0;
  k = m - 1;

  while (nmove < n - 1) {
    while (j > l[k] - 1) {
      j++;
      k = int(c1 * (a[j] - min));
    }

    flash = a[j];
    while (j != l[k]) {
      k = int(c1 * (flash - min));
      l[k]--;
      hold = a[l[k]];
      a[l[k]] = flash;
      flash = hold;
      nmove++;
    }
  }

  /**** STRAIGHT INSERTION *****/
  for (i = 1; i < n; ++i) {
    hold = a[i];
    j = i - 1;
    while (j >= 0 && hold < a[j]) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = hold;
  }

  delete[] l;
}
