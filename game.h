/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * game.h:
 * Exposes the primary interface to the game's functionality.
 */

#ifndef _GAME_H
#define _GAME_H

#include <stdbool.h>
#include <sys/types.h>


/* The state of the game.
 */
struct Game;
typedef struct Game Game;


enum GameResult {
    Quit,
    Won,
    Lost,
};


typedef struct {
    unsigned fps;
    bool disable_bugs;
    unsigned space_ship;
} GameSettings;


/* Generate and allocated the game data based on the settings.
 *
 * settings: the game settings
 *
 * Returns:
 * The newly allocated game data
 *
 * Edge cases:
 * - If anything went wrong NULL gets returned
 */
Game* new_game(GameSettings settings);


/* progress the game by a frame.
 *
 * game: a pointer to the game
 *
 * Returns:
 * Whether of not to quit the game
 */
bool do_frame(Game* game);


/* Attempts to read used input and apply it to the game.
 *
 * game: a pointer to the game
 *
 * Returns:
 * If a input was successfully read
 */
bool try_read_input(Game* game);


/* Free the memory of the game data.
 *
 * game: a pointer to the game
 */
void dealloc_game(Game* game);


/* get the outcome of the game.
 *
 * game: a pointer to the game
 *
 * Returns:
 * The outcome of the game
 */
enum GameResult game_result(const Game* game);


/* Counts how many goals are still remaining in the current game.
 *
 * game: a pointer to the game
 *
 * Returns:
 * The number of remaining goals
 */
size_t game_goals_remaining(const Game* game);


/* Get the name of the current spaceship.
 *
 * game: a pointer to the game
 *
 * Returns:
 * The name of the current spaceship
 */
const char* game_space_ship_name(const Game* game);


/* See if the game state has recorded any error.
 *
 * game: a pointer to the game
 *
 * Returns:
 * If a error has been recorded
 */
bool game_has_error(const Game* game);

#endif
