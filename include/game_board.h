#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "game_object.h"

/* Represents a square grid containing GameObject instances.
 * Each cell in the grid holds a pointer to a GameObject, stored in a
 * dynamically allocated 2D array.
 */
typedef struct GameBoard {
    int size;            // The width and height of the square board (8–15).
    GameObject **cells;  // 2D array of GameObject pointers representing the board cells.
} GameBoard;

/* Creates and initializes a new GameBoard instance.
 * Precondition: size must be between 8 and 15 (inclusive).
 * @param size The width and height of the game board.
 * @return Pointer to a newly allocated GameBoard instance, or NULL if allocation fails.
 */
GameBoard *create_game_board(int size);

/* Frees all memory associated with a GameBoard instance.
 * Precondition: board must not be NULL.
 * @param board Pointer to the GameBoard to destroy.
 * @return None.
 */
void destroy_game_board(GameBoard *board);

/* Places a GameObject at a specific position on the board.
 * If another object already exists at that position, it will be replaced.
 * Precondition: x and y must be within the board bounds (0 ≤ x < size, 0 ≤ y < size).
 * @param board Pointer to the target GameBoard.
 * @param obj Pointer to the GameObject to place.
 * @param x The X-coordinate (column index).
 * @param y The Y-coordinate (row index).
 * @return None.
 */
void place_object(GameBoard *board, GameObject *obj, int x, int y);

/* Moves a GameObject to a new position on the board.
 * Removes the object from its current position and places it at the target coordinates.
 * Any existing object at the destination will be replaced.
 * Precondition: board and object must not be NULL; to_x and to_y must be within bounds.
 * @param board Pointer to the GameBoard.
 * @param object Pointer to the GameObject to move.
 * @param to_x The destination X-coordinate.
 * @param to_y The destination Y-coordinate.
 * @return None.
 */
void move_object(GameBoard *board, GameObject *object, int to_x, int to_y);

/* Retrieves the GameObject located at a specific board position.
 * Precondition: x and y must be within bounds.
 * @param board Pointer to the GameBoard.
 * @param x The X-coordinate of the cell.
 * @param y The Y-coordinate of the cell.
 * @return Pointer to the GameObject at the given position, or NULL if the cell is empty.
 */
GameObject *get_object_at_pos(GameBoard *board, int x, int y);

/* Checks if a given position is within the bounds of the board.
 * Precondition: board must not be NULL.
 * @param board Pointer to the GameBoard.
 * @param x The X-coordinate to check.
 * @param y The Y-coordinate to check.
 * @return 1 if the position is valid; 0 otherwise.
 */
int is_valid_pos(GameBoard *board, int x, int y);

#endif // GAME_BOARD_H