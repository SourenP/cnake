#include "grid.h"

struct grid_type {
    size_t width, height;
    char **cells;
};

Grid grid__create(size_t width, size_t height, char fill_char) {
    Grid g = malloc(sizeof(struct grid_type));
    assert(g != NULL);
    g->cells = (char **)calloc(height, sizeof(char *));
    assert(g->cells != NULL);
    for (int i = 0; i < height; i++) {
        g->cells[i] = (char *)calloc(width, sizeof(char));
    }
    g->width = width;
    g->height = height;
    grid__fill(g, fill_char);
    return g;
}

void grid__fill(Grid g, char fill_char) {
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            g->cells[i][j] = fill_char;
        }
    }
}

void grid__destroy(Grid g) {
    for (int i = 0; i < g->height; i++) {
        free(g->cells[i]);
    }
    free(g->cells);
    free(g);
}

void grid__draw(Grid g, WINDOW *wnd) {
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            mvwaddch(wnd, i + BORDER_THICKNESS, j + BORDER_THICKNESS, g->cells[i][j]);
        }
    }
}