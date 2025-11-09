#include <stdlib.h>
#include "game_object.h"

void rotate(GameObject *pObj) {
    int delta = 0;

    if (pObj->direction == UNDEFINED) return;

    delta = 1;

    pObj->direction = (pObj->direction + delta) % 4;
}

void setPosition(GameObject *pObj, int nPosX, int nPosY) {
    pObj->nPosX = nPosX;
    pObj->nPosY = nPosY;
}

GameObject *emptyGameObject(int nPosX, int nPosY, Status status) {
    GameObject *obj = malloc(sizeof(GameObject));
    obj->type = EMPTY;
    obj->direction = UNDEFINED;
    obj->status = status;

    setPosition(obj, nPosX, nPosY);

    return obj;
}

int getForwardCoordinate(GameObject *pObj, int *pOutX, int *pOutY) {
    int deltaX = 0, deltaY = 0;

    if (pObj->direction == UNDEFINED) return 0;

    switch (pObj->direction) {
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

    *pOutX = pObj->nPosX + deltaX;
    *pOutY = pObj->nPosY + deltaY;
    
    return 1;
}


char* getTypeName(ObjectType type) {
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