#include "curses_util.h"

#include <string.h>

WINDOW *curses_init(int width, int height) {
    // Init curses
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    WINDOW *wnd = newwin(height + 2 * BORDER_THICKNESS,
                         width + 2 * BORDER_THICKNESS, 0, 0);
    box(wnd, BORDER_SIDE_CHAR, BORDER_TOP_CHAR);
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

void curses_draw_tiles(WINDOW *wnd, TileType **tiles, size_t width,

                       size_t height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            mvwaddch(wnd, i + BORDER_THICKNESS, j + BORDER_THICKNESS,
                     TileCharMap[tiles[i][j]]);
        }
    }
}

void curses_draw_game_over(WINDOW *wnd, size_t width, size_t height,
                           int score) {
    // Clear tiles
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            mvwaddch(wnd, i + BORDER_THICKNESS, j + BORDER_THICKNESS,
                     FLOOR_CHAR);
        }
    }

    // Draw game over
    int vert_pos = height / 2 - 1;
    static char over_str[] = "GAME OVER";
    int over_horz_pos = (width - strlen(over_str)) / 2;
    for (int i = 0; i < strlen(over_str); i++) {
        mvwaddch(wnd, vert_pos + BORDER_THICKNESS,
                 (over_horz_pos++) + BORDER_THICKNESS, over_str[i]);
    }

    // Draw score
    static char score_str[256];
    snprintf(score_str, sizeof(score_str), "%d", score);
    int score_horz_pos = (width - strlen(score_str)) / 2;
    for (int i = 0; i < strlen(score_str); i++) {
        mvwaddch(wnd, vert_pos + 2 + BORDER_THICKNESS,
                 (score_horz_pos++) + BORDER_THICKNESS, score_str[i]);
    }
}