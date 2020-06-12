#include "InputHdl.h"

void turnOn(int[1000][1000], int[3][3]);
void turnOff(int[1000][1000], int[3][3]);
void toggle(int[1000][1000], int[3][3]);

int getAction(char*);
void initGrid(int[1000][1000]);
void getCoordinates(char*[], int[3][3], int);

int countLights(int[1000][1000]);
int countBright(int[1000][1000]);

void brightUp(int[1000][1000], int[3][3]);
void brightDown(int[1000][1000], int[3][3]);
void toggleBright(int[1000][1000], int[3][3]);

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	
	char* input = getStrl(argv[1]);
	if (input == NULL)
	{
		printf("Could not read file.\n");
		return 1;
	}
	
	int len = calcLen(input, ' ') + calcLen(input, ',') - 1;
	char* array[len];
	separateStr(input, array, " ,", len);

	int grid[1000][1000];
	initGrid(grid);
	
	int coordinates[3][3] = {{0, 0}, {0, 0}};
	for (int i = 0; i < len; i++)
	{
		switch (getAction(array[i]))
		{
			case 3:
				break;
			case 0:
				getCoordinates(array, coordinates, i);
				turnOff(grid, coordinates);
				break;
			case 1:
				getCoordinates(array, coordinates, i);
				turnOn(grid, coordinates);
				break;
			case 2:
				getCoordinates(array, coordinates, i);
				toggle(grid, coordinates);
				break;
		}
	}
	
	printf("Part 1:\nLights ON: %d\n", countLights(grid));
	
	initGrid(grid);
	
	for (int i = 0; i < len; i++)
	{
		switch (getAction(array[i]))
		{
			case 3:
				break;
			case 0:
				getCoordinates(array, coordinates, i);
				brightDown(grid, coordinates);
				break;
			case 1:
				getCoordinates(array, coordinates, i);
				brightUp(grid, coordinates);
				break;
			case 2:
				getCoordinates(array, coordinates, i);
				toggleBright(grid, coordinates);
				break;
		}
	}
	
	printf("\nPart 2:\nTotal BRIGHTNESS: %d\n", countBright(grid));
	
	return 0;
}

void turnOn(int grid[1000][1000], int coordinates[3][3])
{
	for (int y = coordinates[0][1]; y <= coordinates[1][1]; y++)
	{
		for (int x = coordinates[0][0]; x <= coordinates[1][0]; x++)
		{
			grid[x][y] = 1;
		}
	}
}

void turnOff(int grid[1000][1000], int coordinates[3][3])
{
	for (int y = coordinates[0][1]; y <= coordinates[1][1]; y++)
	{
		for (int x = coordinates[0][0]; x <= coordinates[1][0]; x++)
		{
			grid[x][y] = 0;
		}
	}
}

void toggle(int grid[1000][1000], int coordinates[3][3])
{
	for (int y = coordinates[0][1]; y <= coordinates[1][1]; y++)
	{
		for (int x = coordinates[0][0]; x <= coordinates[1][0]; x++)
		{
			if (grid[x][y] == 0)
				grid[x][y] = 1;
			else
				grid[x][y] = 0;
		}
	}
}

int getAction(char* str)
{
	if (strcmp("off", str) == 0)
		return 0; // Run turn off
	else if (strcmp("on", str) == 0)
		return 1; // Run turn on
	else if (strcmp("toggle", str) == 0)
		return 2; // Run toggle.
	else
		return 3; // Continue to next one.
}

void initGrid(int grid[1000][1000])
{
	for (int x = 0; x < 1000; x++)
	{
		for (int y = 0; y < 1000; y++)
		{
			grid[x][y] = 0;
		}
	}
}

void getCoordinates(char* array[], int coordinates[3][3], int pos)
{
	coordinates[0][0] = atoi(array[pos + 1]);
	coordinates[0][1] = atoi(array[pos + 2]);
	coordinates[1][0] = atoi(array[pos + 4]);
	coordinates[1][1] = atoi(array[pos + 5]);
}

int countLights(int grid[1000][1000])
{
	int count = 0;
	for (int y = 0; y < 1000; y++)
	{
		for (int x = 0; x < 1000; x++)
		{
			if (grid[x][y] == 1)
				count++;
		}
	}
	return count;
}

int countBright(int grid[1000][1000])
{
	int count = 0;
	for (int y = 0; y < 1000; y++)
	{
		for (int x = 0; x < 1000; x++)
		{
			count += grid[x][y];
		}
	}
	return count;
}

void brightUp(int grid[1000][1000], int coordinates[3][3])
{
	for (int y = coordinates[0][1]; y <= coordinates[1][1]; y++)
	{
		for (int x = coordinates[0][0]; x <= coordinates[1][0]; x++)
		{
			grid[x][y]++;
		}
	}
}

void brightDown(int grid[1000][1000], int coordinates[3][3])
{
	for (int y = coordinates[0][1]; y <= coordinates[1][1]; y++)
	{
		for (int x = coordinates[0][0]; x <= coordinates[1][0]; x++)
		{
			if (grid[x][y] != 0)
				grid[x][y]--;
		}
	}
}

void toggleBright(int grid[1000][1000], int coordinates[3][3])
{
	for (int y = coordinates[0][1]; y <= coordinates[1][1]; y++)
	{
		for (int x = coordinates[0][0]; x <= coordinates[1][0]; x++)
		{
			grid[x][y] += 2;
		}
	}
}
