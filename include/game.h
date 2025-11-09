#ifndef GAME_H
#define GAME_H

#include "game_board.h"
#include "game_object.h"

/* Holds runtime configuration options for the game. */
typedef struct GameSettings {
    int nDevMode;  /* When non-zero, enables developer or debug mode features. */
} GameSettings;

/* Tracks how many times the player has performed each action. */
typedef struct PlayerActions {
    int nForward;  /* Number of times the player moved forward. */
    int nRotate;   /* Number of times the player rotated. */
    int nSense;    /* Number of times the player used a sensing action. */
} PlayerActions;

/* Represents the main game state */
typedef struct Game {
    GameBoard *pBoard;        /* Pointer to the active game pBoard. */
    GameObject *pPlayer;      /* Pointer to the player-controlled object. */
    int nIsAlive;            /* Player state flag (1 = alive, 0 = dead). */
    PlayerActions *pActions;  /* Pointer to the player's action counters. */
    int nStatus;              /* Game nStatus flags (implementation-defined). */
} Game;

/* Starts and manages the main game loop. */
void run(void);

#endif /* GAME_H */
