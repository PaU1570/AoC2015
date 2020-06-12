#include "strtok_r.h"
#include "InputHdl.h"

int get_sizes (int**, char*);	//	Returns the number of sizes.
int get_sum (int*, int*, int);
void init_combination (int*, int);
int next_combination (int*, int);	//	Returns 1 if the combination passed is the last one (i.e. all 1s); 0 otherwise.
int containers_used (int*, int);

int main (const int arcg, const char **argv)
{
	char *input = getStrc((char*)argv[1]);
	if (input == NULL)
	{
		fprintf(stderr, "Couldn't read file \"%s\".", argv[1]);
		return -1;
	}
	
	int *sizes = malloc(sizeof(int));
	int size_num = get_sizes(&sizes, input);
	int *combination = malloc(sizeof(int) * size_num);
	init_combination(combination, size_num);
	
	int count = 0, min_count = 0, min = size_num;						//	'count' stores the number of combinations that add up to 150, 'min_count' stores the number of combinations with the minimum amount of containers, stored in 'min'.
	while (next_combination(combination, size_num) != 1)				//	For each combination until the last one... (it's not necessary to count the last one, because if the last combination (using all of the boxes)
	{																	//	adds up to 150, no other combination will (because you would need all of the boxes))... 				
		if (get_sum(sizes, combination, size_num) == 150)				//		...if it adds up to 150...
		{
			int used = containers_used(combination, size_num);			//			...the number of containers used is stored in 'used'.
			if (used < min)												//			...if 'used' is smaller than 'min'...
			{
				min = used;												//				...set 'min' to 'used', and (re)set the 'min_count' to 1.
				min_count = 1;
			}
			else if (used == min)										//			...if 'used' is equal to 'small'...
			{
				min_count++;											//				...increment 'min_count'.
			}
			for (int i = 0; i < size_num; i++)							//			...and print the combination.
			{
				printf("%d ", combination[i]);
			}
			printf("---> 150 (number %d)\n", count++);
		}
	}
	printf("There are %d possible combinations that add up to 150.\nThe smallest number of containers you can use is %d, and there are %d combinations using that number.\n", count, min, min_count);
	
	return 0;
}

int get_sizes (int **sizes, char *input)
{
	char *token = strtok(input, "\n");
	(*sizes)[0] = atoi(token);
	int i;
	for (i = 1; token != NULL; i++)
	{
		token = strtok(NULL, "\n");
		*sizes = realloc(*sizes, sizeof(int) * (i + 1));
		(*sizes)[i] = atoi(token);
	}
	return i - 1;
}

int get_sum (int *array, int *combination, int array_size)
{
	int sum = 0;
	for (int i = 0; i < array_size; i++)
	{
		if (combination[i] == 1)
		{
			sum += array[i];
		}
	}
	return sum;
}

void init_combination (int *combination, int size)
{
	for (int i = 0; i < size; i++)
	{
		combination[i] = 0;
	}
}

int next_combination (int *combination, int size)
{
	int is_last = 1;
	for (int i = 0; i < size; i++)
	{
		if (combination[i] == 0)
		{
			is_last = 0;
		}
	}
	if (is_last == 1)
	{
		return 1;
	}
	
	for (int i = size - 1; i >= 0; i--)
	{
		switch (combination[i])
		{
			case 0 :
				combination[i] = 1;
				return 0;
			case 1 :
				combination[i] = 0;
				break;
		}
	}
}

int containers_used (int *combination, int size)
{
	int containers = 0;
	for (int i = 0; i < size; i++)
	{
		if (combination[i] == 1)
		{
			containers++;
		}
	}
	return containers;
}