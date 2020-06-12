#include "InputHdl.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

void getWires(char*[], unsigned short[][4], int);
int getWireValue(char*, unsigned short[][4]);
int getAction(char*);
int bitwise(char*[], unsigned short[][4], int);
int getLastPos(unsigned short[][4]);
int getWireIndex(char*, unsigned short[][4]);
void initWires(unsigned short[][4]);
int concatInt(int, int);
void printWires(unsigned short[][4]);
bool isCompleted(unsigned short[][4]);


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
		return 0;
	}
	
	printf("%s\n---------------------------------------\n", input);
	int len = calcLen(input, ' ');
	char* array[len];
	separateStr(input, array, " ", len);
	
	unsigned short wires[677][4] = {{}, {}, {}};
	initWires(wires);
	getWires(array, wires, len);

	
	for (int i = 0; i < len; i++)
	{
		if (getAction(array[i]) == 1 && (getAction(array[i - 1]) == 2 || i == 0) && getAction(array[i + 1]) == 3)
		{
			wires[getWireIndex(array[i + 2], wires)][1] = atoi(array[i]);
			wires[getWireIndex(array[i + 2], wires)][2] = 1;
		}
	}
	
	while (!isCompleted(wires))
	{
		for (int i = 0; i < len; i++)
		{
			if (getAction(array[i]) == 2 && (getAction(array[i - 1]) == 2 || i == 0) && getAction(array[i + 1]) == 3)
			{
				if (wires[getWireIndex(array[i], wires)][2] == 1)
				{
					wires[getWireIndex(array[i + 2], wires)][1] = wires[getWireIndex(array[i], wires)][1];
					wires[getWireIndex(array[i + 2], wires)][2] = 1;
				}
			}
		}


		for (int i = 0; i < len; i++)
		{
			if (getAction(array[i]) == 0)
			{
				if ((strcmp(array[i], "AND") == 0) || (strcmp(array[i], "OR") == 0))
				{
					if ((wires[getWireIndex(array[i - 1], wires)][2] == 1 || getAction(array[i - 1]) == 1) && (wires[getWireIndex(array[i + 1], wires)][2] == 1 || getAction(array[i + 1]) == 1))
					{
						wires[getWireIndex(array[i + 3], wires)][1] = bitwise(array, wires, i);
						wires[getWireIndex(array[i + 3], wires)][2] = 1;
					}
				}
				if ((strcmp(array[i], "NOT") == 0))
				{
					if (wires[getWireIndex(array[i + 1], wires)][2] == 1 || getAction(array[i + 1]) == 1)
					{
						wires[getWireIndex(array[i + 3], wires)][1] = bitwise(array, wires, i);
						wires[getWireIndex(array[i + 3], wires)][2] = 1;
					}
				}

				if ((strcmp(array[i], "LSHIFT") == 0) || (strcmp(array[i], "RSHIFT") == 0))
				{
					if (wires[getWireIndex(array[i - 1], wires)][2] == 1 || getAction(array[i - 1]) == 1)
					{
						wires[getWireIndex(array[i + 3], wires)][1] = bitwise(array, wires, i);
						wires[getWireIndex(array[i + 3], wires)][2] = 1;
					}
				}
			}
		}
	}
	
	printWires(wires);
	
	printf("\n---------------------------------------\n\n");
	
	for (int i = 0; wires[i][0] != '\0'; i++)
		wires[i][2] = 0;
	
	for (int i = 0; i < len; i++)
	{
		if (getAction(array[i]) == 1 && (getAction(array[i - 1]) == 2 || i == 0) && getAction(array[i + 1]) == 3)
		{
			wires[getWireIndex(array[i + 2], wires)][1] = atoi(array[i]);
			wires[getWireIndex(array[i + 2], wires)][2] = 1;
		}
	}
	
	wires[getWireIndex("b", wires)][1] = 16076;
	
	while (!isCompleted(wires))
	{
		for (int i = 0; i < len; i++)
		{
			if (getAction(array[i]) == 2 && (getAction(array[i - 1]) == 2 || i == 0) && getAction(array[i + 1]) == 3 && strcmp(array[i + 2], "b") != 0)
			{
				if (wires[getWireIndex(array[i], wires)][2] == 1)
				{
					wires[getWireIndex(array[i + 2], wires)][1] = wires[getWireIndex(array[i], wires)][1];
					wires[getWireIndex(array[i + 2], wires)][2] = 1;
				}
			}
		}


		for (int i = 0; i < len; i++)
		{
			if (getAction(array[i]) == 0 && strcmp(array[i + 2], "b") != 0)
			{
				if ((strcmp(array[i], "AND") == 0) || (strcmp(array[i], "OR") == 0))
				{
					if ((wires[getWireIndex(array[i - 1], wires)][2] == 1 || getAction(array[i - 1]) == 1) && (wires[getWireIndex(array[i + 1], wires)][2] == 1 || getAction(array[i + 1]) == 1))
					{
						wires[getWireIndex(array[i + 3], wires)][1] = bitwise(array, wires, i);
						wires[getWireIndex(array[i + 3], wires)][2] = 1;
					}
				}
				if ((strcmp(array[i], "NOT") == 0))
				{
					if (wires[getWireIndex(array[i + 1], wires)][2] == 1 || getAction(array[i + 1]) == 1)
					{
						wires[getWireIndex(array[i + 3], wires)][1] = bitwise(array, wires, i);
						wires[getWireIndex(array[i + 3], wires)][2] = 1;
					}
				}

				if ((strcmp(array[i], "LSHIFT") == 0) || (strcmp(array[i], "RSHIFT") == 0))
				{
					if (wires[getWireIndex(array[i - 1], wires)][2] == 1 || getAction(array[i - 1]) == 1)
					{
						wires[getWireIndex(array[i + 3], wires)][1] = bitwise(array, wires, i);
						wires[getWireIndex(array[i + 3], wires)][2] = 1;
					}
				}
			}
		}
	}
	
	printWires(wires);
	return 0;
}

