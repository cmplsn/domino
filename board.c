//
// Created by Alessandro on 14/03/24.
//
#include <stdlib.h>
#include <stdio.h>
#include "board.h"

int select_mode(void){
    printf("seleziona modalità di gioco\n1: Domino Lineare\n2: Domino 2D\n");
    int x=-1;
    while(x!=1 && x!=2){
        scanf(" %d", &x);
    }
    system("clear");
    return x;
}

char** initboard(int rows, int cols){
    char** m=(char**) malloc(rows* sizeof(char*));
    for (int i = 0; i < rows; i++) {
        m[i]= (char*)malloc(cols* sizeof(char));
    }
    for (int i = 0; i <rows ; ++i) {
        for (int j = 0; j < cols; ++j) {
            m[i][j]=' ';
        }
    }
    return m;
}

void print_board(Matrix* board){
    for (int i = 0; i < board->rows; ++i) {
        for (int j = 0; j < board->cols; ++j) {
            printf("%c",board->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

char** tile_to_vertical(Tile t){
    char** tile= (char**)malloc(2*sizeof(char*));
    for (int i = 0; i < 2; ++i) {
        tile[i]=(char*) malloc(2* sizeof(char));
    }
    tile[0][0]='{';
    tile[0][1]=t.x;
    tile[1][0]=t.y;
    tile[1][1]='}';
    return tile;
}

char* tile_to_horizontal(Tile t){
    char* tile=(char*) malloc(4*sizeof(char));
    tile[0]='[';
    tile[1]=t.x;
    tile[2]=t.y;
    tile[3]=']';
    return tile;
}

Matrix newMatrix(int rows, int cols){
    Matrix a;
    a.rows=rows;
    a.cols=cols;
    a.matrix=initboard(a.rows,a.cols);
    return a;
}

void free_board(Matrix* board){
    if (board->rows>0){
        for (int i = 0; i <board->rows ; ++i) {
            free(board->matrix[i]);
        }
        free(board->matrix);
    }
}

char select_pos(void){
    printf("posizionare a Destra ( D ) o Sinistra ( S )?:\n");
    char x;
    scanf(" %c",&x);
    while (!(x=='D' || x=='S')){
        printf("Formato Errato, selezionare Destra (D) o Sinistra ( S ):\n");
        scanf(" %c",&x);
    }
    return x;
}

bool insert_right(Matrix *board, Tile tile) {
    bool ok=false;
    int i=0;
    while(board->matrix[0][i]!= ' '){
        i++;
    }
    if((tile.x=='M' && tile.y=='R') && i>3){ //tessere Mirror può essere utilizzata solo se è presente almeno
                                             // un altra tessera
        board->matrix[0][i]='[';
        board->matrix[0][i+1]=board->matrix[0][i-2];
        board->matrix[0][i+2]=board->matrix[0][i-3];
        board->matrix[0][i+3]=']';
        ok=true;
    }else if((tile.x=='+' && tile.y=='1') && i>3){
        for (int j = 0; j < i; ++j) {
            switch(board->matrix[0][j]){
                default:
                    break;
                case '1' ... '5':
                    board->matrix[0][j]++;
                    break;
                case '6':
                    board->matrix[0][j]='1';
                    break;
            }
        }
        ok=true;
    }else if(i==0 ||(board->matrix[0][i-2]==tile.x || board->matrix[0][i-2]=='0'||(tile.x=='0'&& tile.y=='0')) ){
        board->matrix[0][i]='[';
        board->matrix[0][i+1]=tile.x;
        board->matrix[0][i+2]=tile.y;
        board->matrix[0][i+3]=']';
        ok=true;
    }
    system("clear");
    return ok;
}

bool insert_left(Matrix* board, Tile tile){
    bool ok=false;
    int i=0;
    while(board->matrix[0][i] != ' ') {
        i++;
    }
    if(i==0 && !((tile.x == 'M' && tile.y == 'R')||(tile.x == '+' && tile.y == '1'))){
        board->matrix[0][0]='[';
        board->matrix[0][1]=tile.x;
        board->matrix[0][2]=tile.y;
        board->matrix[0][3]=']';
        ok=true;
    }else{
        if(tile.x == '+' && tile.y == '1'){
            for (int j = 0; j < i; ++j) {
                switch (board->matrix[0][j]) {
                    default:
                        break;
                    case '1' ... '5':
                        board->matrix[0][j]++;
                        break;
                    case '6':
                        board->matrix[0][j]='1';
                        break;
                }
            }
            ok=true;
        }else if((tile.x=='M'&& tile.y=='R') ||board->matrix[0][1]==tile.y || board->matrix[0][1]=='0'||tile.y=='0'){
            for (int j = i-1; j >= 0; --j) {
                board->matrix[0][j+4]=board->matrix[0][j];
            }
            for (int j = 0; j < 4; ++j) {
                board->matrix[0][j]=' ';
            }
            board->matrix[0][0]='[';
            board->matrix[0][3]=']';
            if(tile.x == 'M' && tile.y == 'R'){
                board->matrix[0][1]=board->matrix[0][i+2];
                board->matrix[0][2]=board->matrix[0][i+1];
            }else{
                board->matrix[0][1]=tile.x;
                board->matrix[0][2]=tile.y;
            }
            ok=true;
        }
    }

    return ok;
}

int get_score(Matrix* board){
    int sum=0;
    int char_to_int;
    for (int i = 0; i < board->rows; ++i) {
        for (int j = 0; j < board->cols; ++j) {
            switch (board->matrix[i][j]) {
                default:
                    break;
                case '0' ... '6':
                    char_to_int=board->matrix[i][j]-'0';
                    sum+=char_to_int;
            }
        }
    }
    return sum;
}

bool available_moves_linear(Matrix* board, Tile* deck,int deck_size, int n){
    bool found=false;
    if(deck_size==n){
        found=true;
    }else {
        int i=0;
        int j=0;
        while(board->matrix[0][i]!=' '){
            i++;
        }
        while(!found && j<deck_size){
            if((deck[j].x=='0'&& deck[j].y=='0')
            || (deck[j].x=='M' && deck[j].y=='R')
            || (deck[j].x=='+' && deck[j].y=='1')) {
                found=true;
            }else if(board->matrix[0][i-2]=='0' || board->matrix[0][1]=='0'){
                found=true;
            }else if(deck[j].x==board->matrix[0][i-2]||deck[j].x==board->matrix[0][1]||
                deck[j].y==board->matrix[0][i-2] ||deck[j].y==board->matrix[0][1]){
                found=true;
            }else{
                j++;
            }
        }
    }
    return found;
}


void end_game(Matrix* board){
    system("clear");
    print_board(board);
    printf("Non hai più mosse disponibili. Punteggio Finale: %d\n", get_score(board));
}

 void print_screen(Matrix* board, Tile* deck, int decksize){
     printf("Score: %d\n", get_score(board));
     print_board(board);
     print_hand(deck,decksize);
}

