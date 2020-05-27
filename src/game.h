#ifndef GAME_H_
#define GAME_H_

enum Input { INPUT_NONE, INPUT_EXIT, INPUT_UP, INPUT_DOWN, INPUT_LEFT, INPUT_RIGHT };

int game__init();
void game__run();
void game__close();

static enum Input game__getInput();
static void game__draw();

#endif // GAME_H_