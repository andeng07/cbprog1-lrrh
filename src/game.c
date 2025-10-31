#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "game.h"
#include "game_board.h"
#include "io_util.h"
#include "renderer.h"

#define GAME_WIDTH 125

void input_object(GameBoard *board, ObjectType type, Status status) {
    int x, y;
    int size = board->size;

    int isValid;

    do {
        x = input_in_range("\tx-coordinate", 1, size) - 1;
        y = input_in_range("\ty-coordinate", 1, size) - 1;

        isValid = get_object_at_pos(board, x, y)->type == EMPTY;

        if (!isValid) {
            printf("\tCoordinate (%d, %d) already taken. Please try again.\n", x + 1, y + 1);
        }
    } while (!isValid);

    GameObject obj = (GameObject){ type, UNDEFINED, status, x, y };

    place_object(board, &obj, x, y);
}

void place_multiple_objects(GameBoard *board, ObjectType type, int count, Status status) {
    for (int i = 0; i < count; i++) {
        printf("Enter %s #%d location:\n", get_type_name(type), i + 1);
        input_object(board, type, status);
    }
}

int process_move(Game *game, char move) {
    GameBoard *board = game->board;
    GameObject *player = game->player;
    PlayerActions *actions = game->actions;

    switch (move) {
        case 'w': case 's': {
            int forwardX, forwardY;
            get_forward_coordinate(player, &forwardX, &forwardY);

            if (is_valid_pos(board, forwardX, forwardY)) {
                GameObject *target = get_object_at_pos(board, forwardX, forwardY);
                if (move == 'w' && target->type == EMPTY) {
                    move_object(board, player, forwardX, forwardY);
                    actions->forward++;
                } else if (move == 's' && target != NULL) {
                    if (target->status == HIDDEN) {
                        target->status = VISIBLE;
                        actions->sense++;
                    }
                }
            }
            break;
        }
        case 'a': case 'd': {
            rotate(player);
            place_object(board, player, player->x, player->y);

            actions->rotate++;
            break;
        }
    }

    return 0;
}

void game_loop(GameBoard *board, GameObject *player) {
    Game game;

    game.board = board;
    game.player = player;

    game.actions = &(PlayerActions){ 0, 0, 0 };

    game.is_alive = 1;

    game.status = 0;

    while(game.is_alive) {
        print_board(board, GAME_WIDTH);

        printf("=====DASHBOARD=======\n");
        printf("Forward: %d\n", game.actions->forward);
        printf("Rotation: %d\n", game.actions->rotate);
        printf("Sense: %d\n", game.actions->sense);

        char move;
        int valid = 0;
        char validMoves[] = { 'w','a','s','d' };

        while (!valid) {
            move = getch();
            for (int i = 0; i < 4; i++)
                if (validMoves[i] == move) valid = 1;
        }

        process_move(&game, move);
        system("cls");
    }
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
    input_object(board, WOODSMAN, HIDDEN);

    printf("Enter Granny location:\n");
    input_object(board, GRANNY, HIDDEN);

    printf("\n");

    game_loop(board, &player);

    destroy_game_board(board);
}
