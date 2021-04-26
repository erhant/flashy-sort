# Flashy Sort
Flashy Sort is a sorting algorithm similar to Flash Sort.

## TO DO:
- 1) We can perhaps use array instead of newArray, by doing in-place. This is because the positioning system gives us a 1-to-1 mapping.
- 2) We can eliminate maxPlacer by placing max values at the start (code above) and then working with the rest of the array for the rest. We can also deal with mins there too.
- 3) Calculate the denominator of pos just once to make that faster.
- 4) Remove redundant castings from pos calculations.
- 5) We can perhaps use collisions array instead of newCollisions, by doing in-place. Because i + offsets[i] are unique for each i it seems.
- 6) Fix the insertion sort part. Also is normal insertion over whole array good or can we make it better?
