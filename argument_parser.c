/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * argument_parser.c:
 * Implementation of argument_parser.h
 */

#include "argument_parser.h"

#include <string.h>
#include <stdlib.h>


GameSettings parse_settings(int argc, char* argv[]) {
    GameSettings settings = {
        60,
        false,
        0,
    };
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            i++;
            if (i == argc) {
                settings.fps = 0;
                return settings;
            }
            settings.fps = atoi(argv[i]);
            if (settings.fps == 0) {
                settings.fps = 0;
                return settings;
            }
        } else if (strcmp(argv[i], "-no_bug") == 0) {
            settings.disable_bugs = true;
        } else if (strcmp(argv[i], "-s") == 0) {
            i++;
            if (i == argc) {
                settings.fps = 0;
                return settings;
            }
            settings.space_ship = atoi(argv[i]);
        } else {
            settings.fps = 0;
            return settings;
        }
    }
    return settings;
}
