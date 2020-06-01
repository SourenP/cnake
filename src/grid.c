#include "grid.h"

struct Grid {
    size_t width, height;
    char **cells;
};

Grid *grid__create(size_t width, size_t height, char fill_char) {
    Grid *g = (Grid *)hisho_ff__alloc(sizeof(struct Grid));
    assert(g != NULL);
    g->cells = (char **)hisho_ff__alloc(height * sizeof(char *));
    assert(g->cells != NULL);
    for (int i = 0; i < height; i++) {
        g->cells[i] = (char *)hisho_ff__alloc(width * sizeof(char *));
        assert(g->cells[i] != NULL);
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
    const PositionNode *head = snake__get_head(s);

    // Draw body
    const PositionNode *curr = head->next;
    while (curr != NULL) {
        Position snake_pos = curr->pos;
        g->cells[curr->pos.y][curr->pos.x] =
            curr->has_food ? SNAKE_ATE : SNAKE_BODY;
        curr = curr->next;
    }

    // Draw head
    g->cells[head->pos.y][head->pos.x] = SNAKE_HEAD;
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

void grid__add_game_over(Grid *g, Snake *s) {
    int vert_pos = g->height / 2;

    // Draw game over
    static char over_str[] = "GAME OVER";
    int over_horz_pos = (g->width - strlen(over_str)) / 2;
    for (int i = 0; i < strlen(over_str); i++) {
        g->cells[vert_pos][over_horz_pos++] = over_str[i];
    }

    // Draw score
    size_t score = snake__get_size(s);
    static char score_str[256];
    snprintf(score_str, sizeof(score_str), "%zu", score);
    int score_horz_pos = (g->width - strlen(score_str)) / 2;
    for (int i = 0; i < strlen(score_str); i++) {
        g->cells[vert_pos + 2][score_horz_pos++] = score_str[i];
    }
}