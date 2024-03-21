//
// Created by Alessandro on 14/03/24.
//

#ifndef PROJECT_IAP_PLAYER_H
#define PROJECT_IAP_PLAYER_H
#include <stdbool.h>

typedef struct Tile{
    char x;
    char y;
    char orientation;
}Tile;

Tile* assegna(int n);

void print_hand(Tile* hand,int n);

int choose_valid_n(void);

void switch_tile(Tile* tile);

bool valid_tile(Tile* deck, int size, Tile tile, int n);

Tile select_tile(Tile* deck, int size, int n,int mode);

char select_orientation(void);

Tile select_tile_2D(Tile* deck, int deck_size, int n);

#endif //PROJECT_IAP_PLAYER_H
