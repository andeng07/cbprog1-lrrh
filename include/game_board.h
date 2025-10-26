#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "game_object.h"

typedef struct GameBoard {
    int size;
    GameObject **cells;
} GameBoard;

/*
 * Creates a GameBoard instance with the specified size.
 * 
 * @param size The width and height of the square game board.
 * @returns Pointer to a newly allocated GameBoard instance, or NULL on failure.
 */
GameBoard *create_game_board(int size);

/*
 * Deletes a GameBoard instance and frees all allocated memory.
 *
 * @param board Pointer to the GameBoard to be destroyed.
 */
void destroy_game_board(GameBoard* board);

/*
 * Places an object at a specific position on the game board.
 *
 * @param board Pointer to the GameBoard.
 * @param obj Pointer to the GameObject to place.
 * @param x X-coordinate of the target position.
 * @param y Y-coordinate of the target position.
 */
void place_object(GameBoard *board, GameObject *obj, int x, int y);

void move_object(GameBoard *board, int fromX, int fromY, int toX, int toY);

/*
 * Retrieves an object at a specific game board cell.
 *
 * @param board Pointer to the GameBoard.
 * @param x X-coordinate of the cell.
 * @param y Y-coordinate of the cell.
 * @returns Pointer to the GameObject at the specified position,
 *          or NULL if the cell is out of bounds.
 */
GameObject *get_object_at_pos(GameBoard *board, int x, int y);

int is_valid_pos(GameBoard *board, int x, int y);

#endif