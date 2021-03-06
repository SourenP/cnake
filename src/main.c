#include "main.h"

#include "game.h"
#include "grid.h"

int main(int argc, char *argv[]) {
    Game *game = game__create();
    game__init(game, GAME_WIDTH, GAME_HEIGHT);
    game__run(game);
    game__destroy(game);
}