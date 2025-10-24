#include <stdlib.h>
#include "game_object.h"

void rotate(GameObject *obj, RotationDirection direction) {
    if (obj->direction == UNDEFINED) return;

    int delta = (direction == ROTATE_RIGHT) ? 1 : -1;

    // add 4 padding to avoid negative value
    obj->direction = (obj->direction + delta + 4) % 4;
}

void set_pos(GameObject *obj, int x, int y) {
    obj->x = x;
    obj->y = y;
}

GameObject *empty_game_object(int x, int y, Status status) {
    GameObject *obj = malloc(sizeof(GameObject));
    obj->type = EMPTY;
    obj->direction = UNDEFINED;
    obj->status = status;

    set_pos(obj, x, y);

    return obj;
}