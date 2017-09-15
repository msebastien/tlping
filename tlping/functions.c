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

void displayHelp() {
	printf("====== How to use this program (tlping) ======\n");
	printf("tlping [-h display the help (what you currently read)]\n[-c=<count> number of ping to execute]\n");
	printf("[-s=<size> size of the payload (aka data carried by a packet)]\n");
	printf("[-i=<time in millisecond> interval between each ping request]\n");
	printf("[-t=<time in millisecond> timeout (if no response is received after\nthis time elapsed, tlping stops)]\n");
}

void createRandomPayload(char* payload) {
	srand(time(NULL));

	char charset[] = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int sizePayload = prgmArguments.payloadSize;

	for (int j = 0; j < sizePayload; j++) {
		size_t i = (double)rand() / RAND_MAX * (sizeof charset - 1);
		payload[j] = charset[i];
	}
	payload[prgmArguments.payloadSize - 1] = '\0';
}