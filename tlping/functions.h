/**
* functions.c
* Various useful functions
*
* Authors: Levast Émile, Maes Sébastien
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <WS2tcpip.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS 

void displayHelp();
void createRandomPayload(char* payload);

#endif
