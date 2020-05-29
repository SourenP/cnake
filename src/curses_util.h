#ifndef CURSES_UTIL_H_
#define CURSES_UTIL_H_

#include "structs.h"

#include <ncurses.h>
#include <unistd.h>

Input curses_input(void *ctx);
WINDOW *curses_init(int width, int height);
void curses_terminate(WINDOW *wnd);

#endif // UICURSES_H_