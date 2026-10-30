/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * matrix.c:
 * Implements the functionality regarding 3 by 4 matrices.
 */

#include "config.h"
#include "matrix.h"
#include "glitches.h"

#include <math.h>


Vec3 matrix3x4_map(const Matrix3x4* mat, Vec3 vec) {
    Vec3 out = {
        vec.x * mat->part[0].x + vec.y * mat->part[1].x + vec.z * mat->part[2].x + mat->part[3].x,
        vec.x * mat->part[0].y + vec.y * mat->part[1].y + vec.z * mat->part[2].y + mat->part[3].y,
        vec.x * mat->part[0].z + vec.y * mat->part[1].z + vec.z * mat->part[2].z + mat->part[3].z,
    };
    return out;
}


Vec3 matrix3x4_map_rotation(const Matrix3x4* mat, Vec3 vec) {
    Vec3 out = {
        vec.x * mat->part[0].x + vec.y * mat->part[1].x + vec.z * mat->part[2].x,
        vec.x * mat->part[0].y + vec.y * mat->part[1].y + vec.z * mat->part[2].y,
        vec.x * mat->part[0].z + vec.y * mat->part[1].z + vec.z * mat->part[2].z,
    };
    return out;
}


Vec3 matrix3x4_translation(const Matrix3x4* mat) {
    return mat->part[3];
}


