#include "stdafx.h"
#include <iostream>

#include <stdlib.h> 
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>


/* Big O time complexity - 
 * describes the impact of increasing the input data on the time
 * taken for a program to run
 *
 * Big O space complexity - 
 * describes the impact of increasing the input data on the extra
 * memory needed by the program
 */

const size_t SIZE = 15;

void print(int * arr, size_t n);
int linearSearch(int * arr, size_t n, int key);	
int binarySearchIterative(int * arr, int l, int r, int key);
int binarySearchRecursive(int * arr, int l, int r, int key);
int jumpSearch(int * arr, int n, int key);

void bubbleSort(int * arr, size_t n);
void insertionSort(int * arr, size_t n);				
void selectionSort(int * arr, size_t n);				

void merger(int * arr, int leftIdx, int  mi, int rightIdx);
void mergeSortHelper(int * arr, int leftIdx, int rightIdx);
void mergeSort(int * arr, int arr_size);	

int partition(int * arr, int leftIdx, int rightIdx);
void quickSortHelper(int * arr, int leftIdx, int rightIdx);
void quickSort(int * arr, int n);



int main() {
	int arr[SIZE];
	int arr2[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

	srand(time(NULL));
	for (size_t i = 0; i < SIZE; i++) {
		arr[i] = rand() % 100;
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;



	std::cin.get();
}

void print(int * arr, size_t n) {
	for (size_t i = 0; i < n; i++) {
		std::cout << arr[i] << " " << std::flush;
	}
}

// 'linearSearch' -> O(n), linear runtime
// O(1), constant space complexity
int linearSearch(int * arr, size_t n, int key) {
	for (size_t i = 0; i < n; i++) {
		if (arr[i] == key) 
			return i;
		else 
			return -1;
	}
}

// ON SORTED ARRAY
// 'binarySearch' -> O(log_n), logarithmic runtime
// O(1), constant space complexity for iterative
// O(log_n)[for stack frames], logarithmic space complexity for recursive
// each iteration eliminates half of the array
// lon2_n  gives the number of times n needs to be divided by 2 before reaching 1
int binarySearchIterative(int * arr, int l, int r, int key) {
	while (l <= r) {
		int mid = l + (r - l) / 2;

		if (arr[mid] == key)
			return mid;

		if (arr[mid] < key)
			l = mid + 1;
		else 
			r = mid - 1;
	}
	return -1;
}

int binarySearchRecursive(int * arr, int l, int r, int key) {
	if (r >= l) {
		int mid = l + (r - l) / 2;

		if (arr[mid] == key)
			return mid;

		if (arr[mid] > key)
			return binarySearchRecursive(arr, l, mid - 1, key);
		return binarySearchRecursive(arr, mid + 1, r, key);
	}
	return -1;
}

// ON SORTED ARRAY
// 'jumpSearch' ->
int jumpSearch(int * arr, int n, int key) {
	// Finding block size to be jumped 
	int step = sqrt(n);

	// Finding the block where element is 
	// present (if it is present) 
	int prev = 0;
	while (arr[std::min(step, n) - 1] < key) {
		prev = step;
		step += sqrt(n);
		if (prev >= n)
			return -1;
	}

	// Doing a linear search for x in block 
	// beginning with prev. 
	while (arr[prev] < key) {
		prev++;

		// If we reached next block or end of 
		// array, element is not present. 
		if (prev == std::min(step, n))
			return -1;
	}
	// If element is found 
	if (arr[prev] == key)
		return prev;

	return -1;
}

void swap(int * a, int * b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 'bubbleSort' -> O(n^2), quadratic runtime
// O(1), constant space complexity
void bubbleSort(int * arr, size_t n) {
	bool swapped = false;

	for (size_t i = n - 1; i > 0; i--) {
		for (size_t j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}

// 'insertionSort' -> O(n^2), quadratic runtime
// O(1), constant space complexity
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
// O(1), constant space complexity
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

// 'mergeSort' -> O(nlog_n), linearithmic runtime
// O(log_n)[for stack frames] + O(n)[for temp array] = O(n), linear space complexity
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

// 'quickSort' -> O(n^2), quadratic runtime
// O(n)[for stack frames], linear space complexity
// divide-and-conquer sorting algorithm
int partition(int * arr, int leftIdx, int rightIdx) {

	int pivot = arr[rightIdx];
	int smallest = leftIdx - 1;

	for (size_t i = leftIdx; i <= rightIdx - 1; i++) {
		if (arr[i] < pivot) {
			++smallest;
			if (smallest != i)
				swap(&arr[smallest], &arr[i]);
		}
	}
	swap(&arr[++smallest], &arr[rightIdx]);
	return smallest;
}

void quickSortHelper(int * arr, int leftIdx, int rightIdx) {
	if (leftIdx < rightIdx) {
		int pivot = partition(arr, leftIdx, rightIdx);

		quickSortHelper(arr, leftIdx, pivot - 1);	// before pivot
		quickSortHelper(arr, pivot + 1, rightIdx);	// after pivot
	}
}

void quickSort(int * arr, int n) {
	quickSortHelper(arr, 0, n - 1);
}

