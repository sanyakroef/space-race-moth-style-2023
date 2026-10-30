/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * rigid_body.h:
 * Exposes the functionality regarding rigid bodies.
 */

#ifndef _RIGID_BODY_H
#define _RIGID_BODY_H

#include "vec3.h"


typedef struct {
    Vec3 loc;
    Vec3 rot;

    Vec3 loc_v;
    Vec3 rot_v;

    Vec3 loc_f;
    Vec3 rot_f;

    float mass_inv;
} RigidBody;


/* Update the state of the rigid body according to a time step.
 *
 * rb: the rigid body to update
 * dt: the amount of time that has elapsed
 */
void rigid_body_step(RigidBody* rb, float dt);


/* Apply a force from a point relative to the rigid body itself.
 *
 * rb: the rigid body to apply the force to
 * loc: the location of the source of the force
 * force: the directional force that is applied
 */
void rigid_body_aplay_force_relative(RigidBody* rb, Vec3 loc, Vec3 force);

#endif
