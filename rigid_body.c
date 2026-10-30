/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * rigid_body.c:
 * Implements the functionality regarding rigid bodies.
 */

#include "rigid_body.h"
#include "matrix.h"


void rigid_body_step(RigidBody* rb, float dt) {
    float f_mul = rb->mass_inv * dt;
    float hdt = dt * 0.5;
    rb->loc = vec3_add(rb->loc, vec3_mul_scalar(rb->loc_v, hdt));
    rb->rot = vec3_add(rb->rot, vec3_mul_scalar(rb->rot_v, hdt));
    rb->loc_v = vec3_add(rb->loc_v, vec3_mul_scalar(rb->loc_f, f_mul));
    rb->rot_v = vec3_add(rb->rot_v, vec3_mul_scalar(rb->rot_f, f_mul));
    rb->loc = vec3_add(rb->loc, vec3_mul_scalar(rb->loc_v, hdt));
    rb->rot = vec3_add(rb->rot, vec3_mul_scalar(rb->rot_v, hdt));

    Vec3 v0 = {0, 0, 0};
    rb->loc_f = v0;
    rb->rot_f = v0;
}


// based on https://www.toptal.com/game/video-game-physics-part-i-an-introduction-to-rigid-body-dynamics
void rigid_body_aplay_force_relative(RigidBody* rb, Vec3 loc, Vec3 force) {
    Vec3 force_rot;

    rb->rot_f = vec3_add(rb->rot_f, vec3_cross(loc, force));

    Vec3 v0 = {0, 0, 0};
    Matrix3x4 mat = matrix3x4_inverse(matrix3x4_translate_and_rotate(v0, rb->rot));
    rb->loc_f = vec3_add(rb->loc_f, matrix3x4_map_rotation(&mat, force));
}
