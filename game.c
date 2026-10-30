/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * game.c:
 * Implements the primary functionality of the game.
 */

#include "config.h"
#include "game.h"
#include "terminal.h"
#include "renderer.h"
#include "camera.h"
#include "rigid_body.h"
#include "glitches.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <math.h>


/* The data indicating what bugs should be activated when collecting a goal.
 * And how far the player has to get away to deactivate the bugs.
 */
struct GoalDificulty {
    struct Glitches glitches;
    float bug_size;
};


static const struct GoalDificulty GOAL_GLITCHES[TOTAL_GOALS] = {
    {{1, 0, 0, 0}, 6.},
    {{0, 1, 0, 0}, 6.},
    {{0, 0, 1, 0}, 12.},
    {{0, 0, 0, 1}, 20.},
    {{1, 0, 1, 0}, 5.},
};


/* A point source of gravity.
 */
struct GravitySources {
    Vec3 loc;
    float strenght;
};


#define GRAVITY_SOURCES_COUNT 2

static const struct GravitySources GRAVITY_SOURCES[GRAVITY_SOURCES_COUNT] = {
    {{0, 0, 0}, 0.7},
    {{1589., 479., 466.}, 2.0},
};


#define MAX_UI_ELEMENTS 8

/* A ui element that control how much thrust a thruster on the spaceship gives of.
 */
typedef struct {
    float x_start;
    float y_start;
    float x_end;
    float y_end;

    float min_thrust;
    float max_thrust;

    Vec3 thruster_location;
    Vec3 thruster_vector;

    Vec3 current_thrust;
    float current_pos;
} UIElement;
typedef UIElement UIElements[MAX_UI_ELEMENTS];


/* The data unique of a specific spacecraft
 */
struct SpaceCraft {
    UIElements ui;
    char* name;
};


#define AVAILABLE_SPACECRAFT_COUNT 6

