/*
Insertion sort is a simple sorting algorithm, used to sort arrays and other data structures.

Insertion sort uses the idea of sorting portions of the array at a time;
First, it sorts the first 2 items, then the first 3, then 4, then 5, etc.

We start from item 1 (array of size 1 is automatically sorted) and compare it to item 0.
If 1 < 0, we swap the 2 values, otherwise do nothing.
Next we look at item 2.
If 2 < 1, we swap the 2 values; then if 1 < 0 we swap them again as this sub-array is no longer neccessarily sorted.

This recursive sort of behaviour can be simply written in a while loop.
pseudocode:
    for (i = 1, i < array.size, i++) in array:
        j = i - 1;
        // decrement from i - 1 to start, comparing and conditionally swapping as you go
        while (j >= 0 && array[j + 1] < array[j]):
            swapJAndJPlus1();
            --j;
    return array;

    1. The i pointer points at the element we are currently inserting into the sorted portion of the array.
    2. The j pointer starts off one index to the left of i.
    3. Our goal is to find the position that arr[i] should be inserted into the sorted portion of the array.
    4. We continue swapping it with arr[j] until we find the correct position.
    5. After each swap we shift j to the left by 1
    6. We stop once the element is greater than or equal to the element to its left.
*/

#include <vector>

std::vector<int> insertionSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return arr;

    int j;
    int temp;
    for (int i = 1; i < arr.size(); i++) {
        j = i - 1;
        while (j >= 0 && arr[j + 1] < arr[j]) {
            // Swap arr[j] and arr[j+1]
            temp = arr[j + 1];
            arr[j + 1] = arr[j];
            arr[j--] = temp;
        }
    }

    return arr;
}


/*
*Stability

Stability, in terms of sorting algorithms, refers to whether identical values are guarunteed to 
retain their relative order or not.
That is, if we have 2 identical values (say 7{1}, and 7{2}), a stable sorting algorithm will always
end with those 2 identical values retaining their original order.
    [7{1}, 3, 7{2}] ---> [3, 7{1}, 7{2}]
An unstable sorting algorithm may retain this order, but it is not guarunteed.

It is generally advisable to try to make your sorting algorithmns stable if possible without hurting 
their time and space complexity.

This implementation of insertionSort is stable.



*Time and Space Complexity
*Time Complexity

The best case for this algorithm is when the input array is already sorted.
In this case the algorithm will iterate through the array and do 1 comparison per item.
Therefore, the best case time complexity is O(n).

The worst case for this algorithm is when the input array is reverse sorted.
E.g., [5,4,3,2,1]
In this case the maximum number of swaps per item will happen:
    i = 1
        [4,5,3,2,1]
    i = 2
        [4,3,5,2,1]
        [3,4,5,2,1]
    i = 3
        [3,4,2,5,1]
        [3,2,4,5,1]
        [2,3,4,5,1]
    i = 4
        [2,3,4,1,5]
        [2,3,1,4,5]
        [2,1,3,4,5]
        [1,2,3,4,5]

This generalises to be {1 + 2 + 3 + 4 + 5 + ... + n - 1}.
This is actually mathematically bound by n^2 {n + n + n + n + ... + n}.
This is because all corresponding values are <= n.
Therefore the time complexity of c * n^2 where c is some constant less than 1 (c is roughly 0.5 here). [../insertionSortWorstCaseTimeComplexityProof.png]
Therefore, since we ignore constants in big-O notation, the worst-case time complexity is O(n^2) 

*Space Complexity
Since insertion sort is an in-place sorting algorithm (it uses no extra data structures), the space
complexity is O(1). 
*/


/*
Conclusion - insertionSort ()

Case  |Big-O Time |Big-O Space
------+-----------+-----------
Best  |O(n)       |O(1)
Worst |O(n^2)     |O(1)
*/