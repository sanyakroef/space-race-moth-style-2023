/* Name: Sanya Kroef
 * UvAnetID: 14726173
 * Study: BSc Informatica
 *
 * terminal.c:
 * Implements extra functionality to interact with the terminal.
 * Utilising ANSI directly in part because of the shortcoming of ncurses
 *   and in part because of the original intention to use sixel to display the images.
 */

#include "terminal.h"

#include <stdio.h>
#include <ncurses.h>
#include <assert.h>


void terminal_start() {
    setvbuf(stdout, NULL, _IOFBF, 0x1000);

    initscr();
    cbreak();
    noecho();

    keypad(stdscr, TRUE);
    mousemask(REPORT_MOUSE_POSITION, NULL);

    curs_set(0);
}


void terminal_stop() {
    endwin();
}


/* Do some house cleaning tasks of ncurses and move the cursor to the top left position.
 */
void new_frame() {
    refresh();
    printf("\033[1;1H");
}


void show_image(Image* img) {
    if (img == NULL || img->data == NULL) {
        return;
    }

    new_frame();

    // ensure the image height is a multiple of two
    size_t height = img->size.y & ~1;
    size_t width = img->size.x;

    RGB* data = img->data;
    for (size_t v = 0; v < height; v += 2) {
        if (v != 0) {
            printf("\033[0m\r\n");
        }
        for (size_t h = 0; h < width; h++) {
            RGB* data2 = data + width;
            printf("\033[48;2;%hhu;%hhu;%hhum\033[38;2;%hhu;%hhu;%hhum\xe2\x96\x84",
                    data->r, data->g, data->b, data2->r, data2->g, data2->b);
            data++;
        }
        data += width;
    }
    printf("\033[0m");
    fflush(stdout);
}


Size2 get_window_size() {
    Size2 out = {
        COLS,
        LINES * 2,
    };
    return out;
}


int getch_opt() {
    nodelay(stdscr, TRUE);
    int key = getch();
    nodelay(stdscr, FALSE);
    return key;
}
