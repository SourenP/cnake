#include <ncurses.h>
#include <unistd.h>

#include "game.h"

#include "common.h"
#include "defs.h"
#include "grid.h"
#include "snake.h"
#include "uicurses.h"

struct Game {
    /* Params */
    size_t width;
    size_t height;

    /* Curses */
    WINDOW *wnd;

    /* Input */
    void *ctx;
    Input (*input)(void *ctx);

    /* Grid */
    Grid *grid;

    /* Snake */
    Snake *snake;
};

Game *game__create(int width, int height) {
    Game *game = calloc(1, sizeof(struct Game));
    game->width = width;
    game->height = height;
    assert(game != NULL);
    game__init(game);
    return game;
}

void game__run(Game *game) {
    while (1) {
        bool should_exit = game__update(game);
        game__draw(game);

        usleep(GAME_SLEEP);
        refresh();

        if (should_exit) {
            break;
        }
    }

    game__close(game);
}

void game__destroy(Game *game) {
    free(game);
}

int game__init(Game *game) {
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
    game->ctx = game->wnd;
    game->input = curses_input;
    game->grid = grid__create(game->width, game->height, FLOOR);
    game->snake = snake__create((Position){.x = START_X, .y = START_Y}, 0, 0,
                                SNAKE_HEAD, SNAKE_BODY);

    return 0;
}

void game__close(Game *game) {
    grid__destroy(game->grid);
    snake__destroy(game->snake);
    endwin();
}

bool game__update(Game *game) {
    Input input = game->input(game->ctx);
    snake__apply_input(game->snake, input);
    snake__update(game->snake);
    return input == INPUT_EXIT;
}

void game__draw(Game *game) {
    grid__fill(game->grid, FLOOR);
    grid__add_snake(game->grid, game->snake);
    grid__draw(game->grid, game->wnd);
}
