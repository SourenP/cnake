#include "main.h"

#include "game.h"

int main(int argc, char *argv[]) {
    int init_status = game__init();

    if (init_status == 0)
        game__run();

    game__close();

    return 0;
}