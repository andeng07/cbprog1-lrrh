#ifndef IO_UTIL_H
#define IO_UTIL_H

/* Prompts the user for an integer input within a specific range.
 * Precondition: prompt is not NULL.
 * @param prompt The message displayed to the user before reading input.
 * @param lower_bound The minimum acceptable integer value.
 * @param upper_bound The maximum acceptable integer value.
 * @return The validated integer input from the user.
 */
int input_in_range(char *prompt, int lower_bound, int upper_bound);

/* Prompts the user to enter a single character from a set of valid options.
 * Precondition: prompt and valid_set are not NULL.
 * @param prompt The message displayed before reading input.
 * @param valid_set A null-terminated string of allowed characters.
 * @return The validated character entered by the user.
 */
char input_in_set(char *prompt, char *valid_set);

/* Reads a single character from input without prompting.
 * Precondition: valid_set is not NULL.
 * @param valid_set A null-terminated string of allowed characters.
 * @return The validated character entered by the user.
 */
char read_key_in_set(char *valid_set);

/* Prints text centered within a given width.
 * Precondition: to_print is not NULL.
 * @param to_print The string to print.
 * @param width The total width of the output area (e.g., terminal width).
 */
void print_center(char *to_print, int width);

#endif // IO_UTIL_H