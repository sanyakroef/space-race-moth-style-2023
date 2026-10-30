/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * image.h:
 * Defines how a image is represented in memory.
 */

#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>
#include <sys/types.h>


typedef struct {
    size_t x;
    size_t y;
} Size2;


typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;


typedef struct {
    RGB* data;
    Size2 size;
} Image;

#endif
