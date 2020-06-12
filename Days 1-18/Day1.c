#include "InputHdl.h"
#include <stdbool.h>

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
	
	int floor = 0;
	int basement;
	
	char position;
	bool isfirst = true;
	
	for (int i = 0; i < strlen(input); i++)
	{
		position = input[i];
		
		if (position == '(')
			floor++;
		else
			floor--;
		
		
		if (floor < 0 && isfirst)
		{
			basement = i;
			isfirst = false;
		}
	}

	
	printf ("Floor %d\nEntered basement on position %d\n", floor, basement + 1);
	
	return 0;
}