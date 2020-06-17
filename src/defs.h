#ifndef DEFS_H_
#define DEFS_H_

/* Util */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define nelem(a) (sizeof(a) / sizeof(a[0]))

/* Game loop */
#define GAME_SLEEP 140000

/* Dimensions */
#define GAME_WIDTH 24
#define GAME_HEIGHT 13
#define BORDER_THICKNESS 1

/* Food */
#define MAX_FOOD 4
#define SHRINK_FOOD_PROB 0.3

/* Player snake */
#define START_X ((int)GAME_WIDTH / 2)
#define START_Y ((int)GAME_HEIGHT - 2)

/* Rendered characters */
static const char SNAKE_HEAD_CHAR = '@';
static const char SNAKE_BODY_CHAR = '*';
static const char SNAKE_ATE_CHAR = '#';
static const char FLOOR_CHAR = ' ';
static const char GROW_FOOD_CHAR = 'o';
static const char SHRINK_FOOD_CHAR = 'x';
static const char BORDER_TOP_CHAR = '-';
static const char BORDER_SIDE_CHAR = '|';

/* Grid Tiles */
typedef enum TileType {
    FLOOR_TILE,
    GROW_FOOD_TILE,
    SHRINK_FOOD_TILE,
    SNAKE_HEAD_TILE,
    SNAKE_BODY_TILE,
    SNAKE_ATE_TILE,
} TileType;

static const char TileCharMap[] = {[FLOOR_TILE] = FLOOR_CHAR,
                                   [GROW_FOOD_TILE] = GROW_FOOD_CHAR,
                                   [SHRINK_FOOD_TILE] = SHRINK_FOOD_CHAR,
                                   [SNAKE_HEAD_TILE] = SNAKE_HEAD_CHAR,
                                   [SNAKE_BODY_TILE] = SNAKE_BODY_CHAR,
                                   [SNAKE_ATE_TILE] = SNAKE_ATE_CHAR};

#endif // DEFS_H_
