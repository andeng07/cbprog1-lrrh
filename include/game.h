#ifndef GAME_H
#define GAME_H

#include "game_board.h"
#include "game_object.h"

typedef struct GameSettings {
    int dev_mode;
} GameSettings;

typedef struct PlayerActions {
    int forward;
    int rotate;
    int sense;
} PlayerActions;

typedef struct Game {
    GameBoard board;
    GameObject player;
    
    int is_alive;

    PlayerActions actions;

    int status; // flags
} Game;

void run();

#endif // GAME_H