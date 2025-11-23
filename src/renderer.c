#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "renderer.h"
#include "io_util.h"
#include "game_board.h"

void setColor(int fg) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, fg);
}

void resetColor(void) {
    setColor(COLOR_DEFAULT);
}

void clearScreen(void) {
    system("cls");
}

void printBoxedLine(const char *msg) {
    int len = (int)strlen(msg);
    int padding = (SCREEN_WIDTH - 4 - len) / 2;
    if (padding < 0) padding = 0;

    printf("|");
    for (int i = 0; i < padding; i++) putchar(' ');
    printf("%s", msg);
    for (int i = 0; i < SCREEN_WIDTH - 4 - padding - len; i++) putchar(' ');
    printf("|\n");
}

void printDialogueLine(const char *msg, int color) {
    setColor(color);

    printf(" ");
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) putchar('-');
    printf(" \n");

    printBoxedLine(msg);

    printf(" ");
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) putchar('-');
    printf(" \n");

    resetColor();
    printf("Press any key to continue...");
    getch();

    printf("\033[F\033[F\033[F");
}

// ------------------------ Title ------------------------
void printTitle(void) {
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
        printCenter(SCREEN_WIDTH, frame[i]);
        putchar('\n');
    }
}

void printBoard(GameBoard *pBoard) {
    int size = pBoard->nSize;
    int totalWidth = size * 4 + 1;

    for (int row = 0; row < size; row++) {
        int padding = (SCREEN_WIDTH - totalWidth) / 2;
        if (padding < 0) padding = 0;
        for (int i = 0; i < padding; i++) putchar(' ');
        for (int col = 0; col < size; col++) printf("+---");
        printf("+\n");

        for (int i = 0; i < padding; i++) putchar(' ');
        for (int col = 0; col < size; col++) {
            GameObject obj = pBoard->cells[row][col];
            char ch = ' ';
            int color = getTypeColor(obj.type);

            if (obj.status == HIDDEN) {
                ch = '*';
                color = getTypeColor(EMPTY);
            }
            else {
                ch = getTypeMetadata(obj.type)->cLandmark;

                if (obj.type == LITTLE_RED_RIDING_HOOD) {
                    switch (obj.direction) {
                        case UP: ch = '^'; break;
                        case DOWN: ch = 'v'; break;
                        case LEFT: ch = '<'; break;
                        case RIGHT: ch = '>'; break;
                        default: ch = '?'; break;
                    }
                }
            }

            printf("| ");
            setColor(color);
            putchar(ch);
            resetColor();
            printf(" ");
        }
        printf("|\n");
    }

    int padding = (SCREEN_WIDTH - totalWidth) / 2;
    for (int i = 0; i < padding; i++) putchar(' ');
    for (int col = 0; col < size; col++) printf("+---");
    printf("+\n");
}


void renderDashboard(PlayerActions *actions, GameState *state) {
    printBoxedLine("=+=+=+=+=+=+=+=+=+=+=+= PLAYER DASHBOARD =+=+=+=+=+=+=+=+=+=+=+=");

    char buffer[120];
    snprintf(buffer, sizeof(buffer), "Forward Moves: %d | Rotations: %d | Sense Actions: %d",
             actions->nForward, actions->nRotate, actions->nSense);
    printBoxedLine(buffer);

    printBoxedLine("Inventory / Status:");
    if (state->nIsBreadPresent) { setColor(COLOR_BAKESHOP); printBoxedLine("Bread: Present"); resetColor(); }
    if (state->nIsFlowerPresent) { setColor(COLOR_FLOWER); printBoxedLine("Flower: Present"); resetColor(); }
    if (state->nIsWoodsmanPresent) { setColor(COLOR_WOODS); printBoxedLine("Woodsman: Present"); resetColor(); }
    putchar('\n');
}

