#ifndef DEFS_H_
#define DEFS_H_

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define nelem(a) (sizeof(a) / sizeof(a[0]))

#define GAME_SLEEP 80000

#define GAME_WIDTH 31
#define GAME_HEIGHT 15

#define START_X ((int)GAME_WIDTH / 2)
#define START_Y ((int)GAME_HEIGHT / 2)

#define SNAKE_HEAD '@'
#define SNAKE_BODY '*'

#define FLOOR ' '

#define BORDER_THICKNESS 1

#endif // DEFS_H_