static const struct SpaceCraft AVAILABLE_SPACECRAFT[AVAILABLE_SPACECRAFT_COUNT] = {
    {
        {
            {
                0.65, 0.1,
                0.9,  0.9,
                -0.1, 0.1,
                {1., 0., 0.},
                {0., 0., 1.},

                {0., 0., 0.},
                0.5,
            },
            {
                0.65, 0.1,
                0.9,  0.9,
                -0.1, 0.1,
                {-1., 0., 0. },
                {0.,  0., -1.},

                {0., 0., 0.},
                0.5,
            },
            {
                0.1,  0.1,
                0.35, 0.9,
                -0.1, 0.1,
                {0., 1., 0.},
                {0., 0., 1.},

                {0., 0., 0.},
                0.5,
            },
            {
                0.1,  0.1,
                0.35, 0.9,
                -0.1, 0.1,
                {0., -1.,  0.},
                {0.,  0., -1.},

                {0., 0., 0.},
                0.5,
            },
            {
                0.45, 0.1,
                0.55, 0.9,
                -0.1, 0.1,
                {0., 0., -1.},
                {0., 0.,  1.},

                {0., 0., 0.},
                0.5,
            },
        },
        "a paper clip based space ship",
    },
    {
        {
            {
                0.65, 0.1,
                0.9,  0.9,
                -0.1, 0.1,
                {1., 0., 0.},
                {0., 0., 1.},

                {0., 0., 0.},
                0.5,
            },
            {
                0.1,  0.1,
                0.35, 0.9,
                -0.1, 0.1,
                {0., 1., 0.},
                {0., 0., 1.},

                {0., 0., 0.},
                0.5,
            },
            {
                0.45, 0.1,
                0.55, 0.9,
                -0.1, 0.1,
                {0., 0., -1.},
                {0., 0.,  1.},

                {0., 0., 0.},
                0.5,
            },
        },
        "a paper clip based space probe",
    },
    {
        {
            {
                0.1, 0.1,
                0.2, 0.9,
                0.0, 0.1,
                {1., 0., 0.},
                {0., 0., 1.},

                {0., 0., 0.},
                0.,
            },
            {
                0.3, 0.1,
                0.4, 0.9,
                0.0, 0.1,
                {-1., 0., 0.},
                {0.,  0., 1.},

                {0., 0., 0.},
                0.,
            },
            {
                0.6, 0.1,
                0.7, 0.9,
                0.0, 0.1,
                {0., 1., 0.},
                {0., 0., 1.},

                {0., 0., 0.},
                0.,
            },
            {
                0.8, 0.1,
                0.9, 0.9,
                0.0, 0.1,
                {0., -1., 0.},
                {0.,  0., 1.},

                {0., 0., 0.},
                0.,
            },
        },
        "the Hungat",
    },
    {
        {
            {
                0.1, 0.1,
                0.2, 0.9,
                0.0, 0.1,
                {1., 0., 0.},
                {0., 0., 1.},

                {0., 0., 0.},
                0.,
            },
            {
                0.3, 0.1,
                0.4, 0.9,
                0.0, 0.1,
                {-1., 0., 0.},
                {0.,  0., 0.},

                {0., 0., 0.},
                0.,
            },
            {
                0.6, 0.1,
                0.7, 0.9,
                0.0, 0.1,
                {0., 1., 0.},
                {0., 0., 1.},

                {0., 0., 0.},
                0.,
            },
            {
                0.8, 0.1,
                0.9, 0.9,
                0.0, 0.1,
                {0., -1., 0. },
                {0.,  0., 0.2},

                {0., 0., 0.},
                0.,
            },
        },
        "the damaged Hungat",
    },
    {
        {
            {
                0.1, 0.1,
                0.2, 0.9,
                0.0, 0.1,
                {1., 0., 0. },
                {0., 0., 0.1},

                {0., 0., 0.},
                0.,
            },
            {
                0.3, 0.1,
                0.4, 0.9,
                0.0, 0.1,
                {-1., 0., 0. },
                { 0., 0., 0.1},

                {0., 0., 0.},
                0.,
            },
            {
                0.6, 0.1,
                0.7, 0.9,
                0.0, 0.1,
                {0., 1., 0. },
                {0., 0., 0.1},

                {0., 0., 0.},
                0.,
            },
            {
                0.8, 0.1,
                0.9, 0.9,
                0.0, 0.1,
                {0., -1., 0. },
                {0.,  0., 0.1},

                {0., 0., 0.},
                0.,
            },
            {
                0.45,  0.1,
                0.55,  0.9,
                0.0 , 40.0,
                {0., 0., -1.},
                {0., 0.,  1.},

                {0., 0., 0.},
                0.0,
            },
        },
        "a warp drive test vehicle",
    },
    {
        {
            {
                0.4, 0.1,
                0.6, 0.5,
                0.0, 0.1,
                {0., -1., 0.},
                {0.,  1., 1.},

                {0., 0., 0.},
                0.,
            },
            {
                0.65, 0.5,
                0.85, 0.9,
                0.0 , 0.1,
                { 1.,  1., 0.},
                {-1., -1., 1.},

                {0., 0., 0.},
                0.,
            },
            {
                0.15, 0.5,
                0.35, 0.9,
                0.0 , 0.1,
                {-1.,  1., 0.},
                { 1., -1., 1.},

                {0., 0., 0.},
                0.,
            },
        },
        "a escape pod"
    },
};


struct Game {
    float t;
    float dt;
    bool error;
    bool stop;
    enum GameResult result;
    Image frame;

    int cursor_x;
    int cursor_y;
    UIElements ui;

    RigidBody player_rb;
    bool goals_collected[TOTAL_GOALS];

    size_t bug_origin;
    float bug_sphere_size;
    bool disable_bugs;

    char* space_ship_name;
};


