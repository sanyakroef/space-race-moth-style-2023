/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * camera.h:
 * Exposes the functionality regarding the in game camera.
 */

#ifndef _CAMERA_H
#define _CAMERA_H

#include "image.h"
#include "renderer.h"
#include "matrix.h"


struct Camera {
    float h_scale;
    float v_scale;
    float v_offset;
    Matrix3x4 transform;
};
typedef struct Camera Camera;


/* initialise a camera for the given scene and screen.
 *
 * cam: a pointer to the camera to initialise
 * size: the size of the screen in pixels
 * img_ratio: the height of the pixels relative to their width
 * camera_transform: a transformation matrix representing the attribute of the camera in the scene
 */
void init_camera(Camera* cam, Size2 size, float img_ratio, Matrix3x4 camera_transform);


/* Generate the Ray that belongs to the given pixel on the camera.
 *
 * cam: the camera
 * x: the horizontal coordinate of the pixel
 * y: the vertical coordinate of the pixel
 */
Ray pixel_to_ray(const Camera* cam, size_t x, size_t y);

#endif
