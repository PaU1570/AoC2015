#include <stdbool.h>
/* This is a dynamic array of pointers to strings. The array needs to be resized to contain enough pointers, and each pointer needs to allocate enough memory to hold the string being assigned to it. */

typedef struct {
	int used;
	int capacity;
	char** array;
} dynArray;

void dynInitArray(dynArray *a, int initialSize)
{
	a->array = malloc(initialSize * sizeof * a->array);
	a->used = 0;
	a->capacity = initialSize;
}

void dynAppend(dynArray *a, char* str)
{
	if(a->used == a->capacity) // Check if the array is full. In that case, double the capacity and reallocate memory.
	{
		a->capacity *= 2;
		a->array = realloc(a->array, a->capacity * sizeof * a->array);
	}
	
	a->array[a->used] = malloc(sizeof(char) * (strlen(str) + 1)); // Allocate the memory needed to store the string (+ \0).
	strcpy(a->array[a->used], str);						 // Copy the string to the first available element in the array.
	
	a->used++; // Increase the count of used slots.
}

void dynFreeArray(dynArray *a)
{
	for(int i = 0; i < a->used; i++)  // All the allocated memory for the strings needs to be freed first.
	{
		free(a->array[i]);
	}
	free(a->array);				   // Then we can free the array of pointers.
	a->array = NULL;
	a->used = 0;
	a->capacity = 0;
}

char* dynGetStr(dynArray *a, int index)
{
	if(index < 0 || index > a->used - 1)
	{
		printf("Index number out of bounds!");
		return NULL;
	}
	
	return a->array[index];
}

void dynTrimArray(dynArray *a)
{
	if(a->used < a->capacity)
	{
		a->capacity = a->used;
		a->array = realloc(a->array, a->capacity * sizeof * a->array);
	}
}

void dynPrintArray(dynArray *a)
{
	for(int i = 0; i < a->used; i++)
	{
		printf("%d - %s\n", i, a->array[i]);
	}
}

bool dynCheckIfContains(dynArray *a, char* str)
{
	for(int i = 0; i < a->used; i++)
	{
		if(strcmp(a->array[i], str) == 0)
			return true;
	}
	return false;
}