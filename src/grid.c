#include "grid.h"

struct Grid {
    size_t width, height;
    char **cells;
};

Grid *grid__create(size_t width, size_t height, char fill_char) {
    Grid *g = (Grid *)hisho_ff__alloc(sizeof(struct Grid));
    assert(g != NULL);
    g->cells = (char **)hisho_ff__alloc(height * sizeof(char *));
    // g->cells = (char **)calloc(height, sizeof(char *));
    assert(g->cells != NULL);
    for (int i = 0; i < height; i++) {
        g->cells[i] = (char *)hisho_ff__alloc(width * sizeof(char *));
    }
    g->width = width;
    g->height = height;
    grid__fill(g, fill_char);
    return g;
}

void grid__fill(Grid *g, char fill_char) {
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            g->cells[i][j] = fill_char;
        }
    }
}

void grid__destroy(Grid *g) {
    for (int i = 0; i < g->height; i++) {
        hisho_ff__free(g->cells[i]);
    }
    hisho_ff__free(g->cells);
    hisho_ff__free(g);
}

void grid__draw(Grid *g, WINDOW *wnd) {
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            mvwaddch(wnd, i + BORDER_THICKNESS, j + BORDER_THICKNESS,
                     g->cells[i][j]);
        }
    }
}

void grid__add_snake(Grid *g, Snake *s) {
    Position snake_pos = snake__get_pos(s);
    if (grid__in_bounds(g, snake_pos)) {
        g->cells[snake_pos.y][snake_pos.x] = SNAKE_HEAD;
    }

    // todo(sourenp): also draw body (nodes)
}

void grid__add_food(Grid *g, Food *f) {
    const Position *food_pos = food__get_positions(f);
    size_t n_food = food__get_count(f);
    for (int i = 0; i < n_food; i++) {
        g->cells[food_pos[i].y][food_pos[i].x] = FOOD_CHAR;
    }
}

bool grid__in_bounds(Grid *g, Position pos) {
    if (pos.x >= 0 && pos.x < g->width && pos.y >= 0 && pos.y < g->height) {
        return true;
    }
    return false;
}

void grid__add_game_over(Grid *g) {
    static char game_over_str[] = "GAME OVER";
    int vert_pos = g->height / 2;
    int horz_pos = (g->width - strlen(game_over_str)) / 2;
    for (int i = 0; i < strlen(game_over_str); i++) {
        g->cells[vert_pos][horz_pos++] = game_over_str[i];
    }
}