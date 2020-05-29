#ifndef GAME_H_
#define GAME_H_

#include "structs.h"

typedef struct Game Game;

Game *game__create(int width, int height);
void game__run(Game *game);
void game__destroy(Game *game);

static void game__close(Game *game);
static void game__init(Game *game);
static void game__update(Game *game);
static void game__draw(Game *game);
void game__apply_input(Game *game, Input input);

/**
 * Detect and handle collisions. Update game status accordingly.
 * @param game Pointer to game.
 */
static void game__collisions(Game *game);

#endif // GAME_H_