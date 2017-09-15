/**
 * timer.h
 * Interface for time measurement under Windows.
 * 
 * Author: Pierre Tirilly
 */

#ifndef TIMER_H_
#define TIMER_H_

/**
 * Function: get_current_time()
 * Returns: the current time in milliseconds, starting from the Windows Epoch.
 */
double getCurrentTime();

#endif