Game* new_game(GameSettings settings) {
    if (settings.space_ship >= AVAILABLE_SPACECRAFT_COUNT) {
        return NULL;
    }
    Vec3 v0 = {0, 0, 0};
    Game game;
    game.t = 0.;
    game.dt = 1. / (float)settings.fps;
    game.error = false;
    game.stop = false;
    game.result = Quit;
    game.frame.data = NULL;
    game.frame.size.x = 0;
    game.frame.size.y = 0;
    game.cursor_x = 0;
    game.cursor_y = 0;
    RigidBody player_rb = {
        {0, 0, 15},
        {1E-6, 1E-6, 1E-6},
        v0, v0,
        v0, v0,
        1.
    };
    game.player_rb = player_rb;
    game.bug_origin = 0;
    game.bug_sphere_size = 0.;
    game.disable_bugs = settings.disable_bugs;
    game.space_ship_name = AVAILABLE_SPACECRAFT[settings.space_ship].name;

    memset(&game.ui, 0, sizeof(game.ui));
    memset(&game.goals_collected, 0, sizeof(game.goals_collected));

    memcpy(&game.ui, &AVAILABLE_SPACECRAFT[settings.space_ship].ui, sizeof(UIElements));
    game.space_ship_name = AVAILABLE_SPACECRAFT[settings.space_ship].name;

    CURRENT_GLITCHES.matrix_rotate_bug = false;

    Game* out = malloc(sizeof(Game));
    if (out == NULL) {
        return NULL;
    }
    *out = game;
    return out;
}


/* Make sure the image to hold the frame to display is sized identically to the window can display.
 * If not, then reallocate the image data to fit and update the image size.
 *
 * frame: the image
 *
 * Edge cases:
 * - if memory allocation fails the data attribute is set to NULL
 */
void ensure_frame_is_correctly_sized(Image* frame) {
    Size2 target = get_window_size();
    if (frame->size.x != target.x || frame->size.y != target.y) {
        free(frame->data);
        frame->data = malloc(sizeof(RGB) * target.x * target.y);
        frame->size = target;
    }
}


/* initialise a scene to reflect the game state.
 *
 * scene: a pointer to the scene
 * game: a pointer to the game
 */
