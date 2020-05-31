#ifndef DEFS_H_
#define DEFS_H_

/* Util */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define nelem(a) (sizeof(a) / sizeof(a[0]))

/* Game loop */
#define GAME_SLEEP 160000

/* Dimensions */
#define GAME_WIDTH 51
#define GAME_HEIGHT 31
#define BORDER_THICKNESS 1

/* Food */
#define MAX_FOOD 4

/* Player snake */
#define START_X ((int)GAME_WIDTH / 2)
#define START_Y ((int)GAME_HEIGHT / 2)
#define MAX_SNAKE_SIZE (GAME_WIDTH * GAME_HEIGHT)

/* Rendered characters */
#define SNAKE_HEAD '@'
#define SNAKE_BODY '#'
#define BORDER_TOP '-'
#define BORDER_SIDE '|'
#define FLOOR ' '
#define FOOD_CHAR '*'

#endif // DEFS_H_
