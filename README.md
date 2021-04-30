# Flashy Sort
**Flashy Sort** is a sorting algorithm similar to Flash Sort I had written around 2016 during my Sophomore year. It follows the same idea behind **Flash Sort**, though I didn't know about it back then.

```
    pos     arr
    -+-     -+-
 n-1 |       | max
 .   |       | .
 p   |  vs   | v
 .   |       | .
 0   |       | min
    -+-     -+-
For any v, what is p?
```

The idea is to look at the ratio in the setting above, by choosing a value between `max` and `min` from `arr` (which is the array itself), and then calculating where it would correspond to in the `pos` scale. I had thought of this as the Celcius to Fahrenheit conversion when I wrote it, hence I used to call this **Thermo Sort** before. 

Some values will try to occupy the same place, so the algorithm gets trickier on that part.

## Comparison
It is basically a **Flash Sort** with `m=n` and no *in situ* permutation. So, it is way worse in terms of space compared to original.  

- **Flashy Sort** uses a lot more space than **Flash Sort**. Normally the index vector takes up a space of `m`, which is a fraction of `n`. In my code, I use 2 arrays of size `n`. 
- **Flashy Sort** seems to be faster than **Flash Sort** for high problem sizes such as `n = 1500000` and more. However, a more thorough comparison is required, and also both codes here do not use recursion, which was actually used in the original algorithm by Neubert.


## TODOS
- `./sort.exe -n 1003000 -s --double` gives seg fault
