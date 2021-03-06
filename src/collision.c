#include "collision.h"

bool collision__out_of_bounds(Snake *s, Grid *g) {
    return !grid__in_bounds(g, snake__get_head(s)->pos);
}

int collision__snake_food(Snake *s, Food *f) {
    const Position *food_pos = food__get_positions(f);
    size_t n_food = food__get_count(f);
    const Position head_pos = snake__get_head(s)->pos;
    for (int i = 0; i < n_food; i++) {
        if (head_pos.x == food_pos[i].x && head_pos.y == food_pos[i].y) {
            return i;
        }
    }
    return -1;
}

bool collision__snake_snake(Snake *s) {
    const PositionNode *head = snake__get_head(s);
    return contains(head->next, head->pos);
}