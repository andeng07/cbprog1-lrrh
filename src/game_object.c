#include <stdlib.h>
#include "game_object.h"

void rotate(GameObject *pObj, RotationDirection direction) {
    int delta = 0;

    if (pObj->direction == UNDEFINED) return;

    delta = (direction == ROTATE_RIGHT) ? 1 : -1;

    /* add 4 to avoid processing negative values */
    pObj->direction = (pObj->direction + delta + 4) % 4;
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

ObjectTypeMetadata *getTypeMetadata(ObjectType type) {
    ObjectTypeMetadata *metadata = malloc(sizeof(ObjectTypeMetadata));

    switch (type) {
        case LITTLE_RED_RIDING_HOOD: {
            metadata->type = LITTLE_RED_RIDING_HOOD;
            metadata->nIsCollissionPersistent = 1;
            metadata->pName = "Little Red Riding Hood";
            metadata->pSenseName = "N/A";
            metadata->cLandmark = 'L';
            break;
        }
        case GRANNY: {
            metadata->type = GRANNY;
            metadata->nIsCollissionPersistent = 1;
            metadata->pName = "Granny";
            metadata->pSenseName = "Light";
            metadata->cLandmark = 'G';
            break;
        }
        case PIT: {
            metadata->type = PIT;
            metadata->nIsCollissionPersistent = 1;
            metadata->pName = "Pit";
            metadata->pSenseName = "Breeze";
            metadata->cLandmark = 'P';
            break;
        }
        case WOLF: {
            metadata->type = WOLF;
            metadata->nIsCollissionPersistent = 1;
            metadata->pName = "Wolf";
            metadata->pSenseName = "Howl";
            metadata->cLandmark = 'W';
            break;
        }
        case WOODSMAN: {
            metadata->type = WOODSMAN;
            metadata->nIsCollissionPersistent = 0;
            metadata->pName = "Woodsman";
            metadata->pSenseName = "Sound";
            metadata->cLandmark = 'M';
            break;
        }
        case BAKESHOP: {
            metadata->type = BAKESHOP;
            metadata->nIsCollissionPersistent = 1;
            metadata->pName = "Bakeshop";
            metadata->pSenseName = "Heat";
            metadata->cLandmark = 'B';
            break;
        }
        case FLOWER: {
            metadata->type = FLOWER;
            metadata->nIsCollissionPersistent = 0;
            metadata->pName = "Flower";
            metadata->pSenseName = "Scent";
            metadata->cLandmark = 'F';
            break;
        }
        case EMPTY: {
            metadata->type = EMPTY;
            metadata->nIsCollissionPersistent = 0;
            metadata->pName = "Empty";
            metadata->pSenseName = "None";
            metadata->cLandmark = ' ';
            break;
        }

        default: return NULL;
    };

    return metadata;
}