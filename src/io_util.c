#include "io_util.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdarg.h>

int inputInRange(char *pPrompt, int nLowerBound, int nUpperBound) {
    int value;
    int is_valid = 0;

    do {
        printf("%s (%d-%d): ", pPrompt, nLowerBound, nUpperBound);

        if (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
        } else if (value < nLowerBound || value > nUpperBound) {
            printf("Value must be between %d and %d.\n", nLowerBound, nUpperBound);
        } else {
            is_valid = 1;
        }
        
        while (getchar() != '\n');
    } while (!is_valid);

    return value;
}

char inputInSet(char *pPrompt, char *pValidSet, int nSetSize) {
    int i;
    char value;
    int is_valid = 0;

    do {
        printf("%s: ", pPrompt);

        if (scanf(" %c", &value) != 1) {
            printf("Invalid input. Please enter a character.\n");
        } else {
            for (i = 0; i < nSetSize; i++) {
                if (pValidSet[i] == value) is_valid = 1;
            }

            if (!is_valid) printf("Invalid option. Please try again.");
        }

        while (getchar() != '\n');
    } while (!is_valid);

    return value;
}

char readKeyInSet(char *pValidSet, int nSetSize) {
    int i;

    char value;
    int is_valid = 0;

    do {
        value = getch();

        /* perform a linear search */
        for (i = 0; i < nSetSize; i++) {
            if (value == pValidSet[i]) is_valid = 1;
        }
    } while (!is_valid);

    return value; 
}

void printCenter(int nWidth, char *pToPrint, ...) {
    char buffer[1024]; // actual string to output

    int len, left, right;

    va_list args;
    va_start(args, pToPrint);
    vsnprintf(buffer, sizeof(buffer), pToPrint, args);
    va_end(args);

    len = strlen(buffer);
    left = (nWidth - len) / 2;
    if (left < 0) left = 0;
    right = nWidth - len - left;
    if (right < 0) right = 0;

    printf("%*s%s%*s", left, "", buffer, right, "");
}