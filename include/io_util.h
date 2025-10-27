#ifndef IO_UTIL_H
#define IO_UTIL_H

int input_in_range(char *prompt, int lowerBound, int upperBound);

char input_in_set(char *prompt, char* valid);

void print_center(char *toPrint, int width);

#endif // IO_UTIL_H