/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * std_time_h_hotfix.h:
 *
 * This hot fix was build out of:
 * + https://android.googlesource.com/platform/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.7-4.6/+/refs/heads/tools_r20/sysroot/usr/include/bits/types.h
 * + https://android.googlesource.com/platform/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.7-4.6/+/refs/heads/tools_r20/sysroot/usr/include/time.h
 * + and `grep -r CLOCK_MONOTONIC_RAW /usr/include`
 * and thus no of this code belongs to me.
 *
 * For the reason this hot fix even exists view the Dev notes in the MANUAL.md.
 */
#ifndef _STD_TIME_H_HOTFIX_H
#define _STD_TIME_H_HOTFIX_H

typedef __clockid_t clockid_t;


struct timespec {
    __time_t tv_sec;
    long int tv_nsec;
};


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __THROW;


extern int nanosleep (__const struct timespec *__requested_time, struct timespec *__remaining);


#define CLOCK_MONOTONIC_RAW 4

#endif
