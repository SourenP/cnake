#include "collision.h"

bool collision__out_of_bounds(Snake *s, Grid *g) {
    return !grid__in_bounds(g, snake__get_pos(s));
}