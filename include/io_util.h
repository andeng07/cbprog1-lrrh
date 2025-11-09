#ifndef IO_UTIL_H
#define IO_UTIL_H

/* Prompts the user for an integer input within a specific range.
 * Precondition: pPrompt is not NULL.
 * @param pPrompt The message displayed to the user before reading input.
 * @param nLowerBound The minimum acceptable integer value.
 * @param nUpperBound The maximum acceptable integer value.
 * @return The validated integer input from the user.
 */
int inputInRange(char *pPrompt, int nLowerBound, int nUpperBound);

/* Prompts the user to enter a single character from a set of valid options.
 * Precondition: pPrompt and pValidSet are not NULL.
 * @param pPrompt The message displayed before reading input.
 * @param pValidSet A null-terminated string of allowed characters.
 * @return The validated character entered by the user.
 */
char inputInSet(char *pPrompt, char *pValidSet);

/* Reads a single character from input without prompting.
 * Precondition: pValidSet is not NULL.
 * @param pValidSet A null-terminated string of allowed characters.
 * @return The validated character entered by the user.
 */
char readKeyInSet(char *pValidSet);

/* Prints text centered within a given nWidth.
 * Precondition: pToPrint is not NULL.
 * @param pToPrint The string to print.
 * @param nWidth The total nWidth of the output area (e.g., terminal nWidth).
 */
void printCenter(char *pToPrint, int nWidth);

#endif /* IO_UTIL_H */