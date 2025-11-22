#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "game_object.h"

/* Represents a square grid containing GameObject instances.
 * Each cell in the grid holds a pointer to a GameObject, stored in a
 * dynamically allocated 2D array.
 */
typedef struct GameBoard {
    int nSize;            /* The width and height of the square board (8–15). */
    GameObject **cells;   /* 2D array of GameObject pointers representing the board cells. */
    GameObject *pPersistedObject; 
} GameBoard;

/* Creates and initializes a new GameBoard instance.
 * Precondition: nSize must be between 8 and 15 (inclusive).
 * @param nSize The width and height of the game pBoard.
 * @param nDevMode The flag indicating whether developer mode is enabled
 * @return Pointer to a newly allocated GameBoard instance, or NULL if allocation fails.
 */
GameBoard *createGameBoard(int nSize, int nDevMode);

/* Frees all memory associated with a GameBoard instance.
 * Precondition: pBoard must not be NULL.
 * @param pBoard Pointer to the GameBoard to destroy.
 * @return None.
 */
void destroyGameBoard(GameBoard *pBoard);

/* Places a GameObject at a specific position on the pBoard.
 * If another object already exists at that position, it will be replaced.
 * Precondition: nPosX and nPosY must be within the pBoard bounds (0 ≤ nPosX < nSize, 0 ≤ nPosY < nSize).
 * @param pBoard Pointer to the target GameBoard.
 * @param pObj Pointer to the GameObject to place.
 * @param nPosX The X-coordinate (column index).
 * @param nPosY The Y-coordinate (row index).
 * @return None.
 */
void placeObject(GameBoard *pBoard, GameObject *pObj, int nPosX, int nPosY);

/* Moves a GameObject to a new position on the board.
 * Removes the object from its current position and places it at the target coordinates.
 * Any existing pObj at the destination will be replaced.
 * Precondition: pBoard and pObj must not be NULL; nDestX and nDestY must be within bounds.
 * @param pBoard Pointer to the GameBoard.
 * @param pObj Pointer to the GameObject to move.
 * @param nDestX The destination X-coordinate.
 * @param nDestY The destination Y-coordinate.
 * @return None.
 */
void moveObject(GameBoard *pBoard, GameObject *pObj, int nDestX, int nDestY);

/* Retrieves the GameObject located at a specific board position.
 * Precondition: nPosX and nPosY must be within bounds.
 * @param pBoard Pointer to the GameBoard.
 * @param nPosX The X-coordinate of the cell.
 * @param nPosY The Y-coordinate of the cell.
 * @return Pointer to the GameObject at the given position, or NULL if the cell is empty.
 */
GameObject *getObjectAtPosition(GameBoard *pBoard, int nPosX, int nPosY);

/* Checks if a given position is within the bounds of the pBoard.
 * Precondition: pBoard must not be NULL.
 * @param pBoard Pointer to the GameBoard.
 * @param nPosX The X-coordinate to check.
 * @param nPosY The Y-coordinate to check.
 * @return 1 if the position is valid; 0 otherwise.
 */
int isValidPosition(GameBoard *pBoard, int nPosX, int nPosY);

#endif /* GAME_BOARD_H */