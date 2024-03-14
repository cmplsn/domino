//
// Created by Alessandro on 14/03/24.
//
#include "player.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int choose_valid_n(void){
    printf("scegliere numero tessere con cui giocare:\n");
    int n;
    int res=scanf("%d",&n);
    while(res!=1 || n<1 || n>256){
        printf("NON VALIDO. Inserisci input nel formato richiesto:\n");
        res= scanf("%d",&n);
    }
    //printf("si è scelto di giocare con -- %d -- tessere\n",n);
    system("clear");
    return n;
}

void switch_tile(Tile* tile){
    char tmp=tile->x;
    tile->x=tile->y;
    tile->y=tmp;
}

bool valid_tile(Tile* deck, int size, Tile tile, int n){
    bool found=false;
    int i=0;
    if(size == n && ((tile.x=='M'&&tile.y=='R')||(tile.x=='R'&&tile.y=='M')
                     ||(tile.x=='+'&&tile.y=='1')||(tile.x=='1'&& tile.y =='+'))){
        printf("per usare [%c%c] deve essere presente almeno un'altra tessere sul tavolo di gioco \n", tile.x,tile.y);
    }else{
        while(found==false && i<size){
            if((deck[i].x==tile.x && deck[i].y==tile.y)||(deck[i].x==tile.y && deck[i].y == tile.x)){
                found=true;
                Tile tmp={deck[size-1].x,deck[size-1].y,' '};
                deck[size-1].x=deck[i].x;
                deck[size-1].y=deck[i].y;
                deck[i].x=tmp.x;
                deck[i].y=tmp.y;
            }
            i++;
        }

    }

    return found;
}

Tile select_tile(Tile* deck, int size, int n){
    printf("scegliere tessera da giocare:\n");
    char a,b;
    scanf(" %c%c",&a,&b);
    Tile res={a,b,' '};

    while(!valid_tile(deck,size,res,n)){
        printf("\nTESSERA NON VALIDA!\n\nscegliere tessera da giocare:\n");
        scanf(" %c%c",&a,&b);
        res.x=a;
        res.y=b;
    }
    system("clear");
    return res;
}

char select_orientation(void){
    printf("seleziona orientamento tessere: O/V\n");
    char x=' ';
    scanf(" %c",&x);
    while(x!='V' && x!='O'){
        printf("formato non valido, seleziona orientamente: O/V\n");
        scanf(" %c",&x);
    }
    return x;
}
