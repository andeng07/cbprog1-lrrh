#include <stdlib.h>
#include "game_board.h"
#include "game_object.h"

GameBoard *createGameBoard(int nSize, int nDevMode) {
    int i, j;
    
    /*
        allocate memory according to the GameBoard's struct size.
        this was made to avoid re-duplication of GameBoard 
        in memory. 
    */ 
    GameBoard *board = malloc(sizeof(GameBoard));

    board->nSize = nSize;

    /* 
        allocate an array of arrays
     */
    board->cells = malloc(nSize * sizeof(GameObject *));

    for (i = 0; i < nSize; i++) {
        /*
            allocate an array that represents a row
        */
        GameObject *row = malloc(nSize * sizeof(GameObject));

        for (j = 0; j < nSize; j++) {
            GameObject empty = *emptyGameObject(j, i, nDevMode);
            row[j] = empty;
        }

        board->cells[i] = row;
    }

    return board;
}

void destroyGameBoard(GameBoard* pBoard) {
    free(pBoard->cells);
    free(pBoard);
}

void placeObject(GameBoard *pBoard, GameObject *pObj, int nPosX, int nPosY) {
    pBoard->cells[nPosY][nPosX] = *pObj;

    setPosition(pObj, nPosX, nPosY);
}

void moveObject(GameBoard *pBoard, GameObject *pObj, int nDestX, int nDestY) {
    int fromX = pObj->nPosX;
    int fromY = pObj->nPosY;

    GameObject destObj = pBoard->cells[nDestY][nDestX];

    if (pBoard->pPersistedObject != NULL) {
        GameObject *pPersisted = pBoard->pPersistedObject;

        if (pPersisted->nPosX == fromX && pPersisted->nPosY == fromY) {
            pBoard->cells[fromY][fromX] = *pPersisted;
        } else {
            pBoard->cells[fromY][fromX] = *emptyGameObject(fromX, fromY, VISIBLE);
        }

        free(pBoard->pPersistedObject);
        pBoard->pPersistedObject = NULL;
    } else {
        pBoard->cells[fromY][fromX] = *emptyGameObject(fromX, fromY, VISIBLE);
    }

    if (getTypeMetadata(destObj.type)->nIsCollissionPersistent) {
        GameObject *copy = malloc(sizeof(GameObject));
        *copy = destObj;
        pBoard->pPersistedObject = copy;
    }

    setPosition(pObj, nDestX, nDestY);
    pBoard->cells[nDestY][nDestX] = *pObj;
}

GameObject *getObjectAtPosition(GameBoard *pBoard, int nPosX, int nPosY) {
    int is_valid = isValidPosition(pBoard, nPosX, nPosY);

    if (!is_valid) return NULL;

    return &pBoard->cells[nPosY][nPosX];
}

int isValidPosition(GameBoard *pBoard, int nPosX, int nPosY) {
    int size = pBoard->nSize;

    if (nPosX < 0 || nPosX > size - 1 || nPosY < 0 || nPosY > size - 1) {
        return 0;
    }

    return 1;
}

int getLocationOfType(GameBoard *pBoard, ObjectType type, int *nOutX, int *nOutY) {
    int i, j, nFound = 0; 

    for (i = 0; i < pBoard->nSize; i++) {
        for (j = 0; j < pBoard->nSize; j++) {
            if (pBoard->cells[i][j].type == type && !nFound) {
                *nOutX = j;
                *nOutY = i;
                nFound = 1;
            }
        }
    }

    return nFound;
}

int getDistance(GameBoard *pBoard, ObjectType typeOne, ObjectType typeTwo) {
    int nTypeOneLocX, nTypeOneLocY;

    int resultOne = getLocationOfType(pBoard, typeOne, &nTypeOneLocX, &nTypeOneLocY);

    int nTypeTwoLocX, nTypeTwoLocY;
    
    int resultTwo = getLocationOfType(pBoard, typeTwo, &nTypeTwoLocX, &nTypeTwoLocY);

    if (resultOne == -1 || resultTwo == -1) return -1;

    return abs(nTypeOneLocX - nTypeTwoLocX) + abs(nTypeOneLocY - nTypeTwoLocY);
}