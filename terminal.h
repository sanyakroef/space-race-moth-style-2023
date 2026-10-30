/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * terminal.h:
 * Exposes extra functionality to interact with the terminal.
 */

#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "image.h"


/* Initialise all terminal related functionality.
 */
void terminal_start();


/* Terminate all terminal related functionality.
 */
void terminal_stop();


/* Display a image to the screen (using ANSI).
 */
void show_image(Image* img);


/* Get the size a image would need to be to perfectly fit on the screen.
 */
Size2 get_window_size();


/* A non-blocking version of `getch` for ncurses.
 *
 * Returns:
 * the result of getch or ERR if there was no input ready.
 */
int getch_opt();

#endif
