#ifndef RENDERER_H
#define RENDERER_H

#include "game.h"

/* Prints the current state of the game pBoard to the console.
 * Precondition: pBoard is not NULL.
 * @param pBoard Pointer to the GameBoard to render.
 * @param width The console width used for alignment or centering.
 */
void printBoard(GameBoard *pBoard);

/* Prints the game title or banner centered within the given width.
 * Precondition: none.
 * @param width The total width of the display area.
 */
void printTitle(void);
void printDialogue (void);
void renderDashboard(PlayerActions *actions, GameState *state);

#endif /* RENDERER_H */
