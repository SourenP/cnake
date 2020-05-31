#ifndef SNAKE_H_
#define SNAKE_H_

#include "common.h"
#include "structs.h"

typedef struct Snake Snake;

Snake *snake__create(Position pos, int dx, int dy);
void snake__destroy(Snake *s);
void snake__make_empty(Snake *s);
bool snake__is_empty(Snake *s);
size_t snake__size(Snake *s);
bool snake__push(Snake *s, Position v);
Position snake__pop(Snake *s);
const Position snake__get_pos(Snake *s);
void snake__apply_input(Snake *s, Input input);
void snake__update(Snake *s);
const PositionNode *snake__get_head(Snake *s);

#endif // SNAKE_H_