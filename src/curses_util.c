#include "curses_util.h"

#include "defs.h"

WINDOW *curses_init(int width, int height) {
    // Init curses
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    WINDOW *wnd = newwin(height + 2 * BORDER_THICKNESS,
                         width + 2 * BORDER_THICKNESS, 0, 0);
    box(wnd, BORDER_SIDE, BORDER_TOP);
    keypad(wnd, true);
    nodelay(wnd, true);
    curs_set(0);

    if (!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
    }

    start_color();

    // attron(A_BOLD);
    // box(wnd, 0, 0);
    // attroff(A_BOLD);

    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    wbkgd(wnd, COLOR_PAIR(1));

    return wnd;
}

void curses_terminate(WINDOW *wnd) {
    endwin();
}

Input curses_input(void *ctx) {
    Input input_map[] = {['q'] = INPUT_EXIT,
                         [KEY_UP] = INPUT_UP,
                         [KEY_DOWN] = INPUT_DOWN,
                         [KEY_LEFT] = INPUT_LEFT,
                         [KEY_RIGHT] = INPUT_RIGHT};
    int ch = wgetch(ctx);
    return ch < 0 || ch > nelem(input_map) ? INPUT_NONE : input_map[ch];
}