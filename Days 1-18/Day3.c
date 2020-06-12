#include "InputHdl.h"
#include <stdbool.h>

bool isRepeated (int[][2], int, int, int);
void initGrid (int[][2], int);
void logLocation (int[][2], int, int, int);

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	
	char* input = getStrc(argv[1]);
	if (input == NULL)
	{
		printf("Could not read file.\n");
		return 1;
	}
	
	int len = strlen(input);
	int array[len][2];
	initGrid(array, len);
	
	int x = 0, x2 = 0, y = 0, y2 = 0, uniques = 1;
	logLocation(array, 0, x, y);
	for (int i = 1; i < len; i++)
	{
		switch (input[i-1])
		{
			case '^':
				y++;
				break;
				
			case 'v':
				y--;
				break;
				
			case '>':
				x++;
				break;
				
			case '<':
				x--;
				break;
		}
		
		if (!isRepeated(array, x, y, len))
		{
			logLocation(array, i, x, y);
			++uniques;
		}
	}
	printf ("Part 1: Unique houses: %d\n", uniques);

	x = 0;
	y = 0;
	uniques = 1;
	initGrid(array, len);
	
	for (int i = 1; i < len; i++)
	{
		switch (input[i-1])
		{
			case '^':
				if(i % 2 == 0)
					y++;
				else
					y2++;
				break;
				
			case 'v':
				if(i % 2 == 0)
					y--;
				else
					y2--;
				break;
				
			case '>':
				if(i % 2 == 0)
					x++;
				else
					x2++;
				break;
				
			case '<':
				if(i % 2 == 0)
					x--;
				else
					x2--;
				break;
		}
		
		switch (i % 2)
		{
			case 0:
				if (!isRepeated(array, x, y, len))
				{
					logLocation(array, i, x, y);
					++uniques;
				}
				break;
				
			case 1:
				if (!isRepeated(array, x2, y2, len))
				{
					logLocation(array, i, x2, y2);
					++uniques;
				}
		}
		
	}
	
	printf ("Part 2: Unique houses: %d\n", uniques);
	
	return 0;
}

bool isRepeated (int array[][2], int x, int y, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (array[i][0] == x && array[i][1] == y)
			return true;
	}
	return false;
}

void initGrid(int array[][2], int len)
{
	for (int i = 0; i < len; i++)
	{
		array[i][0] = 0;
		array[i][1] = 0;
	}
}

void logLocation (int array[][2], int i, int x, int y)
{
	array[i][0] = x;
	array[i][1] = y;
}