#include "io_util.h"
#include <stdio.h>
#include <string.h>

int input_in_range(char *prompt, int lowerBound, int upperBound) {
    int value;

    while (1) {
        printf("%s: ", prompt);

        if (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (value < lowerBound || value > upperBound) {
            printf("Value must be between %d and %d.\n", lowerBound, upperBound);
            continue;
        }

        while (getchar() != '\n');
        return value;
    }
}

char input_in_set(char *prompt, char *valid) {
    int size = sizeof(valid) / sizeof(valid[0]);

    char value;
    int isValid;

    do {
        printf("%s: ", prompt);

        if (scanf(" %c", &value) != 1) {
            printf("Invalid input. Please enter a character.\n");
            while (getchar() != '\n');
            isValid = 0;
            continue;
        }

        isValid = 0;
        for (int i = 0; i < size; i++) {
            if (value == valid[i]) {
                isValid = 1;
                break;
            }
        }

        if (!isValid) {
            printf("Invalid option. Please try again.\n");
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
            return value;
        }
    } while (!isValid);

    return value;
}

void print_center(char *toPrint, int width) {
    int len = strlen(toPrint);
    int paddingLeft = (width - len) / 2;
    int paddingRight = width - (len + paddingLeft);

    printf("%*s%s%*s\n", paddingLeft, "", toPrint, paddingRight, "");
}