void generate_scene(Scene* scene, const Game* game) {
    scene->player = game->player_rb.loc;
    Vec3 light_loc = {0.1, 0.1, 0.1};
    scene->light_loc = light_loc;
    memset(&scene->spheres, 0, sizeof(Sphere) * MAX_SPHERES);

    {
        float sin, cos;
        sincosf(game->t * 0.01, &sin, &cos);
        float x = sin * 20.;
        float z = cos * 20.;
        scene->spheres[0].origin.x = x;
        scene->spheres[0].origin.y = 0.;
        scene->spheres[0].origin.z = z;
        scene->spheres[0].size = 1.0;

        scene->goals[0] = scene->spheres[0].origin;

        scene->spheres_colors[0].r = 10;
        scene->spheres_colors[0].g = 10;
        scene->spheres_colors[0].b = 200;
        {
            sincosf(game->t, &sin, &cos);
            scene->spheres[1].origin.x = x + sin * 2.;
            scene->spheres[1].origin.y = cos * 2.;
            scene->spheres[1].origin.z = z + sin;
            scene->spheres[1].size = 0.2;

            scene->spheres_colors[1].r = 100;
            scene->spheres_colors[1].g = 10;
            scene->spheres_colors[1].b = 10;
        }
    }
    {
        float sin, cos;
        sincosf(game->t * 0.01 - 0.15, &sin, &cos);
        float x = sin * 20.;
        float z = cos * 20.;
        scene->spheres[2].origin.x = x;
        scene->spheres[2].origin.y = 0.;
        scene->spheres[2].origin.z = z;
        scene->spheres[2].size = 1.0;

        scene->goals[1] = scene->spheres[2].origin;

        scene->spheres_colors[2].r = 10;
        scene->spheres_colors[2].g = 210;
        scene->spheres_colors[2].b = 50;
    }
    {
        float sin, cos;
        sincosf(game->t * 0.1, &sin, &cos);
        float x = sin * 5.;
        float z = cos * 5.;
        scene->spheres[3].origin.x = x;
        scene->spheres[3].origin.y = 0.;
        scene->spheres[3].origin.z = z;
        scene->spheres[3].size = 1.0;

        scene->goals[2] = scene->spheres[3].origin;

        scene->spheres_colors[3].r = 200;
        scene->spheres_colors[3].g = 200;
        scene->spheres_colors[3].b = 100;
    }
    {
        float sin, cos;
        sincosf(game->t * 0.0001, &sin, &cos);
        float x = sin * 100.;
        float z = cos * 100.;
        scene->spheres[4].origin.x = x;
        scene->spheres[4].origin.y = sin * 0.1;
        scene->spheres[4].origin.z = z;
        scene->spheres[4].size = 6.0;

        scene->spheres_colors[4].r = 200;
        scene->spheres_colors[4].g = 100;
        scene->spheres_colors[4].b = 10;
        {
            sincosf(game->t * 0.3, &sin, &cos);
            scene->spheres[5].origin.x = x + sin * 0.7;
            scene->spheres[5].origin.y = cos * 7.;
            scene->spheres[5].origin.z = z + sin * 7.;
            scene->spheres[5].size = 1.0;

            scene->goals[3] = scene->spheres[5].origin;

            scene->spheres_colors[5].r = 255;
            scene->spheres_colors[5].g = 10;
            scene->spheres_colors[5].b = 10;
        }
        {
            sincosf(game->t * 0.12, &sin, &cos);
            scene->spheres[6].origin.x = x + sin * 8.2;
            scene->spheres[6].origin.y = cos * 0.3;
            scene->spheres[6].origin.z = z + cos * 8.6;
            scene->spheres[6].size = 1.2;

            scene->spheres_colors[6].r = 100;
            scene->spheres_colors[6].g = 100;
            scene->spheres_colors[6].b = 150;
        }
    }
    {
        scene->spheres[7].origin.x = 1589.;
        scene->spheres[7].origin.y = 479.;
        scene->spheres[7].origin.z = 466.;
        scene->spheres[7].size = 0.1;

        scene->spheres_colors[7].r = 0;
        scene->spheres_colors[7].g = 0;
        scene->spheres_colors[7].b = 0;
    }
    {
        float sin, cos;
        sincosf(game->t * 0.04, &sin, &cos);
        float x = sin * 7.;
        float z = cos * 7.;
        scene->spheres[8].origin.x = x;
        scene->spheres[8].origin.y = -37.;
        scene->spheres[8].origin.z = z;
        scene->spheres[8].size = 1.0;

        scene->goals[4] = scene->spheres[8].origin;

        scene->spheres_colors[8].r = 120;
        scene->spheres_colors[8].g = 120;
        scene->spheres_colors[8].b = 100;
    }
}


/* render the ui elements to a image.
 *
 * frame: the image
 * uis: the ui elements
 */
void render_ui(Image frame, UIElement uis[MAX_UI_ELEMENTS]) {
    RGB* data = frame.data;
    for (size_t y = 0; y < frame.size.y; y++) {
        float yf = (float)y / (float)frame.size.y;
        for (size_t x = 0; x < frame.size.x; x++) {
            float xf = (float)x / (float)frame.size.x;
            RGB color = {0, 0, 0};

            for (size_t i = 0; i < MAX_UI_ELEMENTS; i++) {
                UIElement* ui = &uis[i];
                if (ui->x_start <= xf && ui->x_end >= xf) {
                    float y = (yf - ui->y_start) / (ui->y_end - ui->y_start);
                    if (y >= 0. && y <= 1.) {
                        y = 1. - y;
                        if (fabsf(y - ui->current_pos) <= 0.1) {
                            color.g = 255;
                        } else {
                            color.r = 100;
                            color.g = 100;
                            color.b = 100;
                        }
                        break;
                    }
                }
            }

            *data = color;
            data++;
        }
    }
}


