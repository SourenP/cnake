#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <stdbool.h>

enum Input {
    INPUT_NONE,
    INPUT_EXIT,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_LEFT,
    INPUT_RIGHT
};
typedef enum Input Input;

enum GameStatus { GAME_EXIT, GAME_OK, GAME_OVER };
typedef enum GameStatus GameStatus;

typedef struct position {
    int x, y;
} Position;

typedef enum FoodKind { NO_FOOD, GROW, SHRINK, KIND_COUNT } FoodKind;

struct PositionNode {
    Position pos;
    FoodKind food_kind;
    struct PositionNode *next;
};
typedef struct PositionNode PositionNode;

#endif