//
// Created by Alessandro on 13/02/24.
//

#ifndef PROJECT_IAP_PLAYER_H
#define PROJECT_IAP_PLAYER_H

#include <time.h>
#include <stdbool.h>

typedef struct Tile{
    char x;
    char y;
    char orientation;
}Tile;

Tile* assegna(int n){
    Tile deck[24]={{'1','1'},{'1','2'},{'1','3'},{'1','4'},{'1','5'},{'1','6'},
                   {'2','2'},{'2','3'},{'2','4'},{'2','5'},{'2','6'},
                   {'3','3'},{'3','4'},{'3','5'},{'3','6'},
                   {'4','4'},{'4','5'},{'4','6'},
                   {'5','5'},{'5','6'},{'6','6'},
                   {'0','0'},{'+','1'},{'M','R'}};

    Tile* hand=(Tile*)malloc(n*sizeof(Tile));
    srand(time(NULL));

    for (int i=0; i<n;i++){
        int x=rand()%24;
        hand[i].x=deck[x].x;
        hand[i].y=deck[x].y;
    }
    return hand;
}

void print_hand(Tile* hand,int n){
    printf("tessere del giocatore: \n");
    for (int i = 0; i <n ; ++i) {
        printf("[%c%c] ",hand[i].x,hand[i].y);
    }
    printf("\n");
}

int choose_valid_n(){
    printf("scegliere numero tessere con cui giocare:\n");
    int n;
    int res=scanf("%d",&n);
    while(res!=1 || n<1 || n>256){
        printf("NON VALIDO. Inserisci input nel formato richiesto:\n");
        res= scanf("%d",&n);
    }
    printf("si è scelto di giocare con -- %d -- tessere\n",n);
    return n;
}

#endif //PROJECT_IAP_PLAYER_H