// Source for the formula: https://www.wolframalpha.com/input?i=%5B%5Ba%2Cb%2Cc%2C0%5D%2C%5Bd%2Ce%2Cf%2C0%5D%2C%5Bg%2Ch%2Ci%2C0%5D%2C%5Bx%2Cy%2Cz%2C1%5D%5D+matrix+inverse
Matrix3x4 matrix3x4_inverse(Matrix3x4 mat) {
    Matrix3x4 out = {{
        {
            (mat.part[2].y * mat.part[1].z - mat.part[1].y * mat.part[2].z) / (
                mat.part[2].x * mat.part[1].y * mat.part[0].z
                - mat.part[1].x * mat.part[2].y * mat.part[0].z
                - mat.part[2].x * mat.part[0].y * mat.part[1].z
                + mat.part[0].x * mat.part[2].y * mat.part[1].z
                + mat.part[1].x * mat.part[0].y * mat.part[2].z
                - mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
            (mat.part[2].x * mat.part[1].z - mat.part[1].x * mat.part[2].z) / (
                -(mat.part[2].x * mat.part[1].y * mat.part[0].z)
                + mat.part[1].x * mat.part[2].y * mat.part[0].z
                + mat.part[2].x * mat.part[0].y * mat.part[1].z
                - mat.part[0].x * mat.part[2].y * mat.part[1].z
                - mat.part[1].x * mat.part[0].y * mat.part[2].z
                + mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
            (mat.part[2].x * mat.part[1].y - mat.part[1].x * mat.part[2].y) / (
                mat.part[2].x * mat.part[1].y * mat.part[0].z
                - mat.part[1].x * mat.part[2].y * mat.part[0].z
                - mat.part[2].x * mat.part[0].y * mat.part[1].z
                + mat.part[0].x * mat.part[2].y * mat.part[1].z
                + mat.part[1].x * mat.part[0].y * mat.part[2].z
                - mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
        },
        {
            (mat.part[2].y * mat.part[0].z - mat.part[0].y * mat.part[2].z) / (
                -(mat.part[2].x * mat.part[1].y * mat.part[0].z)
                + mat.part[1].x * mat.part[2].y * mat.part[0].z
                + mat.part[2].x * mat.part[0].y * mat.part[1].z
                - mat.part[0].x * mat.part[2].y * mat.part[1].z
                - mat.part[1].x * mat.part[0].y * mat.part[2].z
                + mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
            (mat.part[2].x * mat.part[0].z - mat.part[0].x * mat.part[2].z) / (
                mat.part[2].x * mat.part[1].y * mat.part[0].z
                - mat.part[1].x * mat.part[2].y * mat.part[0].z
                - mat.part[2].x * mat.part[0].y * mat.part[1].z
                + mat.part[0].x * mat.part[2].y * mat.part[1].z
                + mat.part[1].x * mat.part[0].y * mat.part[2].z
                - mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
            (mat.part[2].x * mat.part[0].y - mat.part[0].x * mat.part[2].y) / (
                -(mat.part[2].x * mat.part[1].y * mat.part[0].z)
                + mat.part[1].x * mat.part[2].y * mat.part[0].z
                + mat.part[2].x * mat.part[0].y * mat.part[1].z
                - mat.part[0].x * mat.part[2].y * mat.part[1].z
                - mat.part[1].x * mat.part[0].y * mat.part[2].z
                + mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
        },
        {
            (mat.part[1].y * mat.part[0].z - mat.part[0].y * mat.part[1].z) / (
                mat.part[2].x * mat.part[1].y * mat.part[0].z
                - mat.part[1].x * mat.part[2].y * mat.part[0].z
                - mat.part[2].x * mat.part[0].y * mat.part[1].z
                + mat.part[0].x * mat.part[2].y * mat.part[1].z
                + mat.part[1].x * mat.part[0].y * mat.part[2].z
                - mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
            (mat.part[1].x * mat.part[0].z - mat.part[0].x * mat.part[1].z) / (
                -(mat.part[2].x * mat.part[1].y * mat.part[0].z)
                + mat.part[1].x * mat.part[2].y * mat.part[0].z
                + mat.part[2].x * mat.part[0].y * mat.part[1].z
                - mat.part[0].x * mat.part[2].y * mat.part[1].z
                - mat.part[1].x * mat.part[0].y * mat.part[2].z
                + mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
            (mat.part[1].x * mat.part[0].y - mat.part[0].x * mat.part[1].y) / (
                mat.part[2].x * mat.part[1].y * mat.part[0].z
                - mat.part[1].x * mat.part[2].y * mat.part[0].z
                - mat.part[2].x * mat.part[0].y * mat.part[1].z
                + mat.part[0].x * mat.part[2].y * mat.part[1].z
                + mat.part[1].x * mat.part[0].y * mat.part[2].z
                - mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
        },
        {
            (
                mat.part[2].y * mat.part[1].z * mat.part[3].x
                - mat.part[1].y * mat.part[2].z * mat.part[3].x
                - mat.part[2].y * mat.part[0].z * mat.part[3].y
                + mat.part[0].y * mat.part[2].z * mat.part[3].y
                + mat.part[1].y * mat.part[0].z * mat.part[3].z
                - mat.part[0].y * mat.part[1].z * mat.part[3].z
            ) / (
                -(mat.part[2].x * mat.part[1].y * mat.part[0].z)
                + mat.part[1].x * mat.part[2].y * mat.part[0].z
                + mat.part[2].x * mat.part[0].y * mat.part[1].z
                - mat.part[0].x * mat.part[2].y * mat.part[1].z
                - mat.part[1].x * mat.part[0].y * mat.part[2].z
                + mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
            (
                mat.part[2].x * mat.part[1].z * mat.part[3].x
                - mat.part[1].x * mat.part[2].z * mat.part[3].x
                - mat.part[2].x * mat.part[0].z * mat.part[3].y
                + mat.part[0].x * mat.part[2].z * mat.part[3].y
                + mat.part[1].x * mat.part[0].z * mat.part[3].z
                - mat.part[0].x * mat.part[1].z * mat.part[3].z
            ) / (
                mat.part[2].x * mat.part[1].y * mat.part[0].z
                - mat.part[1].x * mat.part[2].y * mat.part[0].z
                - mat.part[2].x * mat.part[0].y * mat.part[1].z
                + mat.part[0].x * mat.part[2].y * mat.part[1].z
                + mat.part[1].x * mat.part[0].y * mat.part[2].z
                - mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
            (
                mat.part[2].x * mat.part[1].y * mat.part[3].x
                - mat.part[1].x * mat.part[2].y * mat.part[3].x
                - mat.part[2].x * mat.part[0].y * mat.part[3].y
                + mat.part[0].x * mat.part[2].y * mat.part[3].y
                + mat.part[1].x * mat.part[0].y * mat.part[3].z
                - mat.part[0].x * mat.part[1].y * mat.part[3].z
            ) / (
                -(mat.part[2].x * mat.part[1].y * mat.part[0].z)
                + mat.part[1].x * mat.part[2].y * mat.part[0].z
                + mat.part[2].x * mat.part[0].y * mat.part[1].z
                - mat.part[0].x * mat.part[2].y * mat.part[1].z
                - mat.part[1].x * mat.part[0].y * mat.part[2].z
                + mat.part[0].x * mat.part[1].y * mat.part[2].z
            ),
        },
    }};
    return out;
}


Matrix3x4 matrix3x4_mul(Matrix3x4 a, Matrix3x4 b) {
    Matrix3x4 out = {{
        {
            a.part[0].x * b.part[0].x + a.part[0].y * b.part[1].x + a.part[0].z * b.part[2].x,
            a.part[0].x * b.part[0].y + a.part[0].y * b.part[1].y + a.part[0].z * b.part[2].y,
            a.part[0].x * b.part[0].z + a.part[0].y * b.part[1].z + a.part[0].z * b.part[2].z,
        },
        {
            a.part[1].x * b.part[0].x + a.part[1].y * b.part[1].x + a.part[1].z * b.part[2].x,
            a.part[1].x * b.part[0].y + a.part[1].y * b.part[1].y + a.part[1].z * b.part[2].y,
            a.part[1].x * b.part[0].z + a.part[1].y * b.part[1].z + a.part[1].z * b.part[2].z,
        },
        {
            a.part[2].x * b.part[0].x + a.part[2].y * b.part[1].x + a.part[2].z * b.part[2].x,
            a.part[2].x * b.part[0].y + a.part[2].y * b.part[1].y + a.part[2].z * b.part[2].y,
            a.part[2].x * b.part[0].z + a.part[2].y * b.part[1].z + a.part[2].z * b.part[2].z,
        },
        {
            a.part[3].x * b.part[0].x + a.part[3].y * b.part[1].x + a.part[3].z * b.part[2].x
                + b.part[3].x,
            a.part[3].x * b.part[0].y + a.part[3].y * b.part[1].y + a.part[3].z * b.part[2].y
                + b.part[3].y,
            a.part[3].x * b.part[0].z + a.part[3].y * b.part[1].z + a.part[3].z * b.part[2].z
                + b.part[3].z,
        },
    }};
    return out;
}


Matrix3x4 matrix3x4_translate(Vec3 offset) {
    Matrix3x4 out = {{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        offset,
    }};
    return out;
}


Matrix3x4 matrix3x4_rotate_x(float roll) {
    float sin;
    float cos;
    sincosf(roll, &sin, &cos);
    Matrix3x4 out = {{
        {1, 0, 0},
        {0, cos, sin},
        {0, -sin, cos},
        {0, 0, 0},
    }};
    return out;
}


Matrix3x4 matrix3x4_rotate_y(float roll) {
    float sin;
    float cos;
    sincosf(roll, &sin, &cos);
    Matrix3x4 out = {{
        {cos, 0, sin},
        {0, 1, 0},
        {-sin, 0, cos},
        {0, 0, 0},
    }};
    return out;
}


Matrix3x4 matrix3x4_rotate_z(float roll) {
    float sin;
    float cos;
    sincosf(roll, &sin, &cos);
    Matrix3x4 out = {{
        {cos, sin, 0},
        {-sin, cos, 0},
        {0, 0, 1},
        {0, 0, 0},
    }};
    return out;
}


// Source for the formula: https://en.wikipedia.org/wiki/Rotation_matrix#Conversion_from_rotation_matrix_to_axis%E2%80%93angle
Matrix3x4 matrix3x4_rotate(Vec3 axis, float angle) {
    float sin;
    float cos;
    sincosf(angle, &sin, &cos);
    float icos = 1. - cos;
    Matrix3x4 out = {{
        {
            cos + axis.x * axis.x * icos,
            axis.x * axis.y * icos - axis.z * sin,
            axis.x * axis.z * icos + axis.y * sin,
        },
        {
            axis.y * axis.x * icos + axis.z * sin,
            cos + axis.y * axis.y * icos,
            axis.y * axis.z * icos - axis.x * sin,
        },
        {
            axis.z * axis.x * icos - axis.y * sin,
            axis.z * axis.y * icos + axis.x * sin,
            cos + axis.z * axis.z * icos,
        },
        {0, 0, 0},
    }};
    if (CURRENT_GLITCHES.matrix_rotate_bug) {
        out.part[2].x += axis.y * sin * 2.;
    }
    return out;
}


Matrix3x4 matrix3x4_translate_and_rotate(Vec3 loc, Vec3 rot) {
    if (CURRENT_GLITCHES.sequential_axis_rotations) {
        Matrix3x4 mat = matrix3x4_rotate_x(rot.x);
        mat = matrix3x4_mul(mat, matrix3x4_rotate_y(rot.y));
        mat = matrix3x4_mul(mat, matrix3x4_rotate_z(rot.z));
        mat.part[3] = loc;
        return mat;
    }

    float length;
    rot = vec3_normalize_and_length(&length, rot);

    if (CURRENT_GLITCHES.abs_rotation_scale) {
        length = fabsf(rot.x) + fabsf(rot.y) + fabsf(rot.z);
    }
    if (CURRENT_GLITCHES.inverted_rotation) {
        length = -length;
    }

    Matrix3x4 mat = matrix3x4_rotate(rot, -length);
    mat.part[3] = loc;
    return mat;
}
