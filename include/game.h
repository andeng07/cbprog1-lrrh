#ifndef GAME_H
#define GAME_H

#include "game_board.h"
#include "game_object.h"

/* Holds runtime configuration options for the game. */
typedef struct GameSettings {
    int nDevMode;  /* When non-zero, enables developer or debug mode features. */
} GameSettings;

/* Tracks how many times the pPlayer has performed each action. */
typedef struct PlayerActions {
    int nForward;  /* Number of times the pPlayer moved forward. */
    int nRotate;   /* Number of times the pPlayer rotated. */
    int nSense;    /* Number of times the pPlayer used a sensing action. */
} PlayerActions;

/* Represents the main game state, including the pBoard, pPlayer, and session nStatus. */
typedef struct Game {
    GameBoard *pBoard;        /* Pointer to the active game pBoard. */
    GameObject *pPlayer;      /* Pointer to the pPlayer-controlled object. */
    int nIsAlive;            /* Player state flag (1 = alive, 0 = dead). */
    PlayerActions *pActions;  /* Pointer to the pPlayer's action counters. */
    int nStatus;              /* Game nStatus flags (implementation-defined). */
} Game;

/* Starts and manages the main game loop. */
void run(void);

#endif /* GAME_H */
