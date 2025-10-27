#include <stdlib.h>
#include "game_board.h"
#include "game_object.h"

GameBoard *create_game_board(int size) {
    GameBoard *board = malloc(sizeof(GameBoard));

    board->size = size;

    board->cells = malloc(size * sizeof(GameObject *));

    for (int i = 0; i < size; i++) {
        GameObject *row = malloc(size * sizeof(GameObject));

        for (int j = 0; j < size; j++) {
            GameObject empty = *empty_game_object(j, i, HIDDEN);
            row[j] = empty;
        }

        board->cells[i] = row;
    }

    return board;
}

void destroy_game_board(GameBoard* board) {
    free(board->cells);
    free(board);
}

void place_object(GameBoard *board, GameObject *obj, int x, int y) {
    GameObject *occupant = &board->cells[y][x];

    board->cells[y][x] = *obj;

    set_pos(obj, x, y);
}

void move_object(GameBoard *board, GameObject *object, int toX, int toY) {
    int fromX = object->x;
    int fromY = object->y;

    board->cells[fromY][fromX] = *empty_game_object(fromX, fromY, VISIBLE);

    set_pos(object, toX, toY);

    board->cells[toY][toX] = *object;
}

GameObject *get_object_at_pos(GameBoard *board, int x, int y) {
    int is_valid = is_valid_pos(board, x, y);

    if (!is_valid) return NULL;

    return &board->cells[y][x];
}

int is_valid_pos(GameBoard *board, int x, int y) {
    int size = board->size;

    if (x < 0 || x > size - 1 || y < 0 || y > size - 1) {
        return 0;
    }

    return 1;
}