#ifndef STRUCTS_H_
#define STRUCTS_H_

enum Input {
    INPUT_NONE,
    INPUT_EXIT,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT
};
typedef enum Input Input;

enum GameStatus { GAME_EXIT, GAME_OK };
typedef enum GameStatus GameStatus;

typedef struct position {
    int x, y;
} Position;

#endif