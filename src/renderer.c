#include "renderer.h"
#include <stdio.h>

void printBoard(GameBoard *pBoard) {
    int i, j;

    int size = pBoard->nSize;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            GameObject obj = pBoard->cells[i][j];
            char landmark = ' ';

            if (obj.status == HIDDEN) {
                landmark = '*';
            } else {
                landmark = getTypeMetadata(obj.type)->cLandmark;

                if (obj.type == LITTLE_RED_RIDING_HOOD) {
                    switch (obj.direction) {
                        case UP: landmark = '^'; break;
                        case DOWN: landmark = 'v'; break;
                        case LEFT: landmark = '<'; break;
                        case RIGHT: landmark = '>'; break;
                        default: landmark = '?'; break;
                    }
                }
            }
            printf("%c ", landmark);
        }
        printf("\n");
    }

}

void printTitle(void) {
    int i;

    char *frame[] = {
        "__| |______________________________________________________________________________________________________| |__",
        "__   ______________________________________________________________________________________________________   __",
        "  | |                                                                                                      | |  ",
        "  | |                                                                                                      | |  ",
        "  | |                                                                                                      | |  ",
        "  | |   _     _ _   _   _        ____          _   ____  _     _ _               _   _                 _   | |  ",
        "  | |  | |   (_) |_| |_| | ___  |  _ \\ ___  __| | |  _ \\(_) __| (_)_ __   __ _  | | | | ___   ___   __| |  | |  ",
        "  | |  | |   | | __| __| |/ _ \\ | |_) / _ \\/ _` | | |_) | |/ _` | | '_ \\ / _` | | |_| |/ _ \\ / _ \\ / _` |  | |  ",
        "  | |  | |___| | |_| |_| |  __/ |  _ <  __/ (_| | |  _ <| | (_| | | | | | (_| | |  _  | (_) | (_) | (_| |  | |  ",
        "  | |  |_____|_|\\__|\\__|_|\\___| |_| \\_\\___|\\__,_| |_| \\_\\_|\\__,_|_|_| |_|\\__, | |_| |_|\\___/ \\___/ \\__,_|  | |  ",
        "  | |                                                                    |___/                             | |  ",
        "  | |                                                                                                      | |  ",
        "  | |                                                                                                      | |  ",
        "__| |______________________________________________________________________________________________________| |__",
        "__   ______________________________________________________________________________________________________   __",
        "  | |                                                                                                      | |  ",
    };

    int lineCount = sizeof(frame) / sizeof(frame[0]);

    for (i = 0; i < lineCount; i++) {
        printf("%s\n", frame[i]);
    }
}