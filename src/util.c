#include "util.h"

bool contains(Position *positions, size_t size, Position pos) {
    for (int i = 0; i < size; i++) {
        if (positions[i].x == pos.x && positions[i].y == pos.y) {
            return true;
        }
    }
    return false;
}