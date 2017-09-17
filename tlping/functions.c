/**
* functions.c
* Various useful functions
*
* Authors: Levast Émile, Maes Sébastien
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "args.h"

extern argSt prgmArguments;

/*
* Procedure :	displayHelp
*				Display arguments and how to use the program
*/
void displayHelp() {
	printf("====== How to use this program (tlping) ======\n");
	printf("tlping [-h display the help (what you currently read)]\n[-c=<count> number of ping to execute]\n");
	printf("[-s=<size> size of the payload (aka data carried by a packet)]\n");
	printf("[-i=<time in second> interval between each ping request]\n");
	printf("[-t=<time in millisecond> timeout (if no response is received after\nthis time elapsed, tlping stops)] [IP Address]\n");
}

/*
* Procedure :	createRandomPayload
*				Generate a random string
* Parameters :	(char*) payload : an empty string
*/
void createRandomPayload(char* payload) {
	srand(time(NULL));

	char charset[] = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int j = 0; j < prgmArguments.payloadSize; j++) {
		size_t i = (double)rand() / RAND_MAX * (sizeof charset - 1);
		payload[j] = charset[i];
	}
	payload[prgmArguments.payloadSize - 1] = '\0';
}