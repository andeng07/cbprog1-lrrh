#ifndef GAME_H
#define GAME_H

#include "game_board.h"
#include "game_object.h"

/* Holds runtime configuration options for the game. */
typedef struct GameSettings {
    int dev_mode;  // When non-zero, enables developer or debug mode features.
} GameSettings;

/* Tracks how many times the player has performed each action. */
typedef struct PlayerActions {
    int forward;  // Number of times the player moved forward.
    int rotate;   // Number of times the player rotated.
    int sense;    // Number of times the player used a sensing action.
} PlayerActions;

/* Represents the main game state, including the board, player, and session status. */
typedef struct Game {
    GameBoard *board;        // Pointer to the active game board.
    GameObject *player;      // Pointer to the player-controlled object.
    int is_alive;            // Player state flag (1 = alive, 0 = dead).
    PlayerActions *actions;  // Pointer to the player's action counters.
    int status;              // Game status flags (implementation-defined).
} Game;

/* Starts and manages the main game loop. */
void run(void);

#endif // GAME_H
