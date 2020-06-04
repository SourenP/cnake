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
#define SHRINK_FOOD_PROB 0.2

/* Player snake */
#define START_X ((int)GAME_WIDTH / 2)
#define START_Y ((int)GAME_HEIGHT - 2)

/* Rendered characters */
#define SNAKE_HEAD '@'
#define SNAKE_BODY '*'
#define SNAKE_ATE '#'
#define BORDER_TOP '-'
#define BORDER_SIDE '|'
#define FLOOR ' '
#define GROW_FOOD_CHAR 'o'
#define SHRINK_FOOD_CHAR 'x'

#endif // DEFS_H_
