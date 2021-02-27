/***** FLASH.C ,FLOAT-, recursive subroutine version  
Translation of Neubert's algorithm into C by Michael Sahota *****/

/* Subroutine Flash(a,n,m)
- Sorts array a with n elements by use of the index vector l of dimension scaleFactor * n. Recommended value for scaleFactor = 0.1
- The routine runs fastest with a uniform distribution of elements.
- The vector l is declare dynamically using the calloc function.
- THRESHOLD is a very important constant.  It is the minimum number of elements required in a subclass before recursion is used. 

Taken from http://www.yendor.com/programming/sort/Jann/SortLibrary/SortLibrary/flashsort.c
*/

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>  

const int THRESHOLD = 75;

template <typename T>
void flashsort_sub(T* a, int n, double scaleFactor) {
	int *l, nmin, nmax, i, j, k, nmove, nx, mx;
	T c1, c2, flash, hold;
	int m = (int)(scaleFactor*n); // m is usually chosen to be 0.1 * n

	l = (int*)calloc(m,sizeof(int));

	/***** CLASS FORMATION ****/
	nmin = 0;
	nmax = 0;
	for (i = 0 ; i < n ; i++) {
		if (a[i] < a[nmin]) nmin = i;
		else if (a[i] > a[nmax]) nmax = i;
	}

	if (a[nmax] == a[nmin])	return; // Array is sorted (max = min)

	c1 = (m-1.0) / (a[nmax]-a[nmin]);
	c2 = a[nmin];
	l[0] = -1; // since the base of the "a" (data) array is 0

	for (i = 0; i < n; i++) {
		k = floor(c1*(a[i]-c2));
		++l[k];
	}

	for (k = 1; k < m; k++) {
		l[k] += l[k-1];
	}

	hold = a[nmax];
	a[nmax] = a[0];
	a[0] = hold; 

	/**** PERMUTATION *****/
	nmove = 0;
	j = 0;
	k = m - 1;

	while (nmove < n) {
		while (j > l[k]) {
			j++;
			k = floor(c1*(a[j]-c2)) ;
		}

		flash = a[j];
		while (j <= l[k]) {
			k = floor(c1*(flash-c2));
			hold = a[l[k]];
			a[l[k]] = flash;
			l[k]--;
			flash = hold;
			nmove++;
		}
	}

	/**** STRAIGHT INSERTION *****/
	for(j = 1; j < n; ++j) {
    hold = a[j];
    i = j - 1;
    while (i >= 0 && a[i] > hold) {
      a[i+1] = a[i--];
    }   
    a[i+1] = hold;
  }

	free(l);   /* need to free the memory we grabbed for the l vector */
}

template <typename T>
void flash_sort(T* arr, int size) {
  flashsort_sub<T>(arr, size, 0.1);
}