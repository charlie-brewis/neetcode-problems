

#include <vector>
#include <iostream>


void merge(std::vector<int>& arr, int start, int mid, int end) {
    int sizeLeft = mid - start + 1;
    int sizeRight = end - mid;

    std::vector<int> copyLeft(sizeLeft);
    std::vector<int> copyRight(sizeRight);

    for (int i = 0; i < sizeLeft; i++) { copyLeft[i] = arr[start + i]; }
    for (int j = 0; j < sizeRight; j++) { copyRight[j] = arr[mid + 1 + j]; }

    int pLeft = 0;
    int pRight = 0;
    int pMerged = start;
    while (pLeft < sizeLeft && pRight < sizeRight) {
        if (copyLeft[pLeft] <= copyRight[pRight]) {
            arr[pMerged++] = copyLeft[pLeft++];
        } else {
            arr[pMerged++] = copyRight[pRight++];
        }
    }

    while (pLeft < sizeLeft) { arr[pMerged++] = copyLeft[pLeft++]; }
    while (pRight < sizeRight) { arr[pMerged++] = copyRight[pRight++]; }

}


void mergeSort(std::vector<int>& arr, int start, int end) {
    if (start >= end) return;

    int mid = (start + end) / 2;

    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);

    merge(arr, start, mid, end);

}



int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    std::cout << "Given array: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}