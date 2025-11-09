#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "game.h"
#include "game_board.h"
#include "io_util.h"
#include "renderer.h"

void inputObject(GameBoard *pBoard, ObjectType type, Status status);
void inputMultipleObjects(GameBoard *pBoard, ObjectType type, int nCount, Status status);
int processMove(Game *pGame, char cMove);
void gameLoop(GameBoard *pBoard, GameObject *pPlayer);

void run(void) {
    char cChoice, cDevModeChoice;

    int nBoardSize, nPitCount, nFlowerCount;

    char aScreenTitleChoices[4] = {'P', 'p', 'Q', 'q'};
    char aDevModeOptions[4] = { 'Y', 'y', 'N', 'n' };

    GameSettings gameSettings;

    GameBoard *pBoard;
    GameObject player = {LITTLE_RED_RIDING_HOOD, DOWN, VISIBLE, 0, 0};

    /* screen title */
    printTitle();

    cChoice = inputInSet("Press [P] to Play or [Q] to Quit", aScreenTitleChoices);

    if (cChoice == 'Q' || cChoice == 'q') {
        printf("Goodbye!\n");
        return;
    }

    /* ask player if they want to proceed in developer mode */
    cDevModeChoice = inputInSet("Continue with Developer Mode? [Y/N]", aDevModeOptions);

    if (cDevModeChoice == 'Y' || cDevModeChoice == 'y') {
        gameSettings.nDevMode = 1;
    } else {
        gameSettings.nDevMode = 0;
    }

    /* initialize pBoard */
    nBoardSize = inputInRange("Enter pBoard nSize", 8, 15);
    pBoard = createGameBoard(nBoardSize, gameSettings.nDevMode);

    /* place player-controlled character */
    placeObject(pBoard, &player, 0, 0);

    /* map configuration */
    nPitCount = inputInRange("Enter number of Pits in the map", 1, pBoard->nSize);
    inputMultipleObjects(pBoard, PIT, nPitCount, gameSettings.nDevMode);

    nFlowerCount = inputInRange("Enter number of Flowers in the map", 1, pBoard->nSize);
    inputMultipleObjects(pBoard, FLOWER, nFlowerCount, gameSettings.nDevMode);

    printf("Enter Wolf location:\n");
    inputObject(pBoard, WOLF, gameSettings.nDevMode);

    printf("Enter Woodsman location:\n");
    inputObject(pBoard, WOODSMAN, gameSettings.nDevMode);

    printf("Enter Granny location:\n");
    inputObject(pBoard, GRANNY, gameSettings.nDevMode);

    printf("\n");

    /* start game */
    gameLoop(pBoard, &player);

    /* free memory once done */
    destroyGameBoard(pBoard);
}

void inputObject(GameBoard *pBoard, ObjectType type, Status status) {
    int nPosX, nPosY;
    int nSize = pBoard->nSize;

    GameObject obj = { EMPTY, UNDEFINED, HIDDEN, -1, -1 };

    int nIsValid;

    do {
        nPosX = inputInRange("\tx-coordinate", 1, nSize) - 1;
        nPosY = inputInRange("\ty-coordinate", 1, nSize) - 1;

        nIsValid = getObjectAtPosition(pBoard, nPosX, nPosY)->type == EMPTY;

        if (!nIsValid) {
            printf("\tCoordinate (%d, %d) already taken. Please try again.\n", nPosX + 1, nPosY + 1);
        }
    } while (!nIsValid);

    obj.type = type;
    obj.status = status;
    obj.nPosX = nPosX;
    obj.nPosY = nPosY;

    placeObject(pBoard, &obj, nPosX, nPosY);
}

void inputMultipleObjects(GameBoard *pBoard, ObjectType type, int nCount, Status status) {
    int i;

    for (i = 0; i < nCount; i++) {
        printf("Enter %s #%d location:\n", getTypeMetadata(type)->pName, i + 1);
        inputObject(pBoard, type, status);
    }
}

int processMove(Game *pGame, char cMove) {
    GameBoard *board = pGame->pBoard;
    GameObject *player = pGame->pPlayer;
    PlayerActions *actions = pGame->pActions;

    switch (cMove) {
        case 'w': case 's': {
            int forwardX, forwardY;
            getForwardCoordinate(player, &forwardX, &forwardY);

            if (isValidPosition(board, forwardX, forwardY)) {
                GameObject *target = getObjectAtPosition(board, forwardX, forwardY);
                if (cMove == 'w' && target->type == EMPTY) {
                    moveObject(board, player, forwardX, forwardY);
                    actions->nForward++;
                } else if (cMove == 's' && target != NULL) {
                    if (target->status == HIDDEN) {
                        ObjectTypeMetadata *metadata = getTypeMetadata(target->type);

                        if (metadata != NULL) printf("You sensed: %s\n", metadata->pSenseName);

                        target->status = VISIBLE;

                        actions->nSense++;
                    }
                }
            }
            break;
        }
        case 'a': case 'd': {
            RotationDirection direction = cMove == 'a' ? ROTATE_RIGHT : ROTATE_LEFT;

            rotate(player, direction);
            placeObject(board, player, player->nPosX, player->nPosY);

            actions->nRotate++;
            break;
        }
    }

    return 0;
}

void gameLoop(GameBoard *pBoard, GameObject *pPlayer) {
    char move;

    char validMoves[] = { 'w','a','s','d','q' };

    Game game;
    PlayerActions actions = {0, 0, 0};

    game.pBoard = pBoard;
    game.pPlayer = pPlayer;

    game.nIsAlive = 1;

    game.nStatus = 0;

    game.pActions = &actions;

    while(game.nIsAlive) {
        printBoard(pBoard);

        printf("=====DASHBOARD=======\n");
        printf("Forward: %d\n", game.pActions->nForward);
        printf("Rotation: %d\n", game.pActions->nRotate);
        printf("Sense: %d\n", game.pActions->nSense);

        move = readKeyInSet(validMoves);

        system("cls");

        processMove(&game, move);

        if (move == 'q') {
            game.nIsAlive = 0;
        }
    }
}