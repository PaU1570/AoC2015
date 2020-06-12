#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "InputHdl.h"


int getSmallest (int, int, int);
int calcArea (int, int, int);
int getTotalArea (int[], int);
int calcRibbon (int, int, int);
int getTotalRibbon (int[], int);

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	
	char* line = getStrl(argv[1]);
	if (line == NULL)
	{
		printf("Could not read file.\n");
		return 1;
	}
	
	char* saveptr;
	int len = calcLen(line, ' ') * 3;
	int array[len];
	for (int i = 0; i < len; i++)
	{
		array[i] = 0;
	}
	
	array[0] = atoi(strtok_r(line, "x ", &saveptr));
	for(int i = 1; i < len ; i++)
	{
		array[i] = atoi(strtok_r(NULL, "x ", &saveptr));
	}
	
	int totalArea = getTotalArea(array, len);
	int totalRibbon = getTotalRibbon(array, len);
	printf("Total area needed: %d sq feet.\n", totalArea);
	printf("Total ribbon neded: %d feet.\n", totalRibbon);
		
	return 0;
}


int getSmallest (int a, int b, int c)
{
	int smallest;
	if (a < b)
		smallest = a;
	else
		smallest = b;
	
	if (smallest > c)
		smallest = c;
	
	return smallest;
}

int calcArea (int w, int h, int l)
{
	int area = (2*l*w) + (2*w*h) + (2*h*l);
	int extra = getSmallest((l*w), (w*h), (h*l));
	
	return area + extra;	
}

int getTotalArea (int array[], int len)
{
	int totalArea = 0;
	
	int num1, num2, counter = 0;
	for (int i = 0; i < len; i++)
	{
		switch (counter)
		{
			case 0:
				num1 = array[i];
				counter++;
				break;
				
			case 1:
				num2 = array[i];
				counter++;
				break;
				
			case 2:
				totalArea += calcArea (num1, num2, array[i]);
				counter = 0;
				break;
				
		}
	}
	
	return totalArea;
}

int calcRibbon (int w, int h, int l)
{
	int total = w * h * l;
	total += getSmallest(2*w+2*h, 2*h+2*l, 2*l+2*w);
	return total;
}

int getTotalRibbon (int array[], int len)
{
	int totalRib = 0;
	
	int num1, num2, counter = 0;
	for (int i = 0; i < len; i++)
	{
		switch (counter)
		{
			case 0:
				num1 = array[i];
				counter++;
				break;
				
			case 1:
				num2 = array[i];
				counter++;
				break;
				
			case 2:
				totalRib += calcRibbon (num1, num2, array[i]);
				counter = 0;
				break;
				
		}
	}
	
	return totalRib;
}