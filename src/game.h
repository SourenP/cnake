#ifndef GAME_H_
#define GAME_H_

#include "structs.h"

typedef struct Game Game;

Game *game__create(int width, int height);
void game__run(Game *game);
void game__destroy(Game *game);

static void game__close(Game *game);
static int game__init(Game *game);
static bool game__update(Game *game);
static void game__draw(Game *game);

#endif // GAME_H_