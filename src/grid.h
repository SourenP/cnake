#ifndef GRID_H_
#define GRID_H_

#include <ncurses.h>
#include <unistd.h>

#include "common.h"
#include "snake.h"

typedef struct grid_type *Grid;

Grid grid__create(size_t width, size_t height, char fill_char);
void grid__destroy(Grid g);
void grid__fill(Grid g, char fill_char);
void grid__draw(Grid g, WINDOW *wnd);
void grid__add_snake(Grid g, Snake s);

#endif // GRID_H_