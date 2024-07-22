# Performance on different ordered containers C++

These two code files represent a performance test on different ordered containers.

In the first file, I use the algorithm library.
In the second file, I use loops and manual testing.

Conclusion: File 1 vs File 2
Using the algorithm library is much better in terms of performance compared to manual testing. For very large sizes, the second file does not compile on my local machine (for large values of N) , whereas the first file compiles normally, with a different execution time, of course. This highlights the richness of the C++ standard library.

In the case of manual testing, I observed that lists are faster than vectors. This is likely due to the fact that lists use iterators for navigation.

## Conclusion regarding the performance of some algorithms on ordered containers:
We observe the following complexities for each class:

 * Filling: O(N)
 * Counting: O(N)
 * Squaring the first 100 elements: O(1)
 * Copying: O(N)
 * Sorting: slightly more than O(N), actually O(N log(N)).
 * Swapping: O(1) [which is the most surprising]
### Recap:
Overall, for these operations:

deque is slower than vector.
list is much slower than vector and deque because memory is not contiguous.
If working with containers of dynamic sizes that vary significantly over time, lists might become the fastest option.
