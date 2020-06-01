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

/**
 * Apply input and update game state correspondingly.
 *
 * @param game Game.
 */
static void _game__update(Game *game);

/**
 * Draw game state onto grid.
 *
 * @param game Game.
 */
static void _game__draw(Game *game);

/**
 * Apply input recieved from user to game state.
 *
 * @param game Game.
 * @param input Input.
 */
static void _game__apply_input(Game *game, Input input);

/**
 * Detect and handle collisions. Update game state accordingly.
 *
 * @param game Game.
 */
static void _game__collisions(Game *game);

#endif // GAME_H_