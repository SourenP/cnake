#include "game.h"

#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#include "collision.h"
#include "common.h"
#include "curses_util.h"
#include "defs.h"
#include "food.h"
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

    /* State */
    GameStatus status;
    Grid *grid;
    Snake *snake;
    Food *food;
};

Game *game__create(int width, int height) {
    Game *game = hisho_ff__alloc(sizeof(struct Game));
    game->wnd = curses_init(width, height);
    game->width = width;
    game->height = height;
    game->status = GAME_OK;
    assert(game != NULL);
    game__init(game);
    return game;
}

void game__run(Game *game) {
    while (1) {
        game__update(game);

        game__draw(game);

        usleep(GAME_SLEEP);
        refresh();

        if (game->status == GAME_EXIT) {
            break;
        }
    }

    game__close(game);
}

void game__destroy(Game *game) {
    curses_terminate(game->wnd);
    hisho_ff__free(game);
}

void game__init(Game *game) {
    /* Init game */
    srand(time(NULL));
    game->ctx = game->wnd;
    game->input = curses_input;
    game->grid = grid__create(game->width, game->height, FLOOR);
    game->snake = snake__create((Position){.x = START_X, .y = START_Y}, 0, 0);
    game->food = food__create(game->width, game->height);
}

void game__close(Game *game) {
    grid__destroy(game->grid);
    snake__destroy(game->snake);
    food__destroy(game->food);
}

void game__update(Game *game) {
    /* Get and apply input */
    Input input = game->input(game->ctx);
    game__apply_input(game, input);

    // Exit early if game exit or over
    if (game->status == GAME_EXIT || game->status == GAME_OVER) {
        return;
    }

    /* Update game state */
    snake__update(game->snake);
    game__collisions(game);

    food__spawn(game->food, snake__get_head(game->snake));
}

void game__apply_input(Game *game, Input input) {
    if (input == INPUT_EXIT) {
        game->status = GAME_EXIT;
    }
    snake__apply_input(game->snake, input);
}

void game__draw(Game *game) {
    grid__fill(game->grid, FLOOR);

    if (game->status == GAME_OVER) {
        grid__add_game_over(game->grid);
    } else {
        grid__add_food(game->grid, game->food);
        grid__add_snake(game->grid, game->snake);
    }

    grid__draw(game->grid, game->wnd);
}

void game__collisions(Game *game) {
    if (collision__out_of_bounds(game->snake, game->grid)) {
        game->status = GAME_OVER;
    }
    int eaten_food_i = collision__snake_food(game->snake, game->food);
    if (eaten_food_i >= 0) {
        fprintf(stderr, "eaten %d", eaten_food_i);
        food__remove(game->food, eaten_food_i);
    }
}