/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * vec3.c:
 * Implements the functionality of 3-dimensional vectors.
 */

#include "config.h"
#include "vec3.h"

#include <math.h>


float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


float vec3_length2(Vec3 vec) {
    return vec3_dot(vec, vec);
}


float vec3_length(Vec3 vec) {
    return sqrtf(vec3_dot(vec, vec));
}


Vec3 vec3_cross(Vec3 a, Vec3 b) {
    Vec3 out = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
    };
    return out;
}


Vec3 vec3_add(Vec3 a, Vec3 b) {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}


Vec3 vec3_add_scalar(Vec3 a, float b) {
    a.x += b;
    a.y += b;
    a.z += b;
    return a;
}


Vec3 vec3_sub(Vec3 a, Vec3 b) {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}


Vec3 vec3_mul_scalar(Vec3 a, float b) {
    a.x *= b;
    a.y *= b;
    a.z *= b;
    return a;
}


Vec3 vec3_normalize(Vec3 vec) {
    return vec3_mul_scalar(vec, 1. / vec3_length(vec));
}


Vec3 vec3_normalize_and_length(float* length, Vec3 vec) {
    float l = vec3_length(vec);
    *length = l;
    return vec3_mul_scalar(vec, 1. / l);
}
