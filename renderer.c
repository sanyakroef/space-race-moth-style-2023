/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * renderer.c:
 * Implements the functionality to reymarch thru a environment and calculate the resulting color.
 */

#include "config.h"
#include "renderer.h"
#include "camera.h"

#include <stdbool.h>
#include <math.h>
#include <stddef.h>


Ray ray_default() {
    Ray out = {
        {0., 0., 0.},
        {0., 0., 0.},
        0.,
        0,
        0.,

        INFINITY,
    };
    return out;
}


void ray_update(Ray* ray, float distance) {
    ray->loc = vec3_add(ray->loc, vec3_mul_scalar(ray->dir, distance));
    ray->distance += distance;
    ray->steps++;
}


bool ray_out_of_reach(const Ray* ray) {
    return ray->steps > STOP_STEPS || ray->distance > ray->stop_distance;
}


float distance_to_sphere(Vec3 loc, Vec3 sphere_loc, float diamiter) {
    if (diamiter <= 0.) {
        return 1E9;
    }
    loc = vec3_sub(loc, sphere_loc);
    return vec3_length(loc) - diamiter;
}


float distance_to_goal(Vec3 loc, const Scene* scene) {
    float d = 1E9;
    for (size_t i = 0; i < TOTAL_GOALS; i++) {
        if (scene->goals[i].x == 0.) {
            continue;
        }
        d = fminf(d, distance_to_sphere(loc, scene->goals[i], 1.));
    }
    return d;
}


float distance_to_spheres(Vec3 loc, const Scene* scene) {
    float d = 1E9;
    for (size_t i = 0; i < MAX_SPHERES; i++) {
        d = fminf(d, distance_to_sphere(loc, scene->spheres[i].origin, scene->spheres[i].size));
    }
    return d;
}


size_t closest_sphere(Vec3 loc, const Scene* scene) {
    float d = 1E9;
    size_t best_i = 0;
    for (size_t i = 0; i < MAX_SPHERES; i++) {
        float d2 = distance_to_sphere(loc, scene->spheres[i].origin, scene->spheres[i].size);
        if (d > d2) {
            d = d2;
            best_i = i;
        }
    }
    return best_i;
}


float distance_to_env1(Vec3 loc) {
    Vec3 v0 = {0., 0., 0.};
    Vec3 loc2 = {loc.x * 0.2, loc.y, loc.z * 0.2};
    float d1 = distance_to_sphere(loc2, v0, 3.);
    float y = fabsf(loc.y);
    loc.y = fmodf(y, 1.) - 0.5;
    loc.x = fabsf(loc.x);
    loc.z = fabsf(loc.z);
    float d2 = distance_to_sphere(loc, v0, 0.7);
    Vec3 v2 = {0.7, 0., 0.};
    d2 = fminf(d2, distance_to_sphere(loc, v2, 0.3));
    Vec3 v3 = {0., 0., 0.5};
    float d3 = distance_to_sphere(loc, v3, 0.3);
    return fmaxf(-fminf(d1, d3), d2);
}


float scene_distance(Vec3 loc, const Scene* scene, bool include_player) {
    float distance = distance_to_env1(loc);

    distance = fminf(distance, distance_to_goal(loc, scene));

    distance = fminf(distance, distance_to_spheres(loc, scene));

    if (include_player) {
        distance = fminf(distance, distance_to_sphere(loc, scene->player, PLAYER_CRAFT_SIZE));
    }
    return distance;
}


CastRayResult ray_to_result(Ray ray, const Scene* scene) {
    Vec3 loc = ray.loc;

    if (distance_to_env1(loc) < COLLITION_DISTANCE) {
        CastRayResult out = {
            COLLIDED_ENV1,
            ray,
            0,
            0.,
        };
        return out;
    }

    float distance_goal = distance_to_goal(loc, scene);
    if (distance_goal < COLLITION_DISTANCE) {
        CastRayResult out = {
            COLLIDED_GOAL,
            ray,
            0,
            0.,
        };
        return out;
    }

    // Did I collide with the player?
    if (distance_to_sphere(loc, scene->player, PLAYER_CRAFT_SIZE) < COLLITION_DISTANCE) {
        CastRayResult out = {
            COLLIDED_ENV1,
            ray,
            0,
            0.,
        };
        return out;
    }

    // Then I must have collided with a sphere
    CastRayResult out = {
        COLLIDED_SPHERE,
        ray,
        closest_sphere(loc, scene),
        0.,
    };
    return out;
}


