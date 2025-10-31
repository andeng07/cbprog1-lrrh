#include <stdlib.h>
#include "game_object.h"

void rotate(GameObject *obj) {
    if (obj->direction == UNDEFINED) return;

    int delta = 1;

    obj->direction = (obj->direction + delta) % 4;
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
        default:
            return 0;
            break;
    }

    *outX = object->x + deltaX;
    *outY = object->y + deltaY;
    
    return 1;
}


char* get_type_name(ObjectType type) {
    switch (type) {
        case LITTLE_RED_RIDING_HOOD: return "Little Red Riding Hood";
        case GRANNY:                 return "Granny";
        case PIT:                    return "Pit";
        case WOODSMAN:               return "Woodsman";
        case BAKESHOP:               return "Bakeshop";
        case FLOWER:                 return "Flower";
        case WOLF:                   return "Wolf";
        case EMPTY:                  return "Empty";
        default:                     return "Unknown";
    }
}