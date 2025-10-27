#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "game.h"
#include "game_board.h"
#include "io_util.h"
#include "renderer.h"

#define GAME_WIDTH 125

void place_multiple_objects(GameBoard *board, ObjectType type, int count, Status status) {
    for (int i = 0; i < count; i++) {
        printf("Enter %s #%d location:\n", get_type_name(type), i + 1);
        input_object(board, type, status);
    }
}

void input_object(GameBoard *board, ObjectType type, Status status) {
    int x, y;
    int size = board->size;

    do {
        x = input_in_range("\tx-coordinate", 1, size) - 1;
        y = input_in_range("\ty-coordinate", 1, size) - 1;
    } while (get_object_at_pos(board, x, y)->type != EMPTY);

    GameObject obj;
    obj.type = type;
    obj.direction = UNDEFINED;
    obj.status = status;
    obj.x = x;
    obj.y = y;

    place_object(board, &obj, x, y);
}

int process_move(GameBoard *board, GameObject *object, char move) {
    switch (move) {
        case 'w': case 's': {
            int forwardX, forwardY;
            get_forward_coordinate(object, &forwardX, &forwardY);

            if (is_valid_pos(board, forwardX, forwardY)) {
                GameObject *target = get_object_at_pos(board, forwardX, forwardY);
                if (move == 'w' && target->type == EMPTY) {
                    move_object(board, object, forwardX, forwardY);
                } else if (move == 's' && target != NULL) {
                    target->status = VISIBLE;
                }
            }
            break;
        }
        case 'a':
            rotate(object, ROTATE_LEFT);
            place_object(board, object, object->x, object->y);
            break;
        case 'd':
            rotate(object, ROTATE_RIGHT);
            place_object(board, object, object->x, object->y);
            break;
    }
    return 0;
}

void game_loop(GameBoard *board, GameObject *player) {
    int is_alive = 1;

    do {
        print_board(board, GAME_WIDTH);

        char move;
        int valid = 0;
        char validMoves[] = { 'w','a','s','d' };

        while (!valid) {
            move = getch();
            for (int i = 0; i < 4; i++)
                if (validMoves[i] == move) valid = 1;
        }

        process_move(board, player, move);
        system("cls");
    } while (is_alive);
}

void run() {
    print_title(GAME_WIDTH);

    char choice = input_in_set("Press [P] to Play or [Q] to Quit: ", (char[]){'P','p','Q','q'});

    if (choice == 'Q' || choice == 'q') {
        printf("Goodbye!\n");
        return;
    }

    int board_size = input_in_range("Enter board size", 8, 15);
    GameBoard *board = create_game_board(board_size);

    GameObject player = {LITTLE_RED_RIDING_HOOD, DOWN, VISIBLE, 0, 0};
    place_object(board, &player, 0, 0);

    int pits = input_in_range("Enter number of Pits in the map", 1, 10);
    place_multiple_objects(board, PIT, pits, HIDDEN);

    int flowers = input_in_range("Enter number of Flowers in the map", 1, 10);
    place_multiple_objects(board, FLOWER, flowers, HIDDEN);

    printf("Enter Wolf location:\n");
    input_object(board, WOLF, HIDDEN);

    printf("Enter Woodsman location:\n");
     input_object(board, WOODSMAN, VISIBLE);

    printf("Enter Granny location:\n");
    input_object(board, GRANNY, VISIBLE);

    printf("\n");

    game_loop(board, &player);

    destroy_game_board(board);
}
