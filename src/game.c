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
void handleCollission(Game *pGame, GameObject *pPlayer, GameObject *pGameObject);
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

    cChoice = inputInSet("Press [P] to Play or [Q] to Quit", aScreenTitleChoices, 4);

    if (cChoice == 'Q' || cChoice == 'q') {
        printf("Goodbye!\n");
        return;
    }

    /* ask player if they want to proceed in developer mode */
    cDevModeChoice = inputInSet("Continue with Developer Mode? [Y/N]", aDevModeOptions, 4);

    if (cDevModeChoice == 'Y' || cDevModeChoice == 'y') {
        gameSettings.nDevMode = 1;
    } else {
        gameSettings.nDevMode = 0;
    }

    /* initialize pBoard */
    nBoardSize = inputInRange("Enter pBoard nSize", 8, 15);
    pBoard = createGameBoard(nBoardSize, gameSettings.nDevMode);
    pBoard->pPersistedObject = emptyGameObject(0, 0, VISIBLE);

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
        case 'w': case 's': { /* Forward or Sense */
            int forwardX, forwardY;
            getForwardCoordinate(player, &forwardX, &forwardY);

            if (isValidPosition(board, forwardX, forwardY)) {
                GameObject *target = getObjectAtPosition(board, forwardX, forwardY);
                if (cMove == 'w') { /* Forward */
                    if (target != NULL) {
                        handleCollission(pGame, pGame->pPlayer, target);
                    }
                    moveObject(board, player, forwardX, forwardY);
                    actions->nForward++;
                } else if (cMove == 's' && target != NULL) { /* Sense */
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
        case 'a': case 'd': { /* Rotate */
            RotationDirection direction = cMove == 'a' ? ROTATE_LEFT : ROTATE_RIGHT;

            rotate(player, direction);
            placeObject(board, player, player->nPosX, player->nPosY);

            actions->nRotate++;
            break;
        }
    }

    return 0;
}

/*
    Precodition:   - pGame, pPlayer, and pGameObject are NOT NULL
                   - pGameObject->type is NOT EMPTY
*/
void handleCollission(Game *pGame, GameObject *pPlayer, GameObject *pGameObject) {
    GameState *pGameState = pGame->pGameState;

    if (getTypeMetadata(pGameObject->type)->nIsCollissionPersistent) {

    }
    
    switch (pGameObject->type) {
        case GRANNY: {  
            // TODO: is bread, flower, and woodsman present? YES: WIN, NO: LOSE
            pGameState->nIsAlive = pGameState->nIsWoodsmanPresent && pGameState->nIsBreadPresent && pGameState->nIsFlowerPresent;

            break;
        }
        case PIT: {
            // TODO: die basically 
            pGameState->nIsAlive = 0;

            break;
        }
        case WOLF: {
            // TODO: gets eaten ONLY IF LRRH doesn't have a bread
            pGameState->nIsAlive = pGameState->nIsBreadPresent;

            if (pGameState->nIsBreadPresent) {
                pGameState->nIsBreadPresent = 0;
            }

            break;
        }
        case WOODSMAN: {
            // TODO: set woodsman flag to true
            pGameState->nIsWoodsmanPresent = 1;

            break;
        }
        case BAKESHOP: {
            // TODO: set bread flag to true
            pGameState->nIsBreadPresent = 1;

            break;
        }
        case FLOWER: {
            // TODO: set flower flag to true
            pGameState->nIsFlowerPresent = 1;

            break;
        }

        default: return;
    }
}

void gameLoop(GameBoard *pBoard, GameObject *pPlayer) {
    char move;

    char validMoves[5] = { 'w','a','s','d','q' };

    Game game;
    GameState state = {1, 0, 0, 0};
    PlayerActions actions = {0, 0, 0};

    game.pBoard = pBoard;
    game.pPlayer = pPlayer;

    game.nStatus = 0;

    game.pGameState = &state;
    game.pActions = &actions;

    while(game.pGameState->nIsAlive) {
        printBoard(pBoard);

        printf("=====DASHBOARD=======\n");
        printf("Forward: %d\n", game.pActions->nForward);
        printf("Rotation: %d\n", game.pActions->nRotate);
        printf("Sense: %d\n", game.pActions->nSense);

        move = readKeyInSet(validMoves, 5);

        system("cls");

        processMove(&game, move);

        if (move == 'q') {
            game.pGameState->nIsAlive = 0;
        }
    }
}