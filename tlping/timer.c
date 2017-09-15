/**
 * timer.c
 * Implementation of time measurement under Windows.
 * 
 * Author: Pierre Tirilly
 */

#include <Windows.h>
#include <Winbase.h>
#include "timer.h"

/**
 * Function: get_current_time ()
 * Returns: the current time in milliseconds, starting from the Windows Epoch.
 */
double getCurrentTime() {
	LARGE_INTEGER current_time;
	LARGE_INTEGER frequency;

	// get current count
	QueryPerformanceCounter ( &current_time );

	// get count frequency in counts per second
	QueryPerformanceFrequency ( &frequency );

	// return count converted to ms
	return (double)current_time.QuadPart / frequency.QuadPart * 1000.0;
}
