#include "curses_util.h"

#include "defs.h"

#include <ncurses.h>
#include <unistd.h>

Input curses_input(void *ctx) {
    Input input_map[] = {['q'] = INPUT_EXIT,
                         [KEY_UP] = INPUT_UP,
                         [KEY_DOWN] = INPUT_DOWN,
                         [KEY_LEFT] = INPUT_LEFT,
                         [KEY_RIGHT] = INPUT_RIGHT};
    int ch = wgetch(ctx);
    return ch < 0 || ch > nelem(input_map) ? INPUT_NONE : input_map[ch];
}