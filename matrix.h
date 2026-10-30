/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * matrix.h:
 * Exposes the functionality regarding 3 by 4 matrices.
 */

#ifndef _MATRIX_H
#define _MATRIX_H

#include "vec3.h"


typedef struct {
    Vec3 part[4];
} Matrix3x4;


/* Map a vector according to a matrix.
 *
 * mat: the matrix
 * vec: the vector
 *
 * Returns:
 * The translated vector
 */
Vec3 matrix3x4_map(const Matrix3x4* mat, Vec3 vec);


/* Map a vector according to a matrix excluding any translation.
 *
 * mat: the matrix
 * vec: the vector
 *
 * Returns:
 * The translated vector
 */
Vec3 matrix3x4_map_rotation(const Matrix3x4* mat, Vec3 vec);


/* Get the translation component of a matrix.
 *
 * mat: the matrix
 *
 * Returns:
 * the translation component of `mat`.
 */
Vec3 matrix3x4_translation(const Matrix3x4* mat);


/* Calculate the inverse of a matrix.
 *
 * mat: the matrix
 *
 * Returns:
 * the inverse of `mat`
 */
Matrix3x4 matrix3x4_inverse(Matrix3x4 mat);


/* Multiply two matrices together.
 *
 * mat: the matrix
 *
 * Returns:
 * The matrix that does the same mapping as using the two matrices in sequence.
 */
Matrix3x4 matrix3x4_mul(Matrix3x4 a, Matrix3x4 b);


/* Create a matrix that has a given translation.
 *
 * offset: the translation
 *
 * Returns:
 * the matrix
 */
Matrix3x4 matrix3x4_translate(Vec3 offset);


/* Create a matrix that is rotated a given amount around the x-axis.
 *
 * roll: the rotation given is radians
 *
 * Returns:
 * the matrix
 */
Matrix3x4 matrix3x4_rotate_x(float roll);


/* Create a matrix that is rotated a given amount around the y-axis.
 *
 * roll: the rotation given is radians
 *
 * Returns:
 * the matrix
 */
Matrix3x4 matrix3x4_rotate_y(float roll);


/* Create a matrix that is rotated a given amount around the y-axis.
 *
 * roll: the rotation given is radians
 *
 * Returns:
 * the matrix
 */
Matrix3x4 matrix3x4_rotate_z(float roll);


/* Create a matrix with a given translation and rotations.
 *
 * loc: the translation
 * rot: the rotations
 *
 * Returns:
 * the matrix
 */
Matrix3x4 matrix3x4_translate_and_rotate(Vec3 loc, Vec3 rot);

#endif
