#ifndef GRID_H_
#define GRID_H_

#include <ncurses.h>
#include <unistd.h>

#include "common.h"
#include "food.h"
#include "snake.h"

typedef struct Grid Grid;

Grid *grid__create(size_t width, size_t height, char fill_char);
void grid__destroy(Grid *g);
void grid__fill(Grid *g, char fill_char);
void grid__draw(Grid *g, WINDOW *wnd);

/**
 * Draw snake onto grid if it's within bounds.
 * @param g Grid pointer
 * @param s Snake pointer
 */
void grid__add_snake(Grid *g, Snake *s);

/**
 * Draw food onto grid if it's within bounds.
 * @param g Grid pointer
 * @param s Food pointer
 */
void grid__add_food(Grid *g, Food *f);

/**
 * @param g Grid pointer
 * @param p Posision to check
 * @return True if position p is within grid bounds
 */
bool grid__in_bounds(Grid *g, Position p);

/**
 * Draw game over onto grid.
 * @param g Grid pointer
 */
void grid__add_game_over(Grid *g);

#endif // GRID_H_