#include "io_util.h"
#include <stdio.h>
#include <string.h>

int input_in_range(char *prompt, int lowerBound, int upperBound) {
    int value;
    int valid = 0;

    do {
        printf("%s: ", prompt);

        if (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
        } else if (value < lowerBound || value > upperBound) {
            printf("Value must be between %d and %d.\n", lowerBound, upperBound);
        } else {
            valid = 1;
        }
        
        while (getchar() != '\n');
    } while (!valid);

    return value;
}

char input_in_set(char *prompt, char *valid) {
    int size = strlen(valid) / sizeof(valid[0]);

    char value;
    int valid = 0;

    do {
        printf("%s: ", prompt);

        if (scanf(" %c", &value) != 1) {
            printf("Invalid input. Please enter a character.\n");
        } else {
            for (int i = 0; i < size; i++) {
                if (valid[i] == value) valid = 1;
            }

            if (!valid) printf("Invalid option. Please try again.");
        }

        while (getchar() != '\n');
    } while (!valid);

    return value;
}

void print_center(char *toPrint, int width) {
    int len = strlen(toPrint);
    int paddingLeft = (width - len) / 2;
    int paddingRight = width - (len + paddingLeft);

    printf("%*s%s%*s\n", paddingLeft, "", toPrint, paddingRight, "");
}