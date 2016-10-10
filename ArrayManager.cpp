/*
 * ArrayManager.cpp
 *
 *  Created on: 1. okt 2016
 *      Author: Merily
 */
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;

bool contains(int array[], int target, int length){
	for (int i = 0; i<length; i++)
		if (array[i] == target)
			return true;
	return false;
}

void generateArray (int array[], int length, int from, int to){
	int random;
	for (int i = 0; i<length; i++){
		do {
			random = from + (rand() % to);
		} while (contains(array, random, i));
		array[i] = random;
	}
}

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


void swapInts (int array[], int firstindex, int secondindex){
	int tmp = array[firstindex];
	array[firstindex] = array[secondindex];
	array[secondindex] = tmp;
}

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

void heapify (int array[], int count) {
	int start = count / 2 - 1;
	while (start >= 0 ) {
		siftDown (array, start, count-1);
		start = start - 1;
	}
}

void heapSort (int array[], int length) {
	heapify (array, length);
	int end = length - 1;
	while (end > 0) {
		swapInts (array, end, 0);
		end = end - 1;
		siftDown (array, 0, end);
	}
}

int main(){
	srand((unsigned)time(NULL));
	int len = 2000;
	int unsorted[len];
	int unsortedCopyBubble[len];
	int unsortedCopyHeap[len];
	chrono::high_resolution_clock::time_point start_time, end_time;

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER start;
	LARGE_INTEGER end;

    double interval;

	for(int tc = 0; tc<5; tc++) {

		generateArray(unsorted, len, 0, 65000);
		/*
		cout << "Unsorted: ";
		for (int i = 0 ; i<len; i++)
			cout << unsorted[i] << "; ";
		cout << endl;
*/

		//make copies for other sorting methods
		std::copy(unsorted, unsorted + len, unsortedCopyBubble);
		std::copy(unsorted, unsorted + len, unsortedCopyHeap);

		start_time = chrono::high_resolution_clock::now();
		QueryPerformanceCounter(&start);

		sort(unsorted, unsorted + len);
/*
		cout << "  Sorted: ";
		for (int i = 0 ; i<len; i++)
			cout << unsorted[i] << "; ";
		cout << endl;
*/
		end_time = chrono::high_resolution_clock::now();
		QueryPerformanceCounter(&end);

		printf(" std::sort() time: %lld nanoseconds \n", chrono::duration_cast<chrono::nanoseconds>(end_time-start_time).count());
		interval = static_cast<double>(end.QuadPart- start.QuadPart) / (frequency.QuadPart/1000000.0);
		printf(" std::sort() time: %.2f microseconds \n", interval);


		start_time = chrono::high_resolution_clock::now();
		QueryPerformanceCounter(&start);
		/*
		cout << "  Unsorted: ";
		for (int i = 0 ; i<len; i++)
			cout << unsortedCopyBubble[i] << "; ";
		cout << endl;
*/

		bubbleSort(unsortedCopyBubble, len);
/*
		cout << "  Sorted: ";
		for (int i = 0 ; i<len; i++)
			cout << unsortedCopyBubble[i] << "; ";
		cout << endl;
*/
		end_time = chrono::high_resolution_clock::now();
		QueryPerformanceCounter(&end);

		printf("bubbleSort() time: %lld nanoseconds \n", chrono::duration_cast<chrono::nanoseconds>(end_time-start_time).count());
		interval = static_cast<double>(end.QuadPart- start.QuadPart) / (frequency.QuadPart/1000000.0);
		printf("bubbleSort() time: %.2f microseconds \n", interval);

		start_time = chrono::high_resolution_clock::now();
		QueryPerformanceCounter(&start);
		/*
		cout << "  Unsorted: ";
				for (int i = 0 ; i<len; i++)
					cout << unsortedCopyHeap[i] << "; ";
				cout << endl;
*/
		heapSort(unsortedCopyHeap, len);
/*
		cout << "  Sorted: ";
		for (int i = 0 ; i<len; i++)
			cout << unsortedCopyHeap[i] << "; ";
		cout << endl;
*/
		end_time = chrono::high_resolution_clock::now();
		QueryPerformanceCounter(&end);

		printf("  heapSort() time: %lld nanoseconds \n", chrono::duration_cast<chrono::nanoseconds>(end_time-start_time).count());
		interval = static_cast<double>(end.QuadPart- start.QuadPart) / (frequency.QuadPart/1000000.0);
		printf("  heapSort() time: %.2f microseconds \n\n", interval);
	}
	return EXIT_SUCCESS;
}





