//
// Created by Alessandro on 14/03/24.
//

#ifndef PROJECT_IAP_BOARD_H
#define PROJECT_IAP_BOARD_H
#include "player.h"

typedef struct Matrix{
    int rows;
    int cols;
    char** matrix;
}Matrix;

Matrix newMatrix(int rows, int cols);

void free_board(Matrix* board);

int select_mode(void);

char** initboard(int rows, int cols);

void print_board(Matrix* board);

char** tile_to_vertical(Tile t);

char* tile_to_horizontal(Tile t);

char select_pos(void);

bool insert_right(Matrix *board, char *tile);

bool insert_left(Matrix* board, char* tile);
int get_score(Matrix* board);

#endif //PROJECT_IAP_BOARD_H
