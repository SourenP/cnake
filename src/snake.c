#include "snake.h"

struct node {
    Position pos;
    struct node *next;
};

struct snake_type {
    struct node *top;
    Position pos;
    int dx, dy;
    char head;
    char body;
};

Snake snake__create(Position pos, int dx, int dy, char head, char body) {
    Snake s = malloc(sizeof(struct snake_type));
    assert(s != NULL);
    s->top = NULL;
    s->pos = pos;
    s->dx = dx;
    s->dy = dy;
    s->head = head;
    s->body = body;
    return s;
}

void snake__destroy(Snake s) {
    snake__make_empty(s);
    free(s);
}

void snake__make_empty(Snake s) {
    while (!snake__is_empty(s)) {
        snake__pop(s);
    }
}

bool snake__is_empty(Snake s) {
    return snake__size(s) == 0;
}

size_t snake__size(Snake s) {
    struct node *n = s->top;
    if (n == NULL) {
        return 0;
    }

    size_t count = 1;
    while (n->next != NULL) {
        count++;
        n = n->next;
    }
    return count;
}

bool snake__push(Snake s, Position pos) {
    // Allocate
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        return false;
    }

    // Populate
    new_node->pos = pos;
    new_node->next = s->top;

    // Swap top
    s->top = new_node;

    return true;
}

Position snake__pop(Snake s) {
    if (snake__is_empty(s)) {
        printf("*** Snake underflow; program terminated. ***\n");
        exit(EXIT_FAILURE);
    }

    struct node *old_top = s->top;
    Position out = old_top->pos;
    s->top = old_top->next;
    free(old_top);

    return out;
}

Position snake__get_pos(Snake s) {
    return s->pos;
}

void snake__apply_input(Snake s, enum Input input) {
    switch (input) {
        case INPUT_UP:
            s->dx = 0;
            s->dy = -1;
            break;
        case INPUT_DOWN:
            s->dx = 0;
            s->dy = 1;
            break;
        case INPUT_LEFT:
            s->dx = -1;
            s->dy = 0;
            break;
        case INPUT_RIGHT:
            s->dx = 1;
            s->dy = 0;
            break;
        default:
            break;
    }
}

void snake__update(Snake s) {
    // move head
    s->pos.x += s->dx;
    s->pos.y += s->dy;

    // todo(sourenp): also move body (nodes)
}