#ifndef COLLISION_H_
#define COLLISION_H_

#include "grid.h"
#include "snake.h"

/**
 * Check if snake is out of the grid bounds.
 * @param s Snake to check collision for.
 * @param g Grid to get bounds from.
 * @return True if snake is out of bounds.
 */
bool collision__out_of_bounds(Snake *s, Grid *g);

#endif // COLLISION_H_