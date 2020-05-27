#ifndef GAME_H_
#define GAME_H_

typedef struct game_type *Game;

Game game__create(int width, int height);
void game__run(Game game);
void game__destroy(Game game);

static void game__close(Game game);
static int game__init(Game game);
static enum Input game__get_input(Game game);
static void game__update(Game game);
static void game__draw(Game game);

#endif // GAME_H_