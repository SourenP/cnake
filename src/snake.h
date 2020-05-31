#ifndef SNAKE_H_
#define SNAKE_H_

#include "common.h"
#include "structs.h"

typedef struct Snake Snake;

Snake *snake__create(Position pos, int dx, int dy);
void snake__destroy(Snake *s);
void snake__make_empty(Snake *s);
bool snake__push(Snake *s, Position pos);
void snake__apply_input(Snake *s, Input input);
void snake__update(Snake *s);
const PositionNode *snake__get_head(Snake *s);
Position snake__get_ate_pos(Snake *s);
void snake__ate(Snake *s);

#endif // SNAKE_H_