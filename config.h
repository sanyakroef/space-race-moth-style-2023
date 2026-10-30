/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * config.h:
 * Contains information that is sporadically used within the code base.
 * In addition to flags to enable/disable features.
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#define _GNU_SOURCE
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif


#define PLAYER_CRAFT_SIZE 0.2
#define GOAL_COLLECT_DISTANCE2 8.
#define STOP_STEPS 0x100
#define COLLITION_DISTANCE 0.01f


#define MAX_SPHERES 9
#define TOTAL_GOALS 5


#define RENDER_THREADS 16
//#define GAME_SHOW_CURSOR
#define STD_TIME_H_HOTFIX

#endif
