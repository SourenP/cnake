#include <ncurses.h>
#include <unistd.h>

#include "game.h"

#include "common.h"
#include "defs.h"
#include "grid.h"
#include "snake.h"

struct game_type {
    WINDOW *wnd;
    Grid grid;
    Snake snake;
    int input;
    int width;
    int height;
};

Game game__create(int width, int height) {
    Game game = calloc(1, sizeof(struct game_type));
    game->width = width;
    game->height = height;
    assert(game != NULL);
    game__init(game);
    return game;
}

void game__run(Game game) {
    while (1) {
        game->input = game__get_input(game);

        game__update(game);
        game__draw(game);

        usleep(GAME_SLEEP);
        refresh();

        if (game->input == INPUT_EXIT) {
            break;
        }
    }

    game__close(game);
}

void game__destroy(Game game) {
    free(game);
}

int game__init(Game game) {
    // Init curses
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    game->wnd = newwin(game->height + 2 * BORDER_THICKNESS,
                       game->width + 2 * BORDER_THICKNESS, 0, 0);
    box(game->wnd, '|', '-');
    keypad(game->wnd, true);
    nodelay(game->wnd, true);
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
    wbkgd(game->wnd, COLOR_PAIR(1));

    // Init game vars
    game->input = INPUT_NONE;
    game->grid = grid__create(game->width, game->height, FLOOR);
    game->snake = snake__create((Position){.x = START_X, .y = START_Y}, 0, 0,
                                SNAKE_HEAD, SNAKE_BODY);

    return 0;
}

void game__close(Game game) {
    grid__destroy(game->grid);
    snake__destroy(game->snake);
    endwin();
}

enum Input game__get_input(Game game) {
    int in_char = wgetch(game->wnd);
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

void game__update(Game game) {
    snake__apply_input(game->snake, game->input);
    snake__update(game->snake);
}

void game__draw(Game game) {
    grid__fill(game->grid, FLOOR);
    grid__add_snake(game->grid, game->snake);
    grid__draw(game->grid, game->wnd);
}
