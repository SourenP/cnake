#include <ncurses.h>
#include <unistd.h>

#include "game.h"

#include "common.h"
#include "curses_util.h"
#include "defs.h"
#include "grid.h"
#include "snake.h"

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
    game->wnd = curses_init(width, height);
    game->width = width;
    game->height = height;
    assert(game != NULL);
    game__init(game);
    return game;
}

void game__run(Game *game) {
    while (1) {
        GameStatus game_status = game__update(game);

        if (game_status == GAME_EXIT) {
            break;
        }

        game__draw(game);

        usleep(GAME_SLEEP);
        refresh();
    }

    game__close(game);
}

void game__destroy(Game *game) {
    curses_terminate(game->wnd);
    free(game);
}

void game__init(Game *game) {

    /* Init game */
    game->ctx = game->wnd;
    game->input = curses_input;
    game->grid = grid__create(game->width, game->height, FLOOR);
    game->snake = snake__create((Position){.x = START_X, .y = START_Y}, 0, 0,
                                SNAKE_HEAD, SNAKE_BODY);
}

void game__close(Game *game) {
    grid__destroy(game->grid);
    snake__destroy(game->snake);
}

GameStatus game__update(Game *game) {
    Input input = game->input(game->ctx);
    if (input == INPUT_EXIT) {
        return GAME_EXIT;
    }
    snake__apply_input(game->snake, input);
    snake__update(game->snake);
    return GAME_OK;
}

void game__draw(Game *game) {
    grid__fill(game->grid, FLOOR);
    grid__add_snake(game->grid, game->snake);
    grid__draw(game->grid, game->wnd);
}
