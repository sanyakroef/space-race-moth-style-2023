/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * time.c:
 * Implements the needed functionality regarding time.
 * With time being measured in nanoseconds.
 * Using the POSIX functions.
 */

#include "config.h"
#include "time.h"

#ifndef STD_TIME_H_HOTFIX
#include <time.h>
#else
#include "std_time_h_hotfix.h"
#endif
#include <errno.h>


uint64_t time_now() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    return (uint64_t)now.tv_sec * NANOSECONDS_IN_A_SECONDS + (uint64_t)now.tv_nsec;
}


void sleep(uint64_t dur) {
    struct timespec ts;
    ts.tv_sec = dur / NANOSECONDS_IN_A_SECONDS;
    ts.tv_nsec = dur % NANOSECONDS_IN_A_SECONDS;

    int err;
    do {
        err = nanosleep(&ts, &ts);
    } while (err && (errno == EINTR));
}
