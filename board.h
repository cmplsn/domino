//
// Created by Alessandro on 13/02/24.
//

#ifndef PROJECT_IAP_BOARD_H
#define PROJECT_IAP_BOARD_H

#include <stdbool.h>

typedef struct Matrix{
    int rows;
    int cols;
    int** matrix;
}Matrix;

int** initboard(int rows, int cols){
    int** m=(int**) malloc(rows* sizeof(int*));
    for (int i = 0; i < rows; i++) {
        m[i]= (int*)malloc(cols* sizeof(int));
    }
    return m;
}

Matrix newMatrix(){
    Matrix a;
    a.cols=2;
    a.rows=2;
    a.matrix=initboard(a.rows,a.cols);
    return a;
}


int switch_tessera(int x){
    int res=x/10;
    res += (x%10)*10;
    return res;
}

int valid_tessera(int* deck,int deck_size,int x){   //todo:  il giocatore sceglie una tessera da giocare (inserisce
                                                    // in input) ed una volta scelta, valid_tessera controlla
                                                    // se l'input corrisponde ad una delle tessere presenti
                                                    // nel suo mazzo.
    int a= switch_tessera(x);
    int i=0;
    while(i<deck_size ){
        if(deck[i]==x || deck[i]==a){
            return 1;
        }else{
            i++;
        }
    }
    return 0;
}
void print_board(Matrix board){
    printf("  ");
    for (int j = 0; j < board.cols; ++j) {
        printf("%d ",j+1);
    }
    printf("\n");

    for (int i = 0; i <board.rows ; ++i) {
        printf("%d ",i+1);
        for (int j = 0; j < board.cols; j=j+2) {
            if(board.matrix[i][j]!=0) {
                printf("[%d %d] ", board.matrix[i][j],board.matrix[i][j+1]);
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
}
void free_board(int** matrix,int rows){
    if (rows>0){
        for (int i = 0; i <rows ; ++i) {
            free(matrix[i]);
        }
        free(matrix);
    }
}
void addRow(int** matrix, int rows, int cols){

}

void addCol(int** matrix, int rows, int cols){

}

char choose_orientation(int tile){
    printf("utilizzare in orizzontale o verticale? O/V:\n");
    char c; scanf(" %c",&c);
    return c;
}

void place_tile(Matrix board, char orientation, int tile){

}

int choose_tile(int* deck, int n){
    mostra_tessere(deck,n);
    int tile;
    bool found=false;
    while(found==false){
        printf("scegli quale tessera utilizzare:\n");
        scanf("%d",&tile);
        if(!valid_tessera(deck,n,tile)) {
            printf("tessera non valida. rinserire tessere con cui si desidera giocare:\n");
            scanf("%d", &tile);
        }else{
            found=1;
        }
    }
    found=false;
    int i=0;
    int tile_rev= switch_tessera(tile);
    while(!found){
        if(tile==deck[i] || tile_rev==deck[i]){
            int tmp=deck[n-1];
            deck[n-1]=deck[i];
            deck[i]=tmp;
            found=1;
        }else{
            i++;
        }
    }
    return tile;
}


char choose_position(){
    int found=0;
    char c;
    while(!found){
        printf("Posizionare la pedina a destra o a sinistra?: D/S\n");
        scanf("%c", &c);

        if(!(c=='D' || c=='S')){
            printf("formato non corretto\n");
        }else{
            found=1;
        }
    }
    return c;
}

void place_orizzontale(int tile, Matrix board){

}

void place_verticale(int tile, int** matrix){

}

void addLeft(){
    //TODO: se pedina è utilizzata in verticale:

    //TODO: se pedina è utilizzata in orizzontale:
}

void addRight(){
    //TODO: se pedina è utilizzata in verticale:

    //TODO: se pedina è utilizzata in orizzontale:
}
#endif //PROJECT_IAP_BOARD_H
