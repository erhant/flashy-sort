/**
 * Flash sort in javascript, based on: https://www.w3resource.com/javascript-exercises/searching-and-sorting-algorithm/searching-and-sorting-algorithm-exercise-12.php
 * 
 * Code slightly modified by Erhan Tezcan
 * 
 * Note: ~~(n) == floor(n), just a fast substitue for flooring in JS
 */
function flash_sort(arr, scalefactor) {
  var nmax = 0, min = arr[0];
  var n = arr.length;
  var m = ~~(scalefactor * n);
   
  /***** CLASS FORMATION ****/
  var l = new Array(m);
  for (var i = 1; i < n; ++i) {
    if (arr[i] < min)       min = arr[i]; 
    if (arr[i] > arr[nmax])  nmax = i; 
  } 
  if (min === arr[nmax]) return arr; // array is sorted (max = min)

  var c1 = (m - 1) / (arr[max] - min);

  for (var k = 0; k < m; k++) { l[k] = 0; }

  for (var j = 0; j < n; ++j) {
    k = ~~(c1 * (arr[j] - min));
    ++l[k];
  }

  for (var p = 1; p < m; ++p) {
    l[p] = l[p] + l[p - 1];
  }

  var hold = arr[nmax];
  arr[nmax] = arr[0];
  arr[0] = hold;

  /**** PERMUTATION *****/
  var move, flash;
  move = 0;
  j = 0; 
  k = m - 1;

  while (move < (n - 1)) {
    while (j > (l[k] - 1)) {
      ++j;
      k = ~~(c1 * (arr[j] - min));
    }
    if (k < 0) break;

    flash = arr[j];
    while (j !== l[k]) {
      k = ~~(c1 * (flash - min));
      l[k]--;
      hold = arr[l[k]];
      arr[l[k]] = flash; 
      flash = hold;
      ++move;
    }
  }

  /**** STRAIGHT INSERTION *****/
  for (j = 1; j < n; j++) {
    hold = arr[j];
    i = j - 1;
    while (i >= 0 && arr[i] > hold) {
      arr[i + 1] = arr[i--];
    }
    arr[i + 1] = hold;
  }
  return arr;
}


var arr = [3, 0, 2, 5, -1, 4, 1]; 
console.log("Original Array Elements"); 
console.log(arr); 
console.log("Sorted Array Elements"); 
console.log(flash_sort(arr, 0, 5));