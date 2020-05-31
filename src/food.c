#include "food.h"

struct Food {
    Position positions[MAX_FOOD]; // Position of foods
    size_t n_food;                // Number of foods present
    size_t width;                 // Width of bounds in which food can spawn
    size_t height;                // Height of bounds in which food can spawn
};

Food *food__create(size_t width, size_t height) {
    Food *f = hisho_ff__alloc(sizeof(struct Food));
    f->width = width;
    f->height = height;
    f->n_food = 0;
    return f;
}

void food__destroy(Food *f) {
    hisho_ff__free(f);
}

void food__spawn(Food *f, const PositionNode *invalid_positions) {
    static size_t max_iter = GAME_WIDTH * GAME_HEIGHT;
    if (f->n_food < MAX_FOOD) {
        size_t count = 0;
        while (count < max_iter) {
            Position pos =
                (Position){.x = (rand() % f->width), .y = (rand() % f->height)};
            if (!contains(invalid_positions, pos)) {
                f->positions[f->n_food++] = pos;
                return;
            }
            count++;
        }
    }
}

const Position *food__get_positions(Food *food) {
    return (const Position *)(food->positions);
}

size_t food__get_count(Food *food) {
    return food->n_food;
}