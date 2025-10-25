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

int get_forward_coordinate(GameObject *object, int *outX, int *outY) {
    if (object->direction == UNDEFINED) return 0;

    int deltaX = 0, deltaY = 0;

    switch (object->direction) {
        case UP:
            deltaY = -1;
            break;
        case RIGHT:
            deltaX = 1;
            break;
        case DOWN:
            deltaY = 1;
            break;
        case LEFT:
            deltaX = -1;
            break;
    }

    *outX = object->x + deltaX;
    *outY = object->y + deltaY;
    
    return 1;
}