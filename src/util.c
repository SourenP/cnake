#include "util.h"

bool contains(const PositionNode *position_nodes, Position pos) {
    const PositionNode *curr_node = position_nodes;
    Position curr_pos;
    while (curr_node != NULL) {
        curr_pos = curr_node->pos;
        if (curr_pos.x == pos.x && curr_pos.y == pos.y) {
            return true;
        }
        curr_node = curr_node->next;
    }
    return false;
}