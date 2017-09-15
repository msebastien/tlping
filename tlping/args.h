/**
* args.c
* Implementation of arguments parsing into useful data for tlping
*
* Authors: Levast �mile, Maes S�bastien
*/

#ifndef ARGS_H
#define ARGS_H

typedef struct arguments {

	const char* ipAddress;
	int payloadSize;
	int timeout;
	int count;
	int interval;

} argSt;

void processArguments(int argc, char* argv[]);


#endif
