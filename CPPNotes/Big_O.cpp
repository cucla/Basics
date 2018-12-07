#include "stdafx.h"
#include <iostream>

#include <stdlib.h> 
#include <time.h>
#include <string>


const size_t SIZE = 15;

void print(int * arr, size_t n);
int linearSearch(int * arr, size_t n, int key);		// O(n)
int binarySearch(int * arr, int l, int r, int key);		// O(log_n)
void selectionSort(int * arr, size_t n);			// O(n^2)
void insertionSort(int * arr, size_t n);


int main() {
	int arr[SIZE];
	int arr2[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

	srand(time(NULL));
	for (size_t i = 0; i < SIZE; i++) {
		arr[i] = rand() % 100;
		//std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	insertionSort(arr, SIZE);
	print(arr, SIZE);


	std::cin.get();
}

void print(int * arr, size_t n) {
	for (size_t i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
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
// repeatedly dividing 1023 by 2 will yield at most 10 divisions (2^10 = 1023)
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

// 'insertionSort'
void insertionSort(int * arr, size_t n) {
	for (size_t i = 1; i < n; i++) {
		for (size_t j = i - 1; j-- > 0;) {
			if (arr[i] < arr[j])
				swap(&arr[i], &arr[i - 1]);
		}
	}

}

