#include "food.h"

static FoodKind _rand_food_kind() {
    return (double)rand() / (double)RAND_MAX < SHRINK_FOOD_PROB ? SHRINK : GROW;
}

struct Food {
    Position positions[MAX_FOOD]; // Position of foods
    int kinds[MAX_FOOD];          // Type of food
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
            FoodKind kind = _rand_food_kind();
            if (!contains(invalid_positions, pos)) {
                f->n_food++;
                f->positions[f->n_food - 1] = pos;
                f->kinds[f->n_food - 1] = kind;
                return;
            }
            count++;
        }
    }
}

const Position *food__get_positions(Food *f) {
    return (const Position *)(f->positions);
}

const FoodKind *food__get_kinds(Food *f) {
    return (const FoodKind *)(f->kinds);
}

FoodKind food__get_kind(Food *f, int i) {
    return f->kinds[i];
}

size_t food__get_count(Food *f) {
    return f->n_food;
}

void food__remove(Food *f, int i) {
    for (int x = i; x < f->n_food - 1; x++) {
        f->positions[x] = f->positions[x + 1];
        f->kinds[x] = f->kinds[x + 1];
    }
    f->n_food--;
}