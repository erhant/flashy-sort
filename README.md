# Flashy Sort
Flashy Sort is a sorting algorithm similar to Flash Sort I had written around 2016 during my Sophomore year. It follows the same idea behind Flash Sort, though I didn't know about it back then.

It is basically a Flash Sort with `m=n` and no *in situ* permutation. So, it is worse than the original Flash Sort. Nevertheless I thought I should still store it for memories I guess.

## Key Idea
 
```
   pos     arr
   -+-     -+-
n-1 |       | max
.   |       | .
p   |  vs   | v
.   |       | .
0   |       | min

For any v, what is p?
```

The idea is to look at the ratio in the setting above, by choosing a value between `max` and `min` from `arr` (which is the array itself), and then calculating where it would correspond to in the `pos` scale. I had thought of this as the Celcius to Fahrenheit conversion when I wrote it, hence I used to call this `Thermo Sort` before. 

Some values will try to occupy the same place, so the algorithm gets trickier on that part.


