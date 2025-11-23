#ifndef RENDERER_H
#define RENDERER_H

#include "game.h"

#define CELL_HEIGHT 3
#define CELL_WIDTH 3

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 120

#define BOX_HEIGHT 5

#define COLOR_DEFAULT 7
#define COLOR_PLAYER 12
#define COLOR_GRANNY 13
#define COLOR_WOODS 10
#define COLOR_WOLF 4
#define COLOR_BAKESHOP 14
#define COLOR_FLOWER 11
#define COLOR_ALERT 6
#define COLOR_PIT 8

#define COLOR_BORDER 8

/* Sets the console foreground color.
 * Precondition: fg is a valid color code.
 * @param fg The foreground color.
 */
void setColor(int fg);

/* Resets the console text color to the default.
 * Precondition: none.
 */
void resetColor(void);

/* Clears the console screen.
 * Precondition: none.
 */
void clearScreen(void);

/* Prints a dialogue line in the specified color.
 * Precondition: msg is not NULL.
 * @param msg The message to print.
 * @param color The color used to print the message.
 */
void printDialogueLine(const char *msg, int color);

/* Prints a single line inside a decorative box.
 * Precondition: msg is not NULL.
 * @param msg The message to print.
 */
void printBoxedLine(const char *msg);

/* Prints the current state of the game board.
 * Precondition: pBoard is not NULL.
 * @param pBoard Pointer to the GameBoard to render.
 */
void printBoard(GameBoard *pBoard);

/* Prints the game title.
 * Precondition: none.
 */
void printTitle(void);

/* Prints all dialogue content managed by the dialogue system.
 * Precondition: none.
 */
void printDialogue(void);

/* Renders the dashboard showing player actions and game state.
 * Precondition: actions and state are not NULL.
 * @param actions Pointer to PlayerActions.
 * @param state Pointer to GameState.
 */
void renderDashboard(PlayerActions *actions, GameState *state);

/* Prints collision dialogue based on the object type encountered.
 * Precondition: state is not NULL.
 * @param type The object type collided with.
 * @param state Pointer to GameState.
 */
void printCollisionDialogue(ObjectType type, GameState *state);

/* Returns the color associated with the given object type.
 * Precondition: type is valid.
 * @param type The object type.
 * @return The color used to represent the type.
 */
int getTypeColor(ObjectType type);

#endif /* RENDERER_H */
