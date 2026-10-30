/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * vec3.h:
 * Exposes the functionality of 3-dimensional vectors.
 */

#ifndef _VEC3_H
#define _VEC3_H

typedef struct {
    float x;
    float y;
    float z;
} Vec3;


/* Calculate the dot product of two vectors.
 *
 * a: a vector
 * b: a vector
 *
 * Returns:
 * The dot product
 */
float vec3_dot(Vec3 a, Vec3 b);


/* Calculated the length of a vector squared.
 *
 * vec: the vector
 *
 * Returns:
 * the square of the length
 */
float vec3_length2(Vec3 vec);


/* Calculated the length of a vector.
 *
 * vec: the vector
 *
 * Returns:
 * the length
 */
float vec3_length(Vec3 vec);


/* Calculate the cross product between two vectors.
 *
 * a: a vector
 * b: a vector
 *
 * Returns:
 * the cross product
 */
Vec3 vec3_cross(Vec3 a, Vec3 b);


/* Add two vectors together.
 *
 * a: a vector
 * b: a vector
 *
 * Returns:
 * the sum
 */
Vec3 vec3_add(Vec3 a, Vec3 b);


/* Add a scalar to a vector.
 *
 * a: the vector
 * b: the scalar
 *
 * Returns:
 * the sum
 */
Vec3 vec3_add_scalar(Vec3 a, float b);


/* Subtract one vector for a other.
 *
 * a: a vector
 * b: the vector to subtract
 *
 * Returns:
 * the two vectors subtracted from each-other
 */
Vec3 vec3_sub(Vec3 a, Vec3 b);


/* Subtract a scalar from a vector.
 *
 * a: the vector
 * b: the scalar
 *
 * Returns:
 * the result of the subtraction
 */
Vec3 vec3_mul_scalar(Vec3 a, float b);


/* Normalise a vector. (aka. make its length 1)
 *
 * vec: the vector
 *
 * Returns:
 * A vector that points in the same direction of the original vector and is 1 long.
 *
 * Edge cases:
 * - inputs with length close to or equal to zero generate undefined results.
 */
Vec3 vec3_normalize(Vec3 vec);


/* Normalise a vector and get it length.
 *
 * vec: the vector
 * length: a point to which the length of `vec` is to be written.
 *
 * Returns:
 * A vector that points in the same direction of the original vector and is 1 long.
 * And write the length of `vec` to `length`.
 *
 * Edge cases:
 * - inputs with length close to or equal to zero generate undefined results.
 */
Vec3 vec3_normalize_and_length(float* length, Vec3 vec);

#endif
