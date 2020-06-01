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

/**
 * Overwrite all grid characters with specified character.
 *
 * @param g Grid
 * @param fill_char Character to fill with
 */
void grid__fill(Grid *g, char fill_char);

/**
 * Draw grid characters onto ncurses grid.
 * This should be called after the grid is populated with the game state.
 *
 * @param g Grid
 * @param wnd Ncurses window to draw onto.
 */
void grid__draw(Grid *g, WINDOW *wnd);

/**
 * Draw snake onto grid.
 *
 * @param g Grid
 * @param s Snake
 */
void grid__add_snake(Grid *g, Snake *s);

/**
 * Draw food onto grid.
 *
 * @param g Grid
 * @param s Food
 */
void grid__add_food(Grid *g, Food *f);

/**
 * Check if position is within bounds of grid. Used for collision.
 *
 * @param g Grid
 * @param p Posision to check
 * @return True if position p is within grid bounds
 */
bool grid__in_bounds(Grid *g, Position p);

/**
 * Draw game over and score onto grid.
 * Score equal to snake size.
 *
 * @param g Grid
 * @param s Snake
 */
void grid__add_game_over(Grid *g, Snake *s);

#endif // GRID_H_