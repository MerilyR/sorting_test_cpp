/*
 * ArrayManager.cpp
 *
 *  Created on: 1. okt 2016
 *      Author: Merily
 */
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <Windows.h>
using namespace std;

/*
 * Check if array of specified length has the integer
 */
bool contains(int array[], int target, int length){
	for (int i = 0; i<length; i++)
		if (array[i] == target)
			return true;
	return false;
}

/*
 * Generate an array of distinct random integers
 *
 * length - length of array
 * from - the smallest possible integer
 * to - the largest possible integer
 */
void generateArray (int array[], int length, int from, int to){
	int random;
	for (int i = 0; i<length; i++){
		do {
			random = from + (rand() % to);
		} while (contains(array, random, i));
		array[i] = random;
	}
}

/*
 * bubble type sorting algorithm
 */
void bubbleSort (int array[], int length){
	int tmp;
	int n = length;
	int newn;
	do{
		newn = 0;
		for (int j = 1; j<n; j++){
			if (array[j-1] > array[j]){
				tmp = array[j-1];
				array[j-1] = array[j];
				array[j] = tmp;
				newn = j;
			}
		}
		n = newn;
	} while (n != 0);
}

/*
 * swap integers in an array
 *
 * first index - of the element to be swapped with the element of second index
 */
void swapInts (int array[], int firstindex, int secondindex){
	int tmp = array[firstindex];
	array[firstindex] = array[secondindex];
	array[secondindex] = tmp;
}

/*
 * sift down method for heap sorting
 */
void siftDown (int array[], int start, int end){
	int root = start;
	while (root*2+1 <= end ){
		int child = root * 2 + 1;
		int swap = root;
		if (array[swap] < array[child])
			swap = child;
		if (child + 1 <= end && array[swap] < array[child+1])
			swap = child+1;
		if (swap != root){
			swapInts (array, root, swap);
			root = swap;
		}
		else
			return;
	}
}

/*
 * heapify method for heap sort
 */
void heapify (int array[], int count) {
	int start = count / 2 - 1;
	while (start >= 0 ) {
		siftDown (array, start, count-1);
		start = start - 1;
	}
}

/*
 * heap type sorting algorithm
 */
void heapSort (int array[], int length) {
	heapify (array, length);
	int end = length - 1;
	while (end > 0) {
		swapInts (array, end, 0);
		end = end - 1;
		siftDown (array, 0, end);
	}
}

/*
 * binary search from array
 */
int binarySearch (int array[], int target, int length) {
	int l = 0;
	int r = length - 1;
	int m;
	while (l <= r) {
		m = (l+r)/2;
		if (array[m] == target)
			return m;
		else if (array[m] < target) {
			l = m+1;
		}
		else if (array[m] > target) {
			r = m-1;
		}
	}
	return -1;
}

int main(){
	// seed random with time to make randoms really random
	srand((unsigned)time(NULL));
	int len = 2000;
	int array[len];
	//int unsortedCopyBubble[len];
	//int unsortedCopyHeap[len];

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER start;
	LARGE_INTEGER end;

    double sortingTime, searchingTime;

	for(int tc = 0; tc<5; tc++) {

		generateArray(array, len, 0, 65000);

		/*//make copies for other sorting methods
		std::copy(unsorted, unsorted + len, unsortedCopyBubble);
		std::copy(unsorted, unsorted + len, unsortedCopyHeap);
*/

		cout << "Sorting new generated array ..." << endl;
		QueryPerformanceCounter(&start);

		sort(array, array + len);

		QueryPerformanceCounter(&end);

		sortingTime = static_cast<double>(end.QuadPart- start.QuadPart) / (frequency.QuadPart/1000000.0);
		printf(" std::sort() time: %.2f microseconds \n", sortingTime);

		cout << "array: ";
		for (int m = 0; m < len; m++) {
			if (m % 200 == 0)
				cout << "\n";
			cout << array[m] << ";";
		}
		cout << endl;

/*		//other sorting methods
		QueryPerformanceCounter(&start);

		bubbleSort(unsortedCopyBubble, len);

		QueryPerformanceCounter(&end);

		interval = static_cast<double>(end.QuadPart- start.QuadPart) / (frequency.QuadPart/1000000.0);
		printf("bubbleSort() time: %.2f microseconds \n", interval);

		QueryPerformanceCounter(&start);

		heapSort(unsortedCopyHeap, len);

		QueryPerformanceCounter(&end);

		interval = static_cast<double>(end.QuadPart- start.QuadPart) / (frequency.QuadPart/1000000.0);
		printf("  heapSort() time: %.2f microseconds \n\n", interval);
*/

		int response = 0;
		int index;
		cout << "Insert value to search..." << endl;
		cin >> response;

		while (cin.fail()) {
			cout << "Not an integer! Try again..." << endl;
			cin.clear();
			cin.ignore(256,'\n');
			cin >> response;
		}

		cout << "Searching for " << response << " ..." << endl;
		QueryPerformanceCounter(&start);
		index = binarySearch(array, response, len);
		QueryPerformanceCounter(&end);
		if (index == -1)
			cout << "Value not found, sowwy"<< endl;
		else
			cout << "Value is on position " << index << endl;

		searchingTime = static_cast<double>(end.QuadPart- start.QuadPart) / (frequency.QuadPart/1000000.0);
		printf("binarySearch() time: %.2f microseconds \n", searchingTime);

		printf ("Sorting and searching (without output printing) took %.2f microseconds.\n\n", sortingTime+searchingTime);

	}

	cout << "End of testcases and also end of file.\n Thanks for playing!";

	return EXIT_SUCCESS;
}





