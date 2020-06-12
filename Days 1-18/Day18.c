#include "strtok_r.h"
#include "InputHdl.h"

#define GRID_SIZE_X 102		//	The grid is bordered by '-1's so that we don't go out of bounds.
#define GRID_SIZE_Y 102

void init_grid (int[GRID_SIZE_X][GRID_SIZE_Y], char*);							//	Initializes the grid with the given input.
int next_step (int[GRID_SIZE_X][GRID_SIZE_Y]);									//	Goes to the next step and returnst the number of lights on.
int toggle_light (int[GRID_SIZE_X][GRID_SIZE_Y], int, int);						//	Returns 1 if the given light should be turned/stayed on, 0 if off.
void copy_grid (int[GRID_SIZE_X][GRID_SIZE_Y], int[GRID_SIZE_X][GRID_SIZE_Y]);	//	Copies the first grid into the second.

int main (const int argc, const char **argv)
{
	char *input = getStrc ((char*)argv[1]);
	if (input == NULL)
	{
		fprintf (stderr, "Couldn't read file \"%s\"", argv[1]);
		return -1;
	}
	
	int grid[GRID_SIZE_X][GRID_SIZE_Y];
	init_grid (grid, input);
	
	int lights_on;
	
	for (int i = 1; i <= 100; i++)
	{
		lights_on = next_step (grid);
		if (i == 1)
		{
			printf ("Lights on after %d step: %d\n", i, lights_on);
		}
		else
		{
			printf ("Lights on after %d steps: %d\n", i, lights_on);
		}
	}
	
	return 0;
}

void init_grid (int grid[GRID_SIZE_X][GRID_SIZE_Y], char *input)
{
	char *line = strtok (input, "\n");
	for (int x = 0; x < GRID_SIZE_X; x++)
	{
		for (int y = 0; y < GRID_SIZE_Y; y++)							
		{
			if ((x == 0 || x == GRID_SIZE_X - 1) || (y == 0 || y == GRID_SIZE_Y - 1))
			{
				grid[x][y] = -1;
			}
			else if (line[y - 1] == '#')
			{
				grid[x][y] = 1;
			}
			else
			{
				grid[x][y] = 0;
			}
		}
		if (x != 0 && x != GRID_SIZE_X - 1)
		{
			line = strtok(NULL, "\n");
		}
	}
	grid[1][1] = 1;									//	Turn
	grid[1][GRID_SIZE_Y - 2] = 1;					//	the
	grid[GRID_SIZE_X - 2][1] = 1;					//	corners
	grid[GRID_SIZE_X - 2][GRID_SIZE_Y - 2] = 1;		//	on.
}

int next_step (int grid[GRID_SIZE_X][GRID_SIZE_Y])
{
	int tmp_grid[GRID_SIZE_X][GRID_SIZE_Y];									//	A temporary grid is created and, lookin' at it, the original grid is changed.
	copy_grid(grid, tmp_grid);
	int lights_on = 0;
	for (int x = 1; x < GRID_SIZE_X - 1; x++)
	{
		for (int y = 1; y < GRID_SIZE_Y - 1; y++)							//	We don't need to iterate through the edges of the grid.
		{
			if (toggle_light(tmp_grid, x, y) == 1)
			{
				grid[x][y] = 1;
				lights_on++;
			}
			else
			{
				grid[x][y] = 0;
			}
		}
	}
	return lights_on;
}

int toggle_light (int grid[GRID_SIZE_X][GRID_SIZE_Y], int x, int y)
{
	if ((x == 1 || x == GRID_SIZE_X - 2) && (y == 1 || y == GRID_SIZE_Y - 2))		//	Keep the light on if it's on the corner.
	{
		return 1;
	}
	int neighbors = 0;
	int current_state = grid[x][y];
	for (int a = (x - 1); a <= (x + 1); a++)
	{
		for (int b = (y - 1); b <= (y + 1); b++)
		{
			if (!((a == x) && (b == y)))
			{
				if (grid[a][b] == 1)
				{
					neighbors++;
				}
			}
		}
	}
	switch (neighbors)
	{
		case 3 :
			return 1;							//	If there are 3 neighbors, light turns/stays on, regardless of current state.
		case 2 :
			if (current_state == 1)				//	If there are 2 neighbors, light only stays on if it was already on.
			{
				return 1;
			}
		default :								//	Any other number of neighbors, the light switches/stays off.
			return 0;
	}
}

void copy_grid (int src[GRID_SIZE_X][GRID_SIZE_Y], int dest[GRID_SIZE_X][GRID_SIZE_Y])
{
	for (int x = 0; x < GRID_SIZE_X; x++)
	{
		for (int y = 0; y < GRID_SIZE_Y; y++)
		{
			dest[x][y] = src[x][y];
		}
	}
}