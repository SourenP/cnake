#include <ncurses.h>
#include <unistd.h>

#include "game.h"

#include "common.h"

WINDOW *wnd;

int game__init() {
    wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    keypad(wnd, true);
    nodelay(wnd, true);
    curs_set(0);

    if (!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

    start_color();

    attron(A_BOLD);
    box(wnd, 0, 0);
    attroff(A_BOLD);

    // init_pair(1, COLOR_BLACK, COLOR_WHITE);
    // wbkgd(wnd, COLOR_PAIR(1));

    return 0;
}

void game__run() {

    bool exit_requested = false;

    // test draw
    move(5, 5);
    addch('h');

    while (1) {
        int in_char = wgetch(wnd);
        switch (in_char) {
            case 'q':
                exit_requested = true;
                break;
            case KEY_UP:
                break;
            case KEY_DOWN:
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            default:
                break;
        }

        usleep(GAME_SLEEP);
        refresh();

        if (exit_requested) {
            break;
        }
    }
}

void game__close() {
    endwin();
}