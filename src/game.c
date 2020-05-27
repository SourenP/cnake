#include <ncurses.h>
#include <unistd.h>

#include "game.h"

#include "common.h"
#include "defs.h"
#include "grid.h"

WINDOW *wnd;
Grid grid;

int game__init() {
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    wnd = newwin(GAME_HEIGHT + 2 * BORDER_THICKNESS, GAME_WIDTH + 2 * BORDER_THICKNESS, 0, 0);
    box(wnd, '|', '-');
    keypad(wnd, true);
    nodelay(wnd, true);
    curs_set(0);

    if (!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

    start_color();

    // attron(A_BOLD);
    // box(wnd, 0, 0);
    // attroff(A_BOLD);

    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    wbkgd(wnd, COLOR_PAIR(1));

    return 0;
}

void game__run() {
    int input = INPUT_NONE;
    grid = grid__create(GAME_WIDTH, GAME_HEIGHT, '*');

    while (1) {
        input = game__getInput();

        game__draw();

        usleep(GAME_SLEEP);
        refresh();

        if (input == INPUT_EXIT) {
            break;
        }
    }
}

void game__close() {
    grid__destroy(grid);
    endwin();
}

enum Input game__getInput() {
    int in_char = wgetch(wnd);
    switch (in_char) {
        case 'q':
            return INPUT_EXIT;
        case KEY_UP:
            return INPUT_UP;
        case KEY_DOWN:
            return INPUT_DOWN;
        case KEY_LEFT:
            return INPUT_LEFT;
        case KEY_RIGHT:
            return INPUT_RIGHT;
        default:
            return INPUT_NONE;
    }
}

void game__draw() {
    grid__draw(grid, wnd);
}