CastRayResult cast_ray(Ray ray, const Scene* scene, bool include_player) {
    CastRayResult out = {
        NO_COLLISION,
        ray,
        0,
        0.,
    };
    float min_distance_to_goal = 1E9;

    while (!ray_out_of_reach(&ray)) {
        float distance = scene_distance(ray.loc, scene, include_player);
        min_distance_to_goal = fminf(min_distance_to_goal, distance_to_goal(ray.loc, scene));

        if (distance < COLLITION_DISTANCE) {
            out = ray_to_result(ray, scene);
            break;
        }

        ray.last_step = distance;
        ray_update(&ray, distance);
    }
    out.ray = ray;

    out.min_distance_to_goal = min_distance_to_goal;
    return out;
}


RGB render_ray(Ray ray, const Scene* scene) {
    CastRayResult res = cast_ray(ray, scene, false);

    float r = 0.;
    float g = 0.;
    float b = 0.;

    if (res.typ != NO_COLLISION) {
        float light = 0.2;

        {
            ray = ray_default();
            Vec3 light_rel = vec3_sub(scene->light_loc, res.ray.loc);
            ray.dir = vec3_normalize_and_length(&ray.stop_distance, light_rel);
            float angle_difrance = -vec3_dot(res.ray.dir, ray.dir);
            if (angle_difrance > 0.) {
                ray.loc = vec3_sub(res.ray.loc, vec3_mul_scalar(res.ray.dir, res.ray.last_step));
                CastRayResult resl = cast_ray(ray, scene, true);
                if (resl.ray.distance >= resl.ray.stop_distance) {
                    light += angle_difrance * 0.8;
                }
            }
        }
        light /= (float)res.ray.steps * 0.1 + 1.;

        switch (res.typ) {
            case COLLIDED_ENV1:
                r = 100.;
                g = 100.;
                b = 100.;
                break;

            case COLLIDED_GOAL:
                r = 100.;
                g = 200.;
                b = 100.;
                break;

            case COLLIDED_SPHERE:;
                RGB rgb = scene->spheres_colors[res.id];
                r = (float)rgb.r;
                g = (float)rgb.g;
                b = (float)rgb.b;
                break;
        }

        r *= light;
        g *= light;
        b *= light;
    }

    float goal_glow = 40. / (res.min_distance_to_goal + 0.2);
    g += goal_glow;

    r = fminf(r, 255.);
    g = fminf(g, 255.);
    b = fminf(b, 255.);
    RGB out = {(uint8_t)r, (uint8_t)g, (uint8_t)b};
    return out;
}


#if RENDER_THREADS == 1

void render(Image* img, const Camera* cam, const Scene* scene) {
    RGB* data = img->data;
    for (size_t y = 0; y < img->size.y; y++) {
        for (size_t x = 0; x < img->size.x; x++) {
            Ray ray = pixel_to_ray(cam, x, y);
            *data = render_ray(ray, scene);
            data++;
        }
    }
}

#else

#include <pthread.h>


typedef struct {
    Image* img;
    const Camera* cam;
    const Scene* scene;
    size_t y_start;
    size_t y_end;

    pthread_t thread_id;
} RenderThread;


void* render_thread(void* arg) {
    const RenderThread* info = (const RenderThread*)arg;

    RGB* data = info->img->data + (info->y_start * info->img->size.x);
    for (size_t y = info->y_start; y < info->y_end; y++) {
        for (size_t x = 0; x < info->img->size.x; x++) {
            Ray ray = pixel_to_ray(info->cam, x, y);
            *data = render_ray(ray, info->scene);
            data++;
        }
    }

    return NULL;
}


void render(Image* img, const Camera* cam, const Scene* scene) {
    RenderThread threads[RENDER_THREADS];
    size_t step = img->size.y / RENDER_THREADS;

    for (int i = 0; i < RENDER_THREADS; i++) {
        threads[i].img = img;
        threads[i].cam = cam;
        threads[i].scene = scene;
        threads[i].y_start = i * step;
        threads[i].y_end = i * step + step;
    }
    threads[RENDER_THREADS - 1].y_end = img->size.y;

    for (int i = 0; i < RENDER_THREADS; i++) {
        pthread_create(&threads[i].thread_id, NULL, render_thread, &threads[i]);
    }
    for (int i = 0; i < RENDER_THREADS; i++) {
        pthread_join(threads[i].thread_id, NULL);
    }
}

#endif
