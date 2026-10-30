/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * time.h:
 * Exposes the needed functionality regarding time.
 * With time being measured in nanoseconds.
 */

#ifndef _TIME_H
#define _TIME_H

#include <stdint.h>


#define NANOSECONDS_IN_A_SECONDS 1000000000


/* Get the current time in nanoseconds using a monotonic clock.
 *
 * Returns:
 * The time in nanoseconds
 */
uint64_t time_now();


/* Sleep for approximately a specified amount of nanoseconds.
 */
void sleep(uint64_t dur);

#endif