/* render the game to its frame image, display it to the screen,
 *   and check if the player has collided with the scene.
 *
 * game: a pointer to the game
 * scene: a pointer to the scene
 */
void render_game_and_check_for_collition(Game* game, const Scene* scene) {
    Camera cam;
    Vec3 translate = {0, 0, -5.};

    size_t ui_hight = game->frame.size.y / 5;
    size_t ui_y = game->frame.size.y - ui_hight;
    Image render_frame = game->frame;
    render_frame.size.y = ui_y;

    Vec3 cam_offset = {0, 0, PLAYER_CRAFT_SIZE};
    init_camera(&cam, game->frame.size, 1.f, matrix3x4_mul(
        matrix3x4_translate_and_rotate(game->player_rb.loc, game->player_rb.rot),
        matrix3x4_translate(cam_offset)
    ));
    render(&render_frame, &cam, scene);

    Image ui_frame = game->frame;
    ui_frame.size.y = ui_hight;
    ui_frame.data += ui_y * game->frame.size.x;
    render_ui(ui_frame, game->ui);

#ifdef GAME_SHOW_CURSOR
    {
        size_t x = game->cursor_x;
        size_t y = game->cursor_y * 2;
        if (x < game->frame.size.x && y < game->frame.size.y) {
            RGB* pixel = &game->frame.data[x + y * game->frame.size.x];
            pixel->r = 255 - pixel->r;
            pixel->g = 255 - pixel->g;
            pixel->b = 255 - pixel->b;
        }
    }
#endif

    show_image(&game->frame);
    fflush(stdout);
}


/* Check if the player has collided with the environment.
 *
 * game: a pointer to the game
 * scene: a pointer to the scene
 */
void check_for_collition(Game* game, const Scene* scene) {
    if (scene_distance(game->player_rb.loc, scene, false) <= PLAYER_CRAFT_SIZE) {
        game->stop = true;
        game->result = Lost;
    }
}


/* Remove the bugs if the player has escaped the region.
 *
 * game: a pointer to the game
 * scene: a pointer to the scene
 */
void update_bug_setings(Game* game, const Scene* scene) {
    Vec3 bug_origin = scene->goals[game->bug_origin];
    float distance_to_bug2 = vec3_length2(vec3_sub(bug_origin, game->player_rb.loc));
    if (distance_to_bug2 > game->bug_sphere_size * game->bug_sphere_size) {
        memset(&CURRENT_GLITCHES, 0, sizeof(struct Glitches));
    }
}


/* Update the ui elements to react to the cursor.
 *
 * game: a pointer to the game
 */
void update_ui(Game* game) {
    size_t ui_hight = game->frame.size.y / 5;
    size_t ui_y = game->frame.size.y - (ssize_t)ui_hight;
    float cursor_y = (float)((ssize_t)game->cursor_y * 2 - (ssize_t)ui_y) / (float)ui_hight;
    float cursor_x = (float)game->cursor_x / (float)game->frame.size.x;

    if (cursor_y >= 0.) {
        for (size_t i = 0; i < MAX_UI_ELEMENTS; i++) {
            UIElement* ui = &game->ui[i];

            if (ui->x_start <= cursor_x && ui->x_end >= cursor_x) {
                float y = (cursor_y - ui->y_start) / (ui->y_end - ui->y_start);
                if (y < 0.) {
                    y = 0.;
                } else if (y > 1.) {
                    y = 1.;
                }
                y = 1. - y;
                ui->current_pos = y;
                ui->current_thrust = vec3_mul_scalar(ui->thruster_vector,
                        y * (ui->max_thrust - ui->min_thrust) + ui->min_thrust);
            }
        }
    }
}


