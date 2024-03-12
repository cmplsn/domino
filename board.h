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

/*char** add_rows(Matrix* board, int addrows){
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
}*/

char select_pos(){
    printf("posizionare a Destra ( D ) o Sinistra ( S )?:\n");
    char x;
    scanf(" %c",&x);
    while (!(x=='D' || x=='S')){
        printf("Formato Errato, selezionare Destra (D) o Sinistra ( S ):\n");
        scanf(" %c",&x);
    }
    return x;
}

void insert_right(Matrix* board, char* tile,int n){
    int i=0;
    while(board->matrix[0][i]!=' '){
        i++;
    }
    if(i==0 ||board->matrix[0][i-2]==tile[1] || board->matrix[0][i-2]=='0' || (tile[1]=='0' && tile[2]=='0')){
        for (int j = 0; j <4 ; ++j) {
            board->matrix[0][i+j]=tile[j];
        }
    }else if(i>3 && tile[1]=='M' && tile[2]=='R'){
        tile[1]=board->matrix[0][i-2];
        tile[2]=board->matrix[0][i-3];

        for (int j = 0; j <4 ; ++j) {
            board->matrix[0][i+j]=tile[j];
        }
    }else if(tile[1]=='+' && tile[2]=='1'){
        for (int j = 0; j < i; ++j) {
            switch (board->matrix[0][j]) {
                case 1 ... 5:
                    board->matrix[0][j]++;
                    break;
                case 6:
                    board->matrix[0][j]=1;
                    break;
            }
        }
    }else{
        printf("Mossa non valida\n");
        exit(1);
    }
}
void insert_left(Matrix* board, char* tile){

}

#endif //PROJECT_IAP_BOARD_H
