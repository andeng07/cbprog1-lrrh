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

/* Holds flags that represents the state of the game. */
typedef struct GameState {
    int nIsAlive;           /* Flag indicating if the player is alive or not. */
    int nIsWoodsmanPresent; /* Flag indicating if the player has located woodsman or not */
    int nIsBreadPresent;    /* Flag indicating if the bread has been retrieved or not. */
    int nIsFlowerPresent;   /* Flag indicating if the flower has been retrieved or not. */
} GameState;

/* Represents the main game state. */
typedef struct Game {
    GameBoard *pBoard;        /* Pointer to the active game pBoard. */
    GameObject *pPlayer;      /* Pointer to the player-controlled object. */
    GameState *pGameState;    /* Pointer to the game's current state */
    PlayerActions *pActions;  /* Pointer to the player's action counters. */
    int nStatus;              /* Game nStatus flags (implementation-defined). */
} Game;

/* Starts and manages the main game loop. */
void run(void);

#endif /* GAME_H */