void printDialogue(void) {
    printDialogueLine("Once upon a time, in a forest shrouded with mist, there was a sweet little girl named Little Red Riding Hood.", COLOR_ALERT);
    printDialogueLine("Today she planned to visit her Grandma, bringing freshly baked bread and beautiful flowers.", COLOR_BAKESHOP);
    printDialogueLine("Beware! The forest is full of peril: sly wolves lurk, and bottomless pits await the unwary.", COLOR_ALERT);
    printDialogueLine("LRRH whispers: 'I must be careful... I hope I get to Grandma safely!'", COLOR_PLAYER);
    printDialogueLine("Little Red Riding Hood steps into the forest, her red hood bright against the shadows...", COLOR_WOODS);
}

void printCollisionDialogue(ObjectType type, GameState *state) {
    switch (type) {
        case GRANNY:
            if (state->nIsWoodsmanPresent && state->nIsBreadPresent && state->nIsFlowerPresent) {
                printDialogueLine("Grandma greets you warmly! You did it!", COLOR_GRANNY);
                printDialogueLine("The forest dangers were no match for your courage.", COLOR_GRANNY);
                printDialogueLine("She hugs you tightly, smelling the fresh bread and flowers.", COLOR_GRANNY);
                printDialogueLine("The End. What a wonderful day!", COLOR_GRANNY);
            } else {
                printDialogueLine("Grandma looks at you sadly...", COLOR_GRANNY);
                printDialogueLine("You weren't able to gather all the items she expected.", COLOR_GRANNY);
                printDialogueLine("The forest was too harsh today, and fate wasn't kind.", COLOR_GRANNY);
                printDialogueLine("The End. Perhaps next time will be better.", COLOR_GRANNY);
            }
            break;

        case PIT:
            printDialogueLine("Oh no! You slipped into a bottomless pit!", COLOR_PIT);
            printDialogueLine("You scream as darkness swallows you...", COLOR_PIT);
            printDialogueLine("Game Over!", COLOR_PIT);
            break;

        case WOLF:
            if (state->nIsBreadPresent) {
                printDialogueLine("The cunning wolf pounces and snatches your bread!", COLOR_WOLF);
                printDialogueLine("LRRH: 'Nooo! My bread! I must find another loaf!'", COLOR_PLAYER);
            } else {
                printDialogueLine("The wolf lunges at you with ferocious eyes!", COLOR_WOLF);
                printDialogueLine("LRRH: 'I have nothing to distract him! I must run!'", COLOR_PLAYER);
                printDialogueLine("The wolf catches you! Game Over!", COLOR_WOLF);
            }
            break;

        case WOODSMAN:
            printDialogueLine("A friendly Woodsman appears!", COLOR_WOODS);
            printDialogueLine("He tips his hat: 'I'll guide you safely through these woods.'", COLOR_WOODS);
            break;

        case BAKESHOP:
            printDialogueLine("You arrive at the Bakeshop.", COLOR_BAKESHOP);
            printDialogueLine("The baker hands you a warm loaf: 'Here, this will keep you safe from hunger.'", COLOR_BAKESHOP);
            break;

        case FLOWER:
            printDialogueLine("You find a radiant flower among the forest undergrowth.", COLOR_FLOWER);
            printDialogueLine("LRRH: 'This will make Grandma so happy!'", COLOR_PLAYER);
            break;

        default: break;
    }
    resetColor();
}

int getTypeColor(ObjectType type) {
    int color;

    switch (type)
    {
        case LITTLE_RED_RIDING_HOOD: color = COLOR_PLAYER; break;
        case GRANNY: color = COLOR_GRANNY; break;
        case WOODSMAN: color = COLOR_WOODS; break;
        case WOLF: color = COLOR_WOLF; break;
        case BAKESHOP: color = COLOR_BAKESHOP; break;
        case FLOWER: color = COLOR_FLOWER; break;
        case PIT: color = COLOR_PIT; break;

        default: color = COLOR_DEFAULT; break;
    }

    return color;
}