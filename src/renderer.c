#include "renderer.h"
#include "io_util.h"
#include <stdlib.h>

void print_board(GameBoard *board, int width) {
    int size = board->size;
    int rowLength = size * 2 + 1;

    for (int i = 0; i < size; i++) {
        char* row = malloc(rowLength * sizeof(char));
        int index = 0;

        for (int j = 0; j < size; j++) {
            GameObject obj = board->cells[i][j];
            char landmark = ' ';

            if (obj.status == HIDDEN) {
                landmark = '*';
            } else {
                switch (obj.type) {
                    case LITTLE_RED_RIDING_HOOD:
                        switch (obj.direction) {
                            case UP: landmark = '^'; break;
                            case DOWN: landmark = 'v'; break;
                            case LEFT: landmark = '<'; break;
                            case RIGHT: landmark = '>'; break;
                            default: landmark = '?'; break;
                        }
                        break;
                    case GRANNY: landmark = 'G'; break;
                    case PIT: landmark = 'P'; break;
                    case WOLF: landmark = 'R'; break;
                    case WOODSMAN: landmark = 'W'; break;
                    case BAKESHOP: landmark = 'B'; break;
                    case FLOWER: landmark = 'F'; break;
                    case EMPTY: landmark = ' '; break;
                }
            }

            row[index++] = landmark;
            row[index++] = ' ';
        }

        row[index] = '\0';
        print_center(row, width);
        free(row);
    }
}

void print_title(int width) {
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

    for (int i = 0; i < lineCount; i++) {
        print_center(frame[i], width);
    }
}