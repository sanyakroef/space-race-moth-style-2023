/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * camera.c:
 * Implements the functionality regarding the in game camera.
 */

#include "camera.h"
#include "vec3.h"

#include <stddef.h>
#include <math.h>
#include <stdbool.h>


void init_camera(Camera* cam, Size2 size, float img_ratio, Matrix3x4 camera_transform) {
    float h_scale = 2.f / (float)size.x;
    float v_scale = h_scale * img_ratio;
    float v_offset = size.y * v_scale * -0.5;

    cam->h_scale = h_scale;
    cam->v_scale = v_scale;
    cam->v_offset = v_offset;
    cam->transform = camera_transform;
}


Ray pixel_to_ray(const Camera* cam, size_t x, size_t y) {
    float xf = (float)x * cam->h_scale - 1.f;
    float yf = (float)y * cam->v_scale + cam->v_offset;

    Vec3 dir = {
        xf,
        yf,
        1.,
    };
    Ray ray = ray_default();
    ray.dir = vec3_normalize(matrix3x4_map_rotation(&cam->transform, dir));
    ray.loc = matrix3x4_translation(&cam->transform);
    ray.stop_distance = 100.;

    return ray;
}
