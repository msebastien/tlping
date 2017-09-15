/**
* args.c
* Implementation of arguments parsing into useful data for tlping
*
* Authors: Levast Émile, Maes Sébastien
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "ping.h"
#include "functions.h"

// Default behaviour
argSt prgmArguments = {
	.ipAddress = NULL,
	.payloadSize = 100,
	.timeout = 5, // in seconds
	.count = 5,
	.interval = 1000 // in milliseconds
};

void processArguments(int argc, char* argv[]) {

	int errorArgument = 0;

	// We start the loop with argv[1] because argv[0] is the program's path of execution.
	// argc is the number of arguments.
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') { // argv[i][0] is the first character of an argument. Each argument is a string.
			switch (argv[i][1]) {

			case 's':
				prgmArguments.payloadSize = atoi(&argv[i][3]); // Size of the data carried by the packet (excluding the header)
				break;

			case 't':
				prgmArguments.timeout = atoi(&argv[i][3]); // If no response is received after this specified time, the program automatically stops.
				break;

			case 'c':
				prgmArguments.count = atoi(&argv[i][3]); // Number of repeats
				break;

			case 'i':
				prgmArguments.interval = atoi(&argv[i][3]); // Time between pings
				break;

			case 'h':
				displayHelp();
				exit(EXIT_SUCCESS);
				break;

			default:
				printf("%s is an unknown argument. Please try again.\n", argv[i]);
				errorArgument = 1;
			}

		}
		else {
			prgmArguments.ipAddress = argv[i];
		}
	}

	// ERRORS

	// If no IP address is specified
	if (prgmArguments.ipAddress == NULL) {
		printf("No IP address is specified.\n");
		displayHelp();
		exit(EXIT_FAILURE);
	}

	// If an argument is unknown
	if (errorArgument) {
		displayHelp();
		exit(EXIT_FAILURE);
	}


}