/*
 * day11.c
 *
 *  Created on: Aug 26, 2017
 *      Author: paulu
 */

#include <stdio.h>
#include <string.h>

int is_password_valid(char[9]);	// Returns 0 if false, 1 if true.
int is_there_sequence(char[9]); // 	  "    "  "   "    "  "   "
void next_password(char[9]);

int main (const int argc, const char* argv[]) {

	switch (argc) {
		case 1 :
			printf("Too few arguments! One argument expected.\n");
			return 1;

		case 2 :
			if (strlen(argv[1]) != 8){
				printf("Input string must be 8 characters long.\n");
				return 1;
			}
			printf("Input string: %s\n", argv[1]);
			break;

		default :
			printf("Too many arguments! One argument expected.\n");
			return 1;
	}
	char password[9];
	for (int i = 0; i < 8; ++i) {
		password[i] = argv[1][i];
	}

	printf("Finding next valid password...");
	do {
		next_password(password);
		printf("\n%s", password);
	} while (is_password_valid(password) == 0);

	printf(" <-------- Found!\n");

	return 0;
}

int is_password_valid(char password[9]) {

	for (int i = 0; i < 8; i++) {	// Check if password contains illegal characters (i, o and l).
		if (password[i] == 'i' || password[i] == 'o' || password[i] == 'l') {
			return 0;
		}
	}

	int pairs = 0;
	char lastPair = ' ';	// This saves the letter of the last pair to check if the next pair is different.
	for (int i = 0; i < 8; i++) {	// Check if password contains enough pairs.
		if (password[i] == password [i + 1] && password[i] != lastPair) {	// The two pairs have to be different.
			lastPair = password[i];
			pairs++;
			i++;	// We can skip to i+2 after we find a pair.
		}
	}
	if (pairs < 2)
		return 0;

	if (is_there_sequence(password) == 1)	// Check if the next two letters are continuations of the next (taking into account that there are no 'i', 'o' or 'l's).
		return 1;

	return 0;
}

int is_there_sequence(char password[9]) {

	for (int i = 0; i < 8; i++) {
		if (password[i] == password[i + 1] - 1 && password[i] == password[i + 2] - 2) // Check for 'normal' sequences.
			return 1;
	}

	for (int i = 0; i < 8; i++) {
		if (password[i] == 'h' || password[i] == 'k' || password[i] == 'n') { // If the first letter of a possible sequence is the one before a forbidden letter...
			if (password[i] == password[i + 1] - 2 && password[i] == password[i + 2] - 3) // Check for sequence skipping the second letter.
				return 1;
		}
		if (password[i] == 'g' || password[i] == 'j' || password[i] == 'm') { // If the first letter of a possible sequence is the one two positions before a forbidden letter...
			if (password[i] == password[i + 1] - 1 && password[i] == password[i + 2] - 3) // Check for sequence skipping the third letter.
				return 1;
		}
	}

	return 0;
}

void next_password(char password[9]) {

	for (int i = 7; i >= 0; i--) {

		if (password[i] != 'z') {
			if (password[i] != 'h' && password[i] != 'k' && password[i] != 'm') {
				password[i]++;
			}
			else {
				password[i] += 2;
			}
			break;
		}
		else {
			password[i] = 'a';
		}
	}
}
