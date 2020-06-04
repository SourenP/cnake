#ifndef GAME_H_
#define GAME_H_

#include "common.h"

typedef struct Game Game;

Game *game__create();
void game__destroy(Game *game);

/**
 * Run main game loop until game status is set to exit.
 * Loop includes:
 * - Update
 * - Draw
 * - Check exit
 *
 * @param game Game.
 */
void game__run(Game *game);

/**
 * Initialize values of game.
 * This must be called before game_run.
 *
 * @param game Game.
 */
void game__init(Game *game, int width, int height);

#endif // GAME_H_