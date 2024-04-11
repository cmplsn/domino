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

bool insert_right(Matrix *board, Tile tile);

bool insert_left(Matrix* board, Tile tile);

bool insert_left_2D(Matrix* board, Tile tile);

bool insert_right_2D(Matrix* board, Tile tile);

int get_score(Matrix* board);

bool available_moves_linear(Matrix* board, Tile* deck,int deck_size, int n);

void end_game(Matrix* board);

void print_screen(Matrix* board, Tile* deck, int decksize);

void find_blank(Matrix *board, int *row, int *col);

void find_blank_left(Matrix *board, int *row, int *col);

bool check_blank(Matrix *board, int i, int j, char orientation);

bool check_blank_left(Matrix *board, int i, int j, char orientation);

bool available_moves_2D(Matrix* board, Tile* deck, int deck_size, int n);

#endif //PROJECT_IAP_BOARD_H
