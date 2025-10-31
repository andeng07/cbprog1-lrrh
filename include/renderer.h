#ifndef RENDERER_H
#define RENDERER_H

#include "game.h"

/* Prints the current state of the game board to the console.
 * Precondition: board is not NULL.
 * @param board Pointer to the GameBoard to render.
 * @param width The console width used for alignment or centering.
 */
void print_board(GameBoard *board, int width);

/* Prints the game title or banner centered within the given width.
 * Precondition: none.
 * @param width The total width of the display area.
 */
void print_title(int width);

#endif // RENDERER_H
