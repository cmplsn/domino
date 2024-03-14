//
// Created by Alessandro on 14/03/24.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

typedef struct Matrix{
    int rows;
    int cols;
    char** matrix;
}Matrix;

typedef struct Tile{
    char x;
    char y;
    char orientation;
}Tile;

int select_mode(){
    printf("seleziona modalità di gioco\n1: Domino Lineare\n2: Domino 2D\n");
    int x=-1;
    while(x!=1 && x!=2){
        scanf(" %d", &x);
    }
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
    if((tile[1]=='M' && tile[2]=='R') && i>3){  //tessere Mirror può essere utilizzata solo se è presente almeno
        // un altra tessera
        tile[1]=board->matrix[0][i-2];
        tile[2]=board->matrix[0][i-3];
        for (int j = 0; j < 4; ++j) {
            board->matrix[0][i+j]=tile[j];
        }
    }else if((tile[1]=='+' && tile[2]=='1') && i>3){
        for (int j = 0; j < i; ++j) {
            switch(board->matrix[0][j]){
                case '0' ... '5':
                    board->matrix[0][j]++;
                    break;
                case '6':
                    board->matrix[0][j]='1';
                    break;
            }
        }
    }else if(i==0 ||(board->matrix[0][i-2]==tile[1] || board->matrix[0][i-2]=='0'||(tile[1]=='0'&& tile[2]=='0')) ){
        for (int j = 0; j < 4; ++j) {
            board->matrix[0][i+j]=tile[j];
        }
    }
}
void insert_left(Matrix* board, char* tile){

}

// PARTE DI PLAYER
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
    return res;
}

char select_orientation(){
    printf("seleziona orientamento tessere: O/V\n");
    char x=' ';
    scanf(" %c",&x);
    while(x!='V' && x!='O'){
        printf("formato non valido, seleziona orientamente: O/V\n");
        scanf(" %c",&x);
    }
    return x;
}