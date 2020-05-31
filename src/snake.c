#include "snake.h"

struct Snake {
    struct PositionNode *head;
    Position pos;
    int dx, dy;
};

Snake *snake__create(Position pos, int dx, int dy) {
    Snake *s = hisho_ff__alloc(sizeof(struct Snake));
    assert(s != NULL);
    s->head = NULL;
    s->pos = pos;
    s->dx = dx;
    s->dy = dy;
    return s;
}

void snake__destroy(Snake *s) {
    snake__make_empty(s);
    hisho_ff__free(s);
}

void snake__make_empty(Snake *s) {
    while (!snake__is_empty(s)) {
        snake__pop(s);
    }
}

bool snake__is_empty(Snake *s) {
    return snake__size(s) == 0;
}

size_t snake__size(Snake *s) {
    struct PositionNode *n = s->head;
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

bool snake__push(Snake *s, Position pos) {
    // Allocate
    struct PositionNode *new_node =
        hisho_ff__alloc(sizeof(struct PositionNode));
    if (new_node == NULL) {
        return false;
    }

    // Populate
    new_node->pos = pos;
    new_node->next = s->head;

    // Swap head
    s->head = new_node;

    return true;
}

Position snake__pop(Snake *s) {
    if (snake__is_empty(s)) {
        printf("*** Snake underflow; program terminated. ***\n");
        exit(EXIT_FAILURE);
    }

    struct PositionNode *old_head = s->head;
    Position out = old_head->pos;
    s->head = old_head->next;
    hisho_ff__free(old_head);

    return out;
}

const Position snake__get_pos(Snake *s) {
    return s->pos;
}

void snake__apply_input(Snake *s, Input input) {
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

void snake__update(Snake *s) {
    // move head
    s->pos.x += s->dx;
    s->pos.y += s->dy;

    // todo(sourenp): also move body (nodes)
}

const PositionNode *snake__get_head(Snake *s) {
    return (const PositionNode *)s->head;
}
