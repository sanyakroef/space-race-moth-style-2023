/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * renderer.h:
 * Exposes the functionality to raymarch thru a environment and calculate the resulting color.
 */

#ifndef _RENDERER_H
#define _RENDERER_H

#include "config.h"
#include "vec3.h"
#include "image.h"

#include <stdbool.h>


struct Camera;


/* A backwards light ray.
 */
typedef struct {
    Vec3 loc;
    Vec3 dir;
    float distance;
    unsigned steps;
    float last_step;

    float stop_distance;
} Ray;


/* Creates a ray with reasonable defaults.
 *
 * Returns:
 * the ray
 */
Ray ray_default();


typedef struct {
    Vec3 origin;
    float size;
} Sphere;


/* A visual environment in a format that is easy to render.
 */
typedef struct {
    float test;
    Vec3 goals[TOTAL_GOALS];
    Vec3 player;

    Vec3 light_loc;

    Sphere spheres[MAX_SPHERES];
    RGB spheres_colors[MAX_SPHERES];
} Scene;


enum CastRayResultType {
    NO_COLLISION,
    COLLIDED_ENV1,
    COLLIDED_GOAL,
    COLLIDED_SPHERE,
};


/* The information about a casted ray.
 */
typedef struct {
    enum CastRayResultType typ;
    Ray ray;
    size_t id;
    float min_distance_to_goal;
} CastRayResult;


/* Calculate the minimum distance to a object in the scene.
 *
 * loc: the point to sample the minimum distance from
 * scene: a pointer to the scene
 * include_player: if the player should be included as a object
 *
 * Returns:
 * the minimum distance to a object in the scene
 */
float scene_distance(Vec3 loc, const Scene* scene, bool include_player);


/* Cast a ray inside of the scene.
 *
 * ray: the ray to cast
 * scene: a pointer to the scene
 * include_player: if the player should be included as a collidable object
 *
 * Returns:
 * The information about the ray within the context of the scene
 */
CastRayResult cast_ray(Ray ray, const Scene* scene, bool include_player);


/* Calculate the pixel values of a image inside of a scene seen from a camera.
 *
 * img: the image the result should be rendered to
 * cam: the in game camera to project from
 * scene: the scene to render
 */
void render(Image* img, const struct Camera* cam, const Scene* scene);

#endif
