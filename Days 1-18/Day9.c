/*
 * day9.c
 *
 *  Created on: Aug 18, 2017
 *      Author: paulu
 */

#include <stdio.h>



void permutate(int, int[8], int[28][2]);	// Heap's algorithm.
void swap(int[8], int, int);	// Swap the items at the given positions of the given array.
int getDistance(int, int, int[28][2]);		// Get the distance between to numbers/cities.
int getTotalDistance(int[8], int[28][2]);	// Get the total distance from an 8-digit combination.
static int shortestDistance = 1000, longestDistance = 0;

int main () {

	int distances[28][2] = { // The first column represents two cities (e.g. "15" means from/to city 1, Tristram; to/from city 5, Faerun). The second column represents the distance between those two cities.
				{12, 34},
				{13, 100},
				{14, 63},
				{15, 108},
				{16, 111},
				{17, 89},
				{18, 132},
				{23, 4},
				{24, 79},
				{25, 44},
				{26, 147},
				{27, 133},
				{28, 74},
				{34, 105},
				{35, 95},
				{36, 48},
				{37, 88},
				{38, 7},
				{45, 68},
				{46, 134},
				{47, 107},
				{48, 40},
				{56, 11},
				{57, 66},
				{58, 144},
				{67, 115},
				{68, 135},
				{78, 127}
		};

	int testarray[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	permutate(8, testarray, distances);
	printf("Shortest path distance: %d\n", shortestDistance);
	printf("Longest path distance: %d\n", longestDistance);

	return 0;
}

void permutate(int n, int array[8], int distances[28][2]) {	// Heap's algorithm.


	if (n == 1) {
		int totalDistance = getTotalDistance(array, distances);
		if (totalDistance < shortestDistance) {
			shortestDistance = totalDistance;
			printf("S %d%d%d%d%d%d%d%d ---> %d\n", array[0], array[1], array[2], array[3], array[4], array[5], array[6], array[7], totalDistance);
		}
		if (totalDistance > longestDistance) {
					longestDistance = totalDistance;
					printf("L %d%d%d%d%d%d%d%d ---> %d\n", array[0], array[1], array[2], array[3], array[4], array[5], array[6], array[7], totalDistance);
				}
	}

	else {
		for (int i = 0; i < n; i++) {
			permutate(n - 1, array, distances);

			if (n % 2 != 0)
				swap(array, 0, n - 1);

			else
				swap(array, i, n - 1);
		}
	}
}

void swap(int array[8], int a, int b) {
	int tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

int getDistance(int city1, int city2, int distances[28][2]) {
	int cities12 = (city1 * 10) + city2;
	int cities21 = (city2 * 10) + city1;

	for (int i = 0; i < 28; i++) {
		if (distances[i][0] == cities12 || distances[i][0] == cities21) {
			return distances[i][1];
		}
	}
	return 0;
}

int getTotalDistance(int combination[8], int distances[28][2]) {
	int totalDistance = 0;
	for (int i = 0; i < 7; i++) {
		totalDistance += getDistance(combination[i], combination[i + 1], distances);
	}
	return totalDistance;
}
