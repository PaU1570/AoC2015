/*
 * main.c
 *
 *  Created on: Aug 18, 2017
 *      Author: paulu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main () {

	char *input = "1113122113";
	char *sequence;
	sequence = (char *) calloc(1, 6000000);
	int seqLength = 10;
	strcpy(sequence, input);



	for (int j = 0; j <= 50; j++) {

		char *newSequence;	// This is where the new sequence is going to be stored.
		newSequence = (char *) calloc(1, 6000000);
		int newSeqLength = 0;	// Reset newSequence and the length.
		int tracker = 0; // This keeps track of where the new digits have to be added on the new sequence.


		char value = sequence[0];
		int repetitions = 1;	// "value" stores the number that is being repeated, "repetitions" keeps track of how many of "value" are in a row.

		for (int i = 1; i < seqLength; i++) {

			printf("Sequence N.%02d - Iteration %d / %d...", j, i, seqLength);

			if (sequence[i] == value) {	// If the number at the next position is the same as "value", add 1 to "repetitions".
							repetitions++;
						}

			else {	// If not, add "value" and "repetitions" to the new sequence and reset "value" and "repetitions".

				newSequence[tracker] = repetitions + 48;	//	48 is added to 'repetitions' to convert it from integer to char.
				newSequence[tracker + 1] = value;

				value = sequence[i];

				repetitions = 1;
				newSeqLength += 2;	//	Length increases by 2 every time this happens.
				tracker += 2;

			}
			printf(" Done!\n");
		}

		/* At the end, the current values of "value" and "repetition" have to be added.	*/
		sprintf(newSequence, "%s%d%c", newSequence, repetitions, value);
		newSeqLength += 2;
		printf("Sequence: %s; New Sequence: %s\n", sequence, newSequence);

		/*	Instead of using strcpy(), make sequence point to newSequence and newSequence point to sequence (I think it should be faster).	*/
		char *_tmp;
		_tmp = sequence;
		sequence = newSequence;
		newSequence = _tmp;
		printf("Swapped!\n");

		printf("Sequence: %s; New(old) Sequence: %s\n", sequence, newSequence);
		printf("Sequence N. %02d length: %d\n\n", j + 1, newSeqLength);

		seqLength = newSeqLength;
		free(newSequence);

	}

	free(input);
	free(sequence);
	return 0;
}
