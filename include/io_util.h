#ifndef IO_UTIL_H
#define IO_UTIL_H

int input_in_range(char *prompt, int lower_bound, int upper_bound);

char input_in_set(char *prompt, char *valid_set);

char read_key_in_set(char *valid_set);

void print_center(char *toPrint, int width);

#endif // IO_UTIL_H