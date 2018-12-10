#include "stdafx.h"
#include <iostream>

#include <stdlib.h> 
#include <time.h>
#include <string>


const size_t SIZE = 15;

void print(int * arr, size_t n);
int linearSearch(int * arr, size_t n, int key);			// O(n)
int binarySearch(int * arr, int l, int r, int key);		// O(log_n)
void insertionSort(int * arr, size_t n);				// O(n^2)
void selectionSort(int * arr, size_t n);				// O(n^2)

void merger(int * arr, int lo, int  mi, int hi);
void mergeSortHelper(int * arr, int lo, int hi);
void mergeSort(int * arr, int arr_size);				// O(nlog_n)


int main() {
	int arr[SIZE];
	int arr2[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

	srand(time(NULL));
	for (size_t i = 0; i < SIZE; i++) {
		arr[i] = rand() % 100;
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	int arr3[7] = { 7, 6, 5, 4, 3, 2, 1 };

	mergeSort(arr3, 7);
	print(arr3, 7);




	std::cin.get();
}

void print(int * arr, size_t n) {
	for (size_t i = 0; i < n; i++) {
		std::cout << arr[i] << " " << std::flush;
	}
}

// 'linearSearch' -> O(n), linear runtime
int linearSearch(int * arr, size_t n, int key) {
	for (size_t i = 0; i < n; i++) {
		if (arr[i] == key) 
			return i;
		else 
			return -1;
	}
}

// 'binarySearch' -> O(log_n), logarithmic runtime
// each iteration eliminates half of the array
// For any number n, lon2 n  gives the number of times n needs to be divided by 2 before reaching 1
int binarySearch(int * arr, int l, int r, int key) {
	if (r >= l) {
		int mid = l + (r - l) / 2;

		if (arr[mid] == key)
			return mid;

		if (arr[mid] > key)
			return binarySearch(arr, l, mid - 1, key);

		return binarySearch(arr, mid + 1, r, key);
	}

	return -1;
}

void swap(int * a, int * b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 'insertionSort' -> O(n^2), quadratic runtime
void insertionSort(int * arr, size_t n) {
	for (size_t i = 1; i < n; i++) {
		for (size_t j = i - 1; j-- > 0;) {
			if (arr[j + 1] < arr[j]) {
				swap(&arr[j + 1], &arr[j]);
			}
		}
	}
}

// 'selectionSort' -> O(n^2), quadratic runtime
void selectionSort(int * arr, size_t n) {
	int min;
	for (auto i = 0; i < n - 1; i++) {
		min = i;

		for (auto j = i + 1; j < n; j++) {
			if (arr[j] < arr[min]) 
				min = j;
		}
		swap(&arr[i], &arr[min]);
	}
}

// 'mergeSort' -> O(nlog_n), logarithmic runtime
// divide-and-conquer sorting algorithm
// always divides the array in two halves and take linear time to merge two halves
void merger(int * arr, int leftIdx, int  mi, int rightIdx) {
	int * temp = new int[rightIdx - leftIdx + 1];

	int i = leftIdx;	// Initial index of left subarray
	int j = mi + 1;		// Initial index of right subarray
	int k = 0;			// Initial index of merged subarray

	while (i <= mi && j <= rightIdx) {
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}

	//rest elements of left-half
	while (i <= mi)
		temp[k++] = arr[i++];
	//rest elements of right-half
	while (j <= rightIdx)
		temp[k++] = arr[j++];

	//copy the mergered temporary array to the original array
	for (k = 0, i = leftIdx; i <= rightIdx; ++i, ++k)
		arr[i] = temp[k];

	delete[] temp;
}
void mergeSortHelper(int * arr, int leftIdx, int rightIdx) {
	int mid;
	if (leftIdx < rightIdx) {
		mid = leftIdx + (rightIdx - leftIdx) / 2;

		mergeSortHelper(arr, leftIdx, mid);
		mergeSortHelper(arr, mid + 1, rightIdx);
		merger(arr, leftIdx, mid, rightIdx);
	}
}
void mergeSort(int * arr, int n) {
	mergeSortHelper(arr, 0, n - 1);
}

