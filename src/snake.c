#include "snake.h"

struct Snake {
    PositionNode *head;
    int dx, dy;
};

Snake *snake__create(Position pos, int dx, int dy) {
    Snake *s = hisho_ff__alloc(sizeof(struct Snake));
    assert(s != NULL);
    s->head = hisho_ff__alloc(sizeof(PositionNode));
    assert(s->head != NULL);

    // Init values
    s->head->has_food = false;
    s->head->pos = pos;
    s->head->next = NULL;
    s->dx = dx;
    s->dy = dy;
    snake__push(s, (Position){pos.x - dy, pos.y - dx});
    return s;
}

void snake__destroy(Snake *s) {
    PositionNode *curr = s->head;
    PositionNode *next;

    // Free nodes
    while (curr != NULL) {
        next = curr->next;
        hisho_ff__free(curr);
        curr = next;
    }

    // Free snake
    hisho_ff__free(s);
}

bool snake__push(Snake *s, Position pos) {
    // Allocate
    struct PositionNode *new_node =
        hisho_ff__alloc(sizeof(struct PositionNode));
    if (new_node == NULL) {
        return false;
    }

    // Move to tail
    PositionNode *curr = s->head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    // Assign
    new_node->has_food = false;
    new_node->pos = pos;
    new_node->next = NULL;
    curr->next = new_node;

    return true;
}

void snake__apply_input(Snake *s, Input input) {
    switch (input) {
        case INPUT_UP:
            if (s->dy != 1) {
                s->dx = 0;
                s->dy = -1;
            }
            break;
        case INPUT_DOWN:
            if (s->dy != -1) {
                s->dx = 0;
                s->dy = 1;
            }
            break;
        case INPUT_LEFT:
            if (s->dx != 1) {
                s->dx = -1;
                s->dy = 0;
            }
            break;
        case INPUT_RIGHT:
            if (s->dx != -1) {
                s->dx = 1;
                s->dy = 0;
            }
            break;
        default:
            break;
    }
}

void snake__update(Snake *s) {

    // move body
    PositionNode *prev = s->head;
    PositionNode *curr = prev->next;
    Position move_to = prev->pos;
    bool food_to = prev->has_food;
    while (curr != NULL) {
        Position temp_pos = curr->pos;
        bool temp_food = curr->has_food;
        curr->pos = move_to;
        curr->has_food = food_to;
        // If food was passed, remove food from previous node
        if (curr->has_food) {
            prev->has_food = false;
        }
        move_to = temp_pos;
        food_to = temp_food;
        prev = curr;
        curr = curr->next;
    }
    // If food reached tail, add new node
    if (food_to) {
        snake__push(s, move_to);
    }

    // move head
    s->head->pos.x += s->dx;
    s->head->pos.y += s->dy;
}

const PositionNode *snake__get_head(Snake *s) {
    return (const PositionNode *)s->head;
}

void snake__ate(Snake *s) {
    s->head->has_food = true;
}

size_t snake__get_size(Snake *s) {
    PositionNode *curr = s->head->next;
    size_t score = 0;
    while (curr != NULL) {
        score++;
        curr = curr->next;
    }
    return score;
}