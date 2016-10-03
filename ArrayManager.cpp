/*
 * ArrayManager.cpp
 *
 *  Created on: 1. okt 2016
 *      Author: Merily
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <time.h>
using namespace std;


bool contains(int array[], int target, int length){
	for (int i = 0; i<length; i++)
		if (array[i] == target)
			return true;
	return false;
}

void generateArray (int array[], int length, int from, int to){
	srand(time(0));
	for (int i = 0; i<length; i++){
		int random;
		do {
			random = from + (rand() % to);
		} while (contains(array, random, i));
		array[i] = random;
	}
}

void bubbleSort (int array[], int length){
	for (int i = 0; i<length-1; i++){
		for (int j = 1; j<length-i; j++){
			if (array[j-1] > array[j]){
				int tmp = array[j-1];
				array[j-1] = array[j];
				array[j] = tmp;
			}
		}
	}
}

int main(){

	int len = 15;
	int unsorted[len];
	generateArray(unsorted, len, 0, 100);


	cout << "Unsorted: ";
	for (int i = 0 ; i<len; i++)
		cout << unsorted[i] << "; ";
	cout << endl;

	int unsortedCopy[len];
	std::copy (unsorted, unsorted + sizeof(unsorted), unsortedCopy);


	clock_t start = clock();

	sort(unsorted, unsorted + len);
	cout << "  Sorted: ";
	for (int i = 0 ; i<len; i++)
		cout << unsorted[i] << "; ";
	cout << endl;

	clock_t end = clock();
	cout << "sort() time: " << end-start << " clicks" << endl;

	start = clock();

	bubbleSort(unsortedCopy, len);
	cout << "  Sorted: ";
	for (int i = 0 ; i<len; i++)
		cout << unsortedCopy[i] << "; ";
	cout << endl;

	end = clock();
	cout << "bubbleSort() time: " << end-start << " clicks" << endl;

	return EXIT_SUCCESS;
}





