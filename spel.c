/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * spel.c:
 * This program is a space racing game with gradually increasing physics bugs.
 * Implemented using ncurses and ANSI.
 * Which display raymarched images to the terminal and is controlled by the mouse.
 *
 * Implements the real-time game loop and orchestrate what happens before and after the game happens.
 */

#include "image.h"
#include "terminal.h"
#include "time.h"
#include "game.h"
#include "argument_parser.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


/* Run the game at a consistent frame rate.
 * Also display the result of the game.
 *
 * settings: the settings for the game to run
 *
 * Returns:
 * If a error occurred
 */
bool game_loop(GameSettings settings) {
    uint64_t target_fps = settings.fps;
    Game* game = new_game(settings);
    if (game == NULL) {
        printf("Failed to initialise the game.\n");
        return true;
    }
    terminal_start();

    uint64_t start = time_now();

    uint64_t last = time_now();
    uint64_t frame_time_target = NANOSECONDS_IN_A_SECONDS / target_fps;
    while (true) {
        while (try_read_input(game)) {}
        if (do_frame(game)) {
            break;
        }

        uint64_t now = time_now();
        int64_t dur = (int64_t)now - (int64_t)last;
        int64_t to_wait = ((int64_t)frame_time_target - dur);
        if (to_wait > 0) {
            last += frame_time_target;
            sleep((uint64_t)to_wait);
        } else {
            last = now;
        }
    }

    uint64_t end = time_now();
    terminal_stop();

    float time = (float)(end - start) / (float)(60. * NANOSECONDS_IN_A_SECONDS);
    const char* name = game_space_ship_name(game);
    switch (game_result(game)) {
        case Won:
            printf(
                "Congratulations you completed the Space Race, Moth Style!!!\nYour time is %f minutes while piloting %s.\n",
                time,
                name
            );
            break;
        case Lost:;
            size_t remaining = game_goals_remaining(game);
            printf(
                "Yea... you collided with that.\nYour run took %f minutes, and there we %u goals remaining while piloting %s.\n",
                time,
                (unsigned)remaining,
                name
            );
            break;
    }

    bool error = game_has_error(game);
    dealloc_game(game);
    return error;
}


/* Run the game based on the command line arguments.
 *
 * argc: argument count
 * argv: argument values
 *
 * Returns:
 * If a error occurred 1, otherwise 0.
 */
int main(int argc, char* argv[]) {
    GameSettings settings = parse_settings(argc, argv);
    if (settings.fps == 0) {
        printf("Invalid arguments\n");
        return 1;
    } else {
        return (int)game_loop(settings);
    }
}
