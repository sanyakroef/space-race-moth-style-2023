/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * argument_parser.h:
 * Parse command line arguments into game settings.
 */

#ifndef _ARGUMENT_PARSER_H
#define _ARGUMENT_PARSER_H

#include "game.h"


//returns fps == 0 if invalid
/* Build the game settings from the arguments.
 *
 * argc: argument count
 * argv: argument values
 *
 * Returns:
 * the settings
 *
 * Edge case:
 * - if the arguments are invalid then a settings is returned with 0 as fps.
 */
GameSettings parse_settings(int argc, char* argv[]);

#endif
