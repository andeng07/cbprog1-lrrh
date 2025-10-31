#include "io_util.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>

int input_in_range(char *prompt, int lower_bound, int upper_bound) {
    int value;
    int is_valid = 0;

    do {
        printf("%s: ", prompt);

        if (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
        } else if (value < lower_bound || value > upper_bound) {
            printf("Value must be between %d and %d.\n", lower_bound, upper_bound);
        } else {
            is_valid = 1;
        }
        
        while (getchar() != '\n');
    } while (!is_valid);

    return value;
}

char input_in_set(char *prompt, char *valid_set) {
    int size = strlen(valid_set);

    char value;
    int is_valid = 0;

    do {
        printf("%s: ", prompt);

        if (scanf(" %c", &value) != 1) {
            printf("Invalid input. Please enter a character.\n");
        } else {
            for (int i = 0; i < size; i++) {
                if (valid_set[i] == value) is_valid = 1;
            }

            if (!is_valid) printf("Invalid option. Please try again.");
        }

        while (getchar() != '\n');
    } while (!is_valid);

    return value;
}

char read_key_in_set(char *valid_set) {
    int size = strlen(valid_set);

    char value;
    int is_valid = 0;

    do {
        value = getch();

        // perform a linear search
        for (int i = 0; i < size; i++) {
            if (value == valid_set[i]) is_valid = 1;
        }
    } while (!is_valid);

    return value; 
}

void print_center(char *to_print, int width) {
    int len = strlen(to_print);

    int paddingLeft = (width - len) / 2;
    int paddingRight = width - (len + paddingLeft);

    printf("%*s%s%*s\n", paddingLeft, "", to_print, paddingRight, "");
}