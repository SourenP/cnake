#ifndef FOOD_H_
#define FOOD_H_

#include "common.h"

typedef struct Food Food;

Food *food__create(size_t width, size_t height);
void food__destroy(Food *f);

/**
 * Try to spawn food within the width and height bounds in a position that's
 * not invalid. Note that it is possible for food not to be spawned.
 *
 * @param food Food
 * @param invalid Array of invalid positions for food to spawn
 */
void food__spawn(Food *f, const PositionNode *invalid_positions);

/**
 * @return Positions of food
 */
const Position *food__get_positions(Food *f);

/**
 * @return Kinds of food
 */
const FoodKind *food__get_kinds(Food *f);

/**
 * @return Food positions count
 */
size_t food__get_count(Food *f);

/**
 * Remove food by index.
 * @param i Index of food to remove
 */
void food__remove(Food *f, int i);

/**
 * @return Kind of food at index i
 */
FoodKind food__get_kind(Food *f, int i);

#endif // FOOD_H_