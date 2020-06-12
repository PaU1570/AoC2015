#include "InputHdl.h"

void countEscapes(char*, int[2]);

int main (int argc, char* argv[])
{
	char* input = getStrc(argv[1]);
	if (input == NULL)
	{
		printf("Could not read file.\n");
		return 1;
	}
	
	int lines = calcLen(input, '\n');
	int escaped_encodedIncrease[2];
	countEscapes(input, escaped_encodedIncrease);
	
	int escaped = escaped_encodedIncrease[0]; // didn't want to change every 'escaped'
	
	int codelen = strlen(input) - lines + 1;
	int memorylen = codelen - escaped - (lines) * 2;
	
	int result1 = codelen - memorylen;
	
	int result2 = lines * 4 + escaped_encodedIncrease[1];
	
	printf("Strlen: %lu\n", strlen(input));
	printf("Number of escaped characters: %d\n", escaped);
	printf("Number of characters of code: %d\n", codelen);
	printf("Number of characters in memory: %d\n", memorylen);
	printf("Part 1 result: %d\n", result1);;
	printf("Part 2 result: %d\n", result2);;
	
	return 0;
}

void countEscapes(char* input, int dest[2])
{
	int count = 0, encodedIncrease = 0;
	for (int i = 0; i < strlen(input); i++)
	{
		if (input[i] == '\\' && input[i + 1] == '"')
		{
			count += 1;
			encodedIncrease += 2;

			i++;
		}
		
		if (input[i] == '\\' && input[i + 1] == 'x')
		{
			count += 3;
			encodedIncrease += 1;

			i += 3;
		}
		
		if (input[i] == '\\' && input[i + 1] == '\\')
		{
			count += 1;
			encodedIncrease += 2;
			i++;
		}
		
	}
	dest[0] = count;
	dest[1] = encodedIncrease;
}