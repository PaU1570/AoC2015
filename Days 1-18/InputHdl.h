#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calcLen (char* str, char sep)
{
	int count = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == sep)
			count++;
	}
	return count + 1;
}

void initArray (char* array[], int len)
{
	for (int i = 0; i < len; i++)
	{
		array[i] = 0;
	}
}

void separateStr(char* str, char* array[], char* separator, int arrLen)
{
	
	initArray(array, arrLen);
	
	char* saveptr;
	array[0] = strtok_r(str, separator, &saveptr);
	for(int i = 1; i < arrLen ; i++)
	{
		array[i] = strtok_r(NULL, separator, &saveptr);
	}
}

char* getStrl(char* filename) // removes new lines
{

	FILE* inputf = fopen(filename, "r");
	if (inputf == NULL)
	{
		return "Error reading the file: file is null";
	}
	
	char line[40];
	char* string = malloc(25);
	int len = 0;
	
	while (fscanf(inputf, "%s", line) != EOF)
	{
		len += strlen(line) + 1;
		string = realloc(string, len + 25);
		sprintf(string, "%s%s ", string, line);
	//	printf("%s\n", string);
	}
	
	string[strlen(string) - 1] = 0;
	fclose(inputf);
	char* rstring;
	strcpy(rstring, string);
	free(string);
	return rstring;
}

char* getStrc(char* filename) // keeps new lines
{
	FILE* inputf = fopen(filename, "r");
	if (inputf == NULL)
	{
		return NULL;
	}
	
	char* string = calloc(1, 10);
	
	int c, len = 1;
	while ((c = getc(inputf)) != EOF)
	{
		len++;
		string = realloc(string, len);
		sprintf(string, "%s%c", string, c);
	}
	
	//char* rstring;
	//strcpy(rstring, string);
	//free(string);
	return string;
}