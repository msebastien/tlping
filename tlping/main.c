/**
* main.c
* tlping is a ping program using UDP protocol and the ECHO service (port 7)
*
* Authors: Levast Émile, Maes Sébastien
*/

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

#include "args.h"
#include "ping.h"

#pragma comment(lib, "Ws2_32.lib")

extern argSt prgmArguments;

/**
* Function:  main
*            Perform a data exchange with the Echo service and compute latency (average, min and max) (PING)
*
* Returns:   0
*/
int main(int argc, char* argv[]) {
	double delay = 0; // Latency between each data exchange, it stores the sum of all the latencies of each ping
	double averageLatency = 0, minLatency = 0, maxLatency = 0; 
	int count = 0, lostBytes = 0; // Count : The number of data exchange/ping
	int failedExchange = 0; // The number of failed data exchanges

	processArguments(argc, argv); // Parse arguments into useful values reusable in the whole program
	
	printf("PING %s - %d bytes of data:\n\n", prgmArguments.ipAddress, prgmArguments.payloadSize);

	do {
		launchPing(&delay, &count, &minLatency, &maxLatency, &lostBytes, &failedExchange); // Function which sends and receive data, it also computes various stats 
		count++; 
		Sleep(prgmArguments.interval); // Wait before the next loop
	} while (count < prgmArguments.count); // Necessary condition in order to execute as many as pings requested by the user

	// STATISTICS DISPLAYED AFTER PINGS
	averageLatency = delay / prgmArguments.count;

	printf("\n=== STATISTICS ===\n");
	printf("Average latency=%fms Min Latency=%fms Max Latency= %fms\n", averageLatency, minLatency, maxLatency);
	printf("lostBytes:%d\n", lostBytes);
	printf("Failed exchanges:%d\n", failedExchange);
	printf("Successful exchanges:%d\n", count - failedExchange );

	return EXIT_SUCCESS;
}