void getWires(char* input[], unsigned short dest[][4], int len)
{
	for (int i = 0; i < len; i++)
	{
		int act = getAction(input[i]);
		bool repeated = false;
		int charNum = 0;
		int destLen = getLastPos(dest);
		for (int j = 0; j < destLen; j++)
		{
			if (act == 2)
			{
				charNum = strlen(input[i]);
				switch (charNum)
				{
					case 1:
						if ((int)input[i][0] - 86 == dest[j][0])
							repeated = true;
						break;
					case 2:
						if (dest[j][0] == concatInt((int)input[i][0] - 86, (int)input[i][1] - 86))
							repeated = true;
						break;
				}
			}
		}
		
		charNum = strlen(input[i]);

		int pos = getLastPos(dest);
		if (!repeated && act == 2)
		{
			switch (charNum)
			{
				case 1:
					dest[pos][0] = (int)input[i][0] - 86;
					break;
				case 2:
					dest[pos][0] = concatInt((int)input[i][0] - 86, (int)input[i][1] - 86);
					break;
			}
		}
	}
}

int getWireValue(char* str, unsigned short wires[][4])
{
	for (int i = 0; wires[i][0] != 0; i++)
	{
		switch (strlen(str))
		{
			case 1:
				if ((int)str[0] - 86 == wires[i][0])
					return wires[i][1];
				break;
			case 2:
				if (concatInt((int)str[0] - 86, (int)str[1] - 86) == wires[i][0])
					return wires[i][1];
				break;
		}
	}
	
	return -1;
}

int getAction(char* str)
{
	if (str[0] > 64 && str[0] < 91)
		return 0;					// B!TW|SE OPER&T|ON
	if (isdigit(str[0]) != 0)
		return 1;					// N0MBER
	if (str[0] > 96 && str[0] < 123)
		return 2;					// lowercase CHARACTER
	
	return 3;						// ->
}

int getLastPos(int unsigned short array[][4])
{
	for (int i = 0; i < 677; i++)
	{
		if (array[i][0] == 0)
			return i;
	}
	return -1;
}