/* Do the needed physics calculations and update the player accordingly.
 *
 * game: a pointer to the game
 */
void update_physics(Game* game) {
    for (size_t i = 0; i < MAX_UI_ELEMENTS; i++) {
        UIElement* ui = &game->ui[i];
        rigid_body_aplay_force_relative(&game->player_rb,
                ui->thruster_location, ui->current_thrust);
    }

    for (size_t i = 0; i < GRAVITY_SOURCES_COUNT; i++) {
        Vec3 dir = vec3_sub(GRAVITY_SOURCES[i].loc, game->player_rb.loc);
        dir = vec3_mul_scalar(dir, GRAVITY_SOURCES[i].strenght / vec3_length2(dir));
        game->player_rb.loc_f = vec3_add(game->player_rb.loc_f, dir);
    }

    rigid_body_step(&game->player_rb, game->dt);
}


/* See if the player has collected a new goal and update the game state accordingly.
 *
 * game: a pointer to the game
 * scene: a pointer to the scene
 */
void update_collect_goals(Game* game, const Scene* scene) {
    for (size_t i = 0; i < TOTAL_GOALS; i++) {
        if (game->goals_collected[i]) {
            continue;
        }
        float distance_to_goal2 = vec3_length2(vec3_sub(scene->goals[i], game->player_rb.loc));
        if (distance_to_goal2 <= GOAL_COLLECT_DISTANCE2) {
            if (!game->disable_bugs) {
                CURRENT_GLITCHES = GOAL_GLITCHES[i].glitches;
                game->bug_sphere_size = GOAL_GLITCHES[i].bug_size;
                game->bug_origin = i;
            }
            game->goals_collected[i] = true;

            bool any_left = false;
            for (size_t i2 = 0; i2 < TOTAL_GOALS; i2++) {
                any_left |= !game->goals_collected[i2];
            }
            if (!any_left) {
                game->stop = true;
                game->result = Won;
            }
        }
    }
}


/* Remove goals that are already collected.
 *
 * scene: a pointer to the scene
 * game: a pointer to the game
 */
void filted_out_collected_goals(Scene* scene, const Game* game) {
    for (size_t i = 0; i < TOTAL_GOALS; i++) {
        if (game->goals_collected[i]) {
            scene->goals[i].x = 0.;
        }
    }
}


bool do_frame(Game* game) {
    if (game->stop) {
        return true;
    }
    ensure_frame_is_correctly_sized(&game->frame);
    if (game->frame.data == NULL) {
        game->error = true;
        return true;
    }

    // GAME LOGIC
    game->t += game->dt;

    Scene scene;
    generate_scene(&scene, game);

    update_bug_setings(game, &scene);
    update_ui(game);
    update_physics(game);
    filted_out_collected_goals(&scene, game);
    update_collect_goals(game, &scene);
    check_for_collition(game, &scene);

    // DISPLAY
    render_game_and_check_for_collition(game, &scene);

    return false;
}


bool try_read_input(Game* game) {
    int key = getch_opt();
    if (key == ERR) {
        return false;
    }

    switch (key) {
        case KEY_MOUSE:;
            MEVENT event;
            if (getmouse(&event) == OK) {
                game->cursor_x = event.x;
                game->cursor_y = event.y;
            }
            break;
        case 'q':
            game->stop = true;
            break;
    }

    return true;
}


void dealloc_game(Game* game) {
    free(game->frame.data);
    free(game);
}


enum GameResult game_result(const Game* game) {
    return game->result;
}


size_t game_goals_remaining(const Game* game) {
    size_t remaining = 0;
    for (size_t i = 0; i < TOTAL_GOALS; i++) {
        remaining += !game->goals_collected[i];
    }
    return remaining;
}


const char* game_space_ship_name(const Game* game) {
    return game->space_ship_name;
}


bool game_has_error(const Game* game) {
    return game->error;
}
