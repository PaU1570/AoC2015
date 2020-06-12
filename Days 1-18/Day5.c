#include "InputHdl.h"
#include <stdbool.h>

bool containsDisallowed(char*);
bool containsRepeated(char*);
int vowelCount(char*);
bool containsPair(char*);
bool containsRepBet(char*);
bool isNice(int, char*);

int main(int argc, char* argv[])
{
	int part = atoi(argv[1]);
	
	if (argc != 3 || (part != 1 && part != 2))
	{
		printf("Usage: %s [part(1 or 2)] [filename]\n", argv[0]);
		return 1;
	}
	
	char* str = getStrl(argv[2]);
	if (str == NULL)
	{
		printf("Could not read file.\n");
		return 1;
	}
	
	char* saveptr;
	int len = calcLen(str, ' ');
	char* array[len];
	initArray(array, len);

	array[0] = strtok_r(str, " ", &saveptr);
	for(int i = 1; i < len ; i++)
	{
		array[i] = strtok_r(NULL, " ", &saveptr);
	}
	
	int niceStr = 0, naughtyStr = 0;
	
	for (int i = 0; i < len; i++)
	{	
		printf("%s --> ", array[i]);
		if (isNice(part, array[i]))
		{
			printf("NICE\n");
			niceStr++;
		}
		else
		{
			printf("NAUGHTY\n");
			naughtyStr++;
		}
	}
	
	printf("Nice strings: %d\nNaughty strings: %d\n", niceStr, naughtyStr);
		
	return 0;
}

bool containsDisallowed(char* str)
{
	char ab[3] = {'a', 'b'};
	char cd[3] = {'c', 'd'};
	char pq[3] = {'p', 'q'};
	char xy[3] = {'x', 'y'};
	
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == ab[0] && str[i+1] == ab[1])
			return true;
		if (str[i] == cd[0] && str[i+1] == cd[1])
			return true;
		if (str[i] == pq[0] && str[i+1] == pq[1])
			return true;
		if (str[i] == xy[0] && str[i+1] == xy[1])
			return true;
	}
	
	return false;
}

bool containsRepeated(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == str[i+1])
			return true;
	}
	return false;
}

int vowelCount(char* str)
{
	int count = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == 97 || str[i] == 101 || str[i] == 105 || str[i] == 111 || str[i] == 117)
		{
			count++;
		}
	}
	return count;
}

bool containsPair(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		char pair[3] = {str[i], str[i+1]};
		for (int j = i + 2; j < strlen(str) - 1; j++)
		{
			if (pair[0] == str[j] && pair[1] == str[j+1])
				return true;
		}
	}
	return false;
}

bool containsRepBet(char* str)
{
	for (int i = 0; str[i+2] != '\0'; i++)
	{
		if (str[i] == str[i+2])
			return true;
	}
	return false;
}

bool isNice(int part, char* str)
{
	if (vowelCount(str) >= 3 && containsRepeated(str) && !containsDisallowed(str) && part == 1)
		return true;
	if (containsPair(str) && containsRepBet(str) && part == 2)
		return true;
	return false;
}