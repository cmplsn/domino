//
// Created by Alessandro on 13/02/24.
//

#ifndef PROJECT_IAP_BOARD_H
#define PROJECT_IAP_BOARD_H

#include <stdbool.h>

typedef struct Matrix{
    int rows;
    int cols;
    char** matrix;
}Matrix;

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

Matrix newMatrix(){
    Matrix a;
    a.rows=2;
    a.cols=4;
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

char** add_rows(Matrix* board, int addrows){
    char** tmp=(char**) realloc(board->matrix,(board->rows+addrows)* sizeof(char*));
    if(tmp) {
        board->matrix=tmp;
        for (int i = 0; i < addrows; ++i) {
            board->matrix[board->rows + i] = (char *) malloc(board->cols * sizeof(char));
        }
    }
    board->rows+=addrows;
    return board->matrix;
}
char** add_cols( Matrix* board, int addcols){
    for (int i = 0; i < board->rows; ++i) {
        char *tmp= (char*)realloc(board->matrix[i], (board->cols+addcols)*sizeof(char*));
        if(tmp){
            board->matrix[i]=tmp;
        }
    }
    board->cols+=addcols;
    return board->matrix;
}


/*


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
}*/
#endif //PROJECT_IAP_BOARD_H
