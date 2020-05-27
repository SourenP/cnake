#ifndef GAME_H_
#define GAME_H_

int game__init();
void game__run();
void game__close();

static enum Input game__get_input();
static void game__update();
static void game__draw();

#endif // GAME_H_