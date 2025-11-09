#include "renderer.h"
#include "io_util.h"
#include <stdlib.h>
#include <stdio.h>

void print_board(GameBoard *board) {
    int size = board->size;

    for (int i = 0; i < size; i++) {
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
            printf("%c ", landmark);
        }
        printf("\n");
    }

}

void print_title() {
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
        printf("%s\n", frame[i]);
    }
}