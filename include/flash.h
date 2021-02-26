/***** FLASH.C ,FLOAT-, recursive subroutine version  

   Translation of Neubert's algorithm into C by Michael Sahota 
   Modified by Erhan Tezcan

   Also see: https://www.drdobbs.com/database/the-flashsort1-algorithm/184410496
*****/



/* Subroutine Flash(A,n,m,ctr)
 - Sorts array A with n elements by use of the index vector l of dimension m (with m about 0.1 n).
 - The routine runs fastest with a uniform distribution of elements.
 - The vector l is declared dynamically using the calloc function.
 - The variable ctr counts the number of times that flashsort is called.
 - THRESHOLD is a very important constant. It is the minimum number of elements required in a subclass before recursion is used.     
*/

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>  

 

#define FLASHSORT_THRESHOLD 75
#define FLASHSORT_CLASS_SIZE 75 // minimum value for m 

void flash_sort(float* arr, int size) {
  flashsort_sub(arr, size, 0.1 * size, 0);
}

void flashsort_sub(float a[], int n, int m, int ctr){
  int *l, nmin, nmax, i, j, k, nmove, nx, mx;
  float c1, c2, flash, hold;

  /* allocate space for the l vector */
  l = (int*) calloc (m, sizeof(int));

  /***** CLASS FORMATION ****/
  nmin = nmax = 0;

  for (i=0; i < n; i++) {
    if (a[i] < a[nmin]) nmin = i;
    else if (a[i] > a[nmax]) nmax = i;
  }

  if ((a[nmax]==a[nmin]) && (ctr==0)) {
    printf("All the numbers are identical, the list is sorted\n");  return;
  }

  c1=(m-1.0)/(a[nmax]-a[nmin]) ;
  c2=a[nmin];

  l[0]=-1; /* since the base of the "a" (data) array is 0 */
  for (k=1; k < m; k++) 
    l[k]=0;

  for (i=0; i < n; i++) {
    k = floor(c1*(a[i]-c2));
    l[k]+=1;
  }

  for (k=1; k < m; k++) {
    l[k]+=l[k-1];
  }

  hold = a[nmax];
  a[nmax] = a[0];
  a[0] = hold; 

  /**** PERMUTATION *****/ 
  nmove = 0;
  j = 0;
  k = m-1;

  while (nmove < n) {
    while  (j > l[k]) {
      j++;
      k = floor(c1 * (a[j] - c2));
    }

    flash = a[j];

    while (j <= l[k]) {
      k = floor(c1 * (flash - c2));
      hold = a[l[k]];
      a[l[k]] = flash;
      l[k]--;
      flash = hold;
      nmove++;
    }

  }


  /**** Choice of RECURSION or STRAIGHT INSERTION *****/ 
  for (k=0; k<(m-1); k++) {
    if ((nx = l[k+1]-l[k]) > FLASHSORT_THRESHOLD) { 
      // recurse
      flashsort(&a[l[k]+1], nx, FLASHSORT_CLASS_SIZE, ctr+1); 
    } else {
      // insertion sort
      for (i = l[k+1]-1; i > l[k]; i--) {
        if (a[i] > a[i+1]) {
          hold = a[i];
          j = i;
          while (hold > a[j+1]) {
            a[j++] = a[j+1];
          }            
          a[j] = hold;
        }
      }
    }
  }
      
  free(l);   /* need to free the memory we grabbed for the l vector */
}