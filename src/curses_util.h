#ifndef CURSES_UTIL_H_
#define CURSES_UTIL_H_

#include <ncurses.h>
#include <unistd.h>

#include "defs.h"
#include "structs.h"

Input curses_input(void *ctx);
WINDOW *curses_init(int width, int height);
void curses_terminate(WINDOW *wnd);
void curses_draw_tiles(WINDOW *wnd, TileType **tiles, size_t width,
                       size_t height);
void curses_draw_game_over(WINDOW *wnd, size_t width, size_t height, int score);

#endif // UICURSES_H_