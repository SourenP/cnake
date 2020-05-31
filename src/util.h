#ifndef UTIL_H_
#define UTIL_H_

#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

/**
 * @return True if linked list of PositionNodes contains pos value
 */
bool contains(const PositionNode *position_nodes, Position pos);

#endif // UTIL_H_