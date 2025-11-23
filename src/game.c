#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "game.h"
#include "game_board.h"
#include "io_util.h"
#include "renderer.h"

void inputObject(GameBoard *pBoard, ObjectType type, Status status);
void inputMultipleObjects(GameBoard *pBoard, ObjectType type, int nCount, Status status);
int processMove(Game *pGame, char cMove);
void handleCollision(Game *pGame, GameObject *pPlayer, GameObject *pGameObject);
void gameLoop(GameBoard *pBoard, GameObject *pPlayer);

void run(void) {
    char cChoice, cDevModeChoice;
    int nBoardSize, nPitCount, nFlowerCount;

    char aScreenTitleChoices[4] = {'P', 'p', 'Q', 'q'};
    char aDevModeOptions[4] = { 'Y', 'y', 'N', 'n' };

    GameSettings gameSettings;
    GameBoard *pBoard;
    GameObject player = {LITTLE_RED_RIDING_HOOD, DOWN, VISIBLE, 0, 0};

    clearScreen();
    printTitle();

    cChoice = inputInSet("Press [P] to Play or [Q] to Quit", aScreenTitleChoices, 4);
    if (cChoice == 'Q' || cChoice == 'q') {
        printBoxedLine("Goodbye!");
        return;
    }

    cDevModeChoice = inputInSet("Continue with Developer Mode? [Y/N]", aDevModeOptions, 4);
    gameSettings.nDevMode = (cDevModeChoice == 'Y' || cDevModeChoice == 'y');

    // Initialize board
    nBoardSize = inputInRange("Enter board size", 8, 15);
    pBoard = createGameBoard(nBoardSize, gameSettings.nDevMode);
    pBoard->pPersistedObject = emptyGameObject(0, 0, VISIBLE);

    // Place player
    placeObject(pBoard, &player, 0, 0);

    // Map configuration
    nPitCount = inputInRange("Enter number of Pits in the map", 1, pBoard->nSize);
    inputMultipleObjects(pBoard, PIT, nPitCount, gameSettings.nDevMode);

    nFlowerCount = inputInRange("Enter number of Flowers in the map", 1, pBoard->nSize);
    inputMultipleObjects(pBoard, FLOWER, nFlowerCount, gameSettings.nDevMode);

    printf("Enter Bakeshop location:\n");
    inputObject(pBoard, BAKESHOP, gameSettings.nDevMode);

    printf("Enter Wolf location:\n");
    inputObject(pBoard, WOLF, gameSettings.nDevMode);

    printf("Enter Woodsman location:\n");
    inputObject(pBoard, WOODSMAN, gameSettings.nDevMode);

    printf("Enter Granny location:\n");
    inputObject(pBoard, GRANNY, gameSettings.nDevMode);

    clearScreen();
    printDialogue();

    // Start main game loop
    gameLoop(pBoard, &player);

    // Free memory
    destroyGameBoard(pBoard);

    printf("\n\n\n\n\n");
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
        if (!nIsValid) printBoxedLine("Coordinate already taken. Try again.");
    } while (!nIsValid);

    obj.type = type;
    obj.status = status;
    obj.nPosX = nPosX;
    obj.nPosY = nPosY;

    placeObject(pBoard, &obj, nPosX, nPosY);
}

void inputMultipleObjects(GameBoard *pBoard, ObjectType type, int nCount, Status status) {
    for (int i = 0; i < nCount; i++) {
        printf("Enter %s #%d location:\n", getTypeMetadata(type)->pName, i + 1);
        inputObject(pBoard, type, status);
    }
}

void gameLoop(GameBoard *pBoard, GameObject *pPlayer) {
    char move;
    char validMoves[10] = { 'w','a','s','d','q','W','A','S','D','Q' };

    Game game;
    GameState state = {1, 0, 0, 0}; 
    PlayerActions actions = {0, 0, 0};

    game.pBoard = pBoard;
    game.pPlayer = pPlayer;
    game.pGameState = &state;
    game.pActions = &actions;
    game.nStatus = 0;

    while (state.nIsAlive) {
        clearScreen();
        printBoard(pBoard);
        printf("\n\n");
        renderDashboard(&actions, &state);

        move = readKeyInSet(validMoves, 10);
        processMove(&game, move);

        if (move == 'q') {
            printBoxedLine("Game Over! Thank you for playing.");
            break;
        }
    }
}

int processMove(Game *pGame, char cMove) {
    GameBoard *board = pGame->pBoard;
    GameObject *player = pGame->pPlayer;
    PlayerActions *actions = pGame->pActions;

    int forwardX, forwardY;

    switch (cMove) {
        case 'w': case 'W':
            getForwardCoordinate(player, &forwardX, &forwardY);
            if (isValidPosition(board, forwardX, forwardY)) {
                GameObject *target = getObjectAtPosition(board, forwardX, forwardY);
                if (target != NULL && target->type != EMPTY) handleCollision(pGame, player, target);
                moveObject(board, player, forwardX, forwardY);
                actions->nForward++;
            }
            break;

        case 's': case 'S':
            getForwardCoordinate(player, &forwardX, &forwardY);
            if (isValidPosition(board, forwardX, forwardY)) {
                GameObject *target = getObjectAtPosition(board, forwardX, forwardY);
                if (target != NULL && target->status == HIDDEN) {
                    ObjectTypeMetadata *meta = getTypeMetadata(target->type);
                    target->status = VISIBLE;
                    printDialogueLine(meta ? meta->pSenseName : "You sensed something!", getTypeColor(target->type));
                    actions->nSense++;
                }
            }
            break;

        case 'a': case 'A':
            rotate(player, ROTATE_LEFT);
            actions->nRotate++;
            placeObject(board, player, player->nPosX, player->nPosY);
            break;

        case 'd': case 'D':
            rotate(player, ROTATE_RIGHT);
            actions->nRotate++;
            placeObject(board, player, player->nPosX, player->nPosY);
            break;
    }

    return 0;
}

void handleCollision(Game *pGame, GameObject *pPlayer, GameObject *pGameObject) {
    GameState *state = pGame->pGameState;

    switch (pGameObject->type) {
        case GRANNY:
            state->nIsAlive = 0;
            printCollisionDialogue(GRANNY, state);
            break;

        case PIT:
            state->nIsAlive = 0;
            printCollisionDialogue(PIT, state);
            break;

        case WOLF:
            if (state->nIsBreadPresent) {
                printCollisionDialogue(WOLF, state);
                state->nIsBreadPresent = 0;
            } else {
                state->nIsAlive = 0;
                printCollisionDialogue(WOLF, state);
            }
            break;

        case WOODSMAN:
            state->nIsWoodsmanPresent = 1;
            printCollisionDialogue(WOODSMAN, state);
            break;

        case BAKESHOP:
            state->nIsBreadPresent = 1;
            printCollisionDialogue(BAKESHOP, state);
            break;

        case FLOWER:
            state->nIsFlowerPresent = 1;
            printCollisionDialogue(FLOWER, state);
            break;

        default: break;
    }
}