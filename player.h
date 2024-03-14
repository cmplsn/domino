//
// Created by Alessandro on 14/03/24.
//

#ifndef PROJECT_IAP_PLAYER_H
#define PROJECT_IAP_PLAYER_H
typedef struct Tile{
    char x;
    char y;
    char orientation;
}Tile;

Tile* assegna(int n);

void print_hand(Tile* hand,int n);

int choose_valid_n();

void switch_tile(Tile* tile);

bool valid_tile(Tile* deck, int size, Tile tile, int n);

Tile select_tile(Tile* deck, int size, int n);

char select_orientation();

#endif //PROJECT_IAP_PLAYER_H
