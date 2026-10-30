/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * glitches.h:
 * Defines the glitches that can be enabled
 *   and a global to read and write to what is currently enabled.
 */

#ifndef _GLITCHES_H
#define _GLITCHES_H

#include <stdbool.h>


/* A collection of enabled glitches.
 */
struct Glitches {
    bool matrix_rotate_bug :1;
    bool sequential_axis_rotations :1;
    bool abs_rotation_scale :1;
    bool inverted_rotation :1;
};


/* The currently activated glitches.
 */
extern struct Glitches CURRENT_GLITCHES;

#endif
