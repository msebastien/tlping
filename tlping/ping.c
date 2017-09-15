/**
* ping.c
* Implementation of a unique ping
*
* Authors: Levast Émile, Maes Sébastien
*/

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "args.h"
#include "functions.h"
#include "timer.h"

extern argSt prgmArguments;

void launchPing(double *delay, int *count, double *min, double *max, int *lostBytes, int *failedExchange) {
	
	// STRUCTURES	
	struct sockaddr_in target = {
		.sin_family = AF_INET,
		.sin_port = ntohs(7),
		.sin_addr.S_un.S_addr = inet_addr(prgmArguments.ipAddress)

	}; // stores the IP address and port
	WSADATA wsad; // Required structure to enable sockets
	
	// VARIABLES
	int IdSocket; // Contains the ID of the socket
	int sentBytes, receivedBytes; // number of the sent bytes and the received Bytes
	int targetSize = sizeof(target);
	double startTime, endTime, latency;
	char* payload = NULL; // Data to send
	char* buffer = NULL; // Buffer stores received data

	// Memory allocation (1 char = 1 byte)
	payload = malloc(prgmArguments.payloadSize * sizeof(char));
	buffer = malloc(prgmArguments.payloadSize * sizeof(char));

	// ---------------------------------------------------------------------------------------

	// If the IP address is not parsable
	if (target.sin_addr.S_un.S_addr == INADDR_NONE || target.sin_addr.S_un.S_addr == INADDR_ANY) {
		printf("The IP address is not parsable.\n");
		displayHelp();
		exit(EXIT_FAILURE);
	}

	// Enabling Windows Sockets	
	WSAStartup(2, &wsad);

	// Creating and opening a UDP socket
	IdSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// TIMEOUT
	struct timeval timeOut = {
		.tv_sec = prgmArguments.timeout,
		.tv_usec = 0
	};
	setsockopt(IdSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeOut, sizeof timeOut);

	// Create a random string
	createRandomPayload(payload);

	// Sending the payload to the target
	sentBytes = sendto(IdSocket, payload, (sizeof(char)*prgmArguments.payloadSize), 0, (struct sockaddr*)&target, targetSize);
	startTime = getCurrentTime();

	if (sentBytes == -1) {
		printf("[FAILURE] Impossible to reach target (count=%d)\n", *count +1);
		*failedExchange += 1;

	}
	else // If sending the payload succeeds, we wait to receive data back.
	{
		receivedBytes = recvfrom(IdSocket, buffer, (sizeof(char)*prgmArguments.payloadSize), 0, (struct sockaddr*)&target, &targetSize);

		if (receivedBytes == -1)
		{
			*failedExchange += 1;
			printf("[FAILURE] Data reception has failed (count=%d)\n", *count +1);

		}
	}

	endTime = getCurrentTime();

	// Closing Socket
	if (closesocket(IdSocket) < 0) {
		perror("sendto()");
		exit(errno);
	}

	// ---------------------------------------------------------------------------
	// LATENCY COMPUTATION
	latency = endTime - startTime;
	*delay += latency;

	if (*count == 0) // First ping
	{
		*min = latency;
		*max = latency;
	}
	else if (latency < (*min))
	{
		*min = latency;

	}
	else if (latency > (*max))
	{
		*max = latency;
	}

	// Number of bytes during pings
	(*lostBytes) = (*lostBytes) + (sentBytes - receivedBytes);

	
	if (receivedBytes != -1) {
		printf("Response from %s: count=%d time=%f ms\n", prgmArguments.ipAddress, *count + 1, latency);
		printf("Received Bytes=%d / Sent Bytes=%d\n", receivedBytes, sentBytes);
	}

	

	// Free memory to avoid memory leaks
	free(payload);
	free(buffer);

}