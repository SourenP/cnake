/**
 * Snake implemented as a dynamically allocated linked list.
 * Movement and food propogate down from the head to the tail.
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include "common.h"
#include "structs.h"

typedef struct Snake Snake;

Snake *snake__create(Position pos, int dx, int dy);

/**
 * @param
 */
void snake__destroy(Snake *s);

/**
 * Add a new node to the end of the snake.
 *
 * @param s Snake
 * @param pos Position to add the new node to
 * @return True if node was added successfully. Fails if memory allocation
 * fails.
 */
bool snake__push(Snake *s, Position pos);

/**
 * Apply user input to snake. Changes direction of snake.
 *
 * @param s Snake
 * @param input Input
 */
void snake__apply_input(Snake *s, Input input);

/**
 * Update snake.
 * Move head, body, food and potentially add new node.
 *
 *@param s Snake
 */
void snake__update(Snake *s);

/**
 * Indicate to snake that it ate food.
 * This will add a food to the head which will flow down the body and eventually
 * add a node at the tail.
 *
 * @param s Snake
 */
void snake__ate(Snake *s);

/**
 * @return Pointer to snake head.
 */
const PositionNode *snake__get_head(Snake *s);

/**
 * @return Snake size not counting head.
 */
size_t snake__get_size(Snake *s);

#endif // SNAKE_H_