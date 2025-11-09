#include <stdlib.h>
#include "game_board.h"
#include "game_object.h"

GameBoard *createGameBoard(int nSize, int nDevMode) {
    int i, j;

    GameBoard *board = malloc(sizeof(GameBoard));

    board->nSize = nSize;

    board->cells = malloc(nSize * sizeof(GameObject *));

    for (i = 0; i < nSize; i++) {
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

    pBoard->cells[fromY][fromX] = *emptyGameObject(fromX, fromY, VISIBLE);

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