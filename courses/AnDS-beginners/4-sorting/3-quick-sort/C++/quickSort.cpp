


#include <vector>
#include <iostream>


void swap(std::vector<int>& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void quickSort(std::vector<int>& arr, int start, int end) {
    if (start >= end) return;

    int pivot = arr[end];
    int nextLeasti = start;
    for (int i = start; i < end; i++) {
        if (arr[i] < pivot) swap(arr, nextLeasti++, i);
    }

    swap(arr, nextLeasti, end);

    quickSort(arr, start, nextLeasti - 1);
    quickSort(arr, nextLeasti + 1, end);
}



int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    std::cout << "Given array: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    quickSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}