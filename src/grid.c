#include "grid.h"

#include <assert.h>

#include "curses_util.h"

struct Grid {
    size_t width, height;
    TileType **tiles;
};

Grid *grid__create(size_t width, size_t height, TileType fill_tile) {
    Grid *g = (Grid *)hisho_ff__alloc(sizeof(struct Grid));
    assert(g != NULL);
    g->tiles = (TileType **)hisho_ff__alloc(height * sizeof(char *));
    assert(g->tiles != NULL);
    for (int i = 0; i < height; i++) {
        g->tiles[i] = (TileType *)hisho_ff__alloc(width * sizeof(char *));
        assert(g->tiles[i] != NULL);
    }
    g->width = width;
    g->height = height;
    grid__fill(g, fill_tile);
    return g;
}

void grid__fill(Grid *g, TileType fill_tile) {
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            g->tiles[i][j] = fill_tile;
        }
    }
}

void grid__destroy(Grid *g) {
    for (int i = 0; i < g->height; i++) {
        hisho_ff__free(g->tiles[i]);
    }
    hisho_ff__free(g->tiles);
    hisho_ff__free(g);
}

void grid__draw(Grid *g, WINDOW *wnd) {
    curses_draw_tiles(wnd, g->tiles, g->width, g->height);
}

void grid__add_snake(Grid *g, Snake *s) {
    const PositionNode *head = snake__get_head(s);

    // Draw body
    const PositionNode *curr = head->next;
    while (curr != NULL) {
        Position snake_pos = curr->pos;
        g->tiles[snake_pos.y][snake_pos.x] =
            curr->food_kind != NO_FOOD ? SNAKE_ATE_TILE : SNAKE_BODY_TILE;
        curr = curr->next;
    }

    // Draw head
    g->tiles[head->pos.y][head->pos.x] = SNAKE_HEAD_TILE;
}

void grid__add_food(Grid *g, Food *f) {
    const Position *food_pos = food__get_positions(f);
    const FoodKind *food_kind = food__get_kinds(f);
    size_t n_food = food__get_count(f);
    for (int i = 0; i < n_food; i++) {
        assert(food_kind[i] != NO_FOOD);
        g->tiles[food_pos[i].y][food_pos[i].x] =
            food_kind[i] == GROW ? GROW_FOOD_TILE : SHRINK_FOOD_TILE;
    }
}

bool grid__in_bounds(Grid *g, Position pos) {
    if (pos.x >= 0 && pos.x < g->width && pos.y >= 0 && pos.y < g->height) {
        return true;
    }
    return false;
}