int bitwise(char* str[], unsigned short wires[][4], int pos)
{
	if (strcmp(str[pos], "AND") == 0)
	{
		if (getAction(str[pos - 1]) == 1 && getAction(str[pos + 1]) == 1)
			return atoi(str[pos - 1]) & atoi(str[pos + 1]);
		else if (getAction(str[pos - 1]) == 1)
			return atoi(str[pos - 1]) & getWireValue(str[pos + 1], wires);
		else if (getAction(str[pos + 1]) == 1)
			return getWireValue(str[pos - 1], wires) & atoi(str[pos + 1]);
		else
			return getWireValue(str[pos - 1], wires) & getWireValue(str[pos + 1], wires);
	}
	
	if (strcmp(str[pos], "OR") == 0)
	{
		if (getAction(str[pos - 1]) == 1 && getAction(str[pos + 1]) == 1)
			return atoi(str[pos - 1]) | atoi(str[pos + 1]);
		else if (getAction(str[pos - 1]) == 1)
			return atoi(str[pos - 1]) | getWireValue(str[pos + 1], wires);
		else if (getAction(str[pos + 1]) == 1)
			return getWireValue(str[pos - 1], wires) | atoi(str[pos + 1]);
		else
			return getWireValue(str[pos - 1], wires) | getWireValue(str[pos + 1], wires);
	}
	
	if (strcmp(str[pos], "NOT") == 0)
	{
		if (getAction(str[pos + 1]) == 1)
			return ~atoi(str[pos + 1]);
		else
			return ~getWireValue(str[pos + 1], wires);
	}
	
	if (strcmp(str[pos], "LSHIFT") == 0)
	{
		if (getAction(str[pos - 1]) == 1)
			return atoi(str[pos - 1]) << atoi(str[pos + 1]);
		else
			return getWireValue(str[pos - 1], wires) << atoi(str[pos + 1]);
	}
	
	if (strcmp(str[pos], "RSHIFT") == 0)
	{
		if (getAction(str[pos - 1]) == 1)
			return atoi(str[pos - 1]) >> atoi(str[pos + 1]);
		else
			return getWireValue(str[pos - 1], wires) >> atoi(str[pos + 1]);
	}
		
	return -1;
}

int getWireIndex(char* str, unsigned short wires[][4])
{
	int numVal;
	switch (strlen(str))
	{
		case 1:
			numVal = (int)str[0] - 86;
			for (int i = 0; wires[i][0] != 0; i++)
			{
				if (wires[i][0] == numVal)
					return i;
			}
			break;
		case 2:
			numVal = concatInt((int)str[0] - 86, (int)str[1] - 86);
			for (int i = 0; wires[i][0] != 0; i++)
			{
				if (wires[i][0] == numVal)
					return i;
			}
	}
	return -1;
}

void initWires(unsigned short array[][4])
{
	for (int i = 0; i < 676; i++)
	{
		array[i][0] = 0;
		array[i][1] = 0;
		array[i][2] = 0;
	}
}

int concatInt(int num1, int num2)
{
	char str[8];
	sprintf(str, "%d%d", num1, num2);
	return atoi(str);
}

void printWires(unsigned short wires[][4])
{
	for(int i = 97; i < 123; i++)
	{
		char wire[2];
		sprintf(wire, "%c", i);
		if (wires[getWireIndex(wire, wires)][2] == 1)
		{
			printf("%s. %d (%d)\n", wire, wires[getWireIndex(wire, wires)][1], wires[getWireIndex(wire, wires)][2]);
		}
	}
	
	for(int i = 97; i < 123; i++)
	{
		for(int j = 97; j < 123; j++)
		{
			char wire[3];
			sprintf(wire, "%c%c", i, j);
			if (wires[getWireIndex(wire, wires)][2] == 1)
			{
				printf("%s. %d (%d)\n", wire, wires[getWireIndex(wire, wires)][1], wires[getWireIndex(wire, wires)][2]);
			}
		}
	}
}

bool isCompleted(unsigned short wires[][4])
{
	for (int i = 0; wires[i][0] != '\0'; i++)
	{
		if (wires[i][2] == 0 && wires[i][0] != 0)
			return false;
	}
	return true;
}