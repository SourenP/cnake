#include "collision.h"

bool collision__out_of_bounds(Snake *s, Grid *g) {
    return !grid__in_bounds(g, snake__get_pos(s));
}

int collision__snake_food(Snake *s, Food *f) {
    const Position *food_pos = food__get_positions(f);
    size_t n_food = food__get_count(f);
    const Position snake_pos = snake__get_pos(s);
    for (int i = 0; i < n_food; i++) {
        if (snake_pos.x == food_pos[i].x && snake_pos.y == food_pos[i].y) {
            return i;
        }
    }
    return -1;
}