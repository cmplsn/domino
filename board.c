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
//todo: funzione che viene richiamata quando viene inserita sulla board una tessera [+1]
void plus_one(Matrix *board){
        for (int i = 0; i < board->rows; ++i) {
            for (int j = 0; j < board->cols; ++j) {
                switch (board->matrix[i][j]) {
                    default:
                        break;
                    case '1' ... '5':
                        board->matrix[i][j]++;
                        break;
                    case '6':
                        board->matrix[i][j] = '1';
                        break;
                }
            }
        }
}

void move_board(Matrix *board, int mode){
    //todo: in mode==1 ricopio tutto spostato di 4 chae se necessario per creare spazio per una nuova tessera orizzontale
    if(mode==1){
        for (int i = 0; i <board->rows; ++i) {
            for (int j = board->cols-1; j >=4; --j) {
                board->matrix[i][j]=board->matrix[i][j-4];
            }
            for (int j = 0; j < 4; ++j) {
                board->matrix[i][j]=' ';
            }
        }
    }else{

    }
    print_board(board);
}

bool insert_right(Matrix *board, Tile tile) {
    bool ok=false;
    int i=0;
    while(board->matrix[0][i]!= ' ' && i<board->cols){
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
        plus_one(board);
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
    while(board->matrix[0][i] != ' ' && i<board->cols) {
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
            plus_one(board);
            ok=true;
        }else if((tile.x=='M'&& tile.y=='R') ||board->matrix[0][1]==tile.y || board->matrix[0][1]=='0'||tile.y=='0'){
            move_board(board,1);
            board->matrix[0][0]='[';
            board->matrix[0][3]=']';
            if(tile.x == 'M' && tile.y == 'R'){
                board->matrix[0][1]=board->matrix[0][6];
                board->matrix[0][2]=board->matrix[0][5];
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
            || (deck[j].x=='+' && deck[j].y=='1')){
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
    system("clear");
     printf("Score: %d\n", get_score(board));
     print_board(board);
     print_hand(deck,decksize);
}

void find_blank(Matrix *board, int* row, int* col){
    while(*row< board->rows){
        while(*col<board->cols){
            if(board->matrix[*row][*col]==' '){
                return;
            }else{
                if(*col+1 > board->cols){
                   row++;
                   *col=0;
                }else{
                    *col = *col+1;
                }
            }
        }
    }

}

bool check_blank(Matrix *board, int i, int j, char orientation){
    bool ok=true;
    //todo: se uno dei char che la tessera nuova dovrà occupare in board è diverso da  ' ' oppure se lo spazio
    // necessario "sfora" i limiti del tavolo di gioco, ok viene impostato
    if(orientation=='O'){
        int k=0;
        while(k<4 &&ok){
            if(j+k <= board->cols-1 && board->matrix[i][j+k] == ' '){
                k++;
            }else{
                ok=false;
            }
        }
    }else{
        if(i>=board->rows-1){
            ok=false;
        }else {
            for (int k = 0; (k < 2) && ok; ++k) {
                for (int l = 0; l < 2; ++l) {
                    if (board->matrix[i + k][j + l] != ' ' || i + k >= board->rows || j + l >= board->cols) {
                        ok = false;
                    }
                }
            }
        }
    }
    return ok;
}

bool insert_right_2D(Matrix *board, Tile tile){
    bool placed=false;

    //todo:Qualsiasi sia il verso della tessera [+1] aggiunta quando la partita è in modalità 2D aumenta tutta la board
    // di 1. Se board è vuota non fa nulla perchè utilizzo di [+1] viene bloccato già prima di entrare nella insert

    if(tile.x=='+' && tile.y=='1'){
        plus_one(board);
        placed=true;
    }else{
        int i=0;int j=0;

        while(!placed && i<board->rows && j<board->cols){
            find_blank(board, &i, &j);

            if(tile.orientation=='O'){

                char *h = tile_to_horizontal(tile);

                if (i==0 && j==0 ){

                    //todo: se find_blank trova la board completamente vuota e la tile è diversa da [MR]
                    if(!(tile.x=='M' && tile.y=='R')){
                        for (int k = 0; k < 4; ++k) {
                            board->matrix[i][j+k]=h[k];
                        }
                        placed = true;
                    }
                }else{
                    if(check_blank(board,i,j,'O')){

                        //todo: caso in cui la tessera sia [00] oppure sia presente sul tavolo {0, 0} o 0]
                        if(tile.x=='0' ||(board->matrix[i][j-2]=='{' && board->matrix[i][j-1]=='0')
                        || (board->matrix[i][j-2]=='0'&&(board->matrix[i][j-1]=='}' || board->matrix[i][j-1]==']'))){

                            for (int k = 0; k < 4; ++k) {
                                board->matrix[i][j+k]=h[k];
                            }
                            placed=true;

                        }else if((tile.x=='M'&&tile.y=='R') ){

                            //todo: caso in cui la tessera sia [MR], suddiviso in altri tre casi: tessere posta in
                            // orizzontale, pezzo di tessera in verticale {x e pezzo tessera in verticale y}

                            board->matrix[i][j] = '[';
                            board->matrix[i][j+3] = ']';

                            if(board->matrix[i][j-1]==']'){
                                board->matrix[i][j+1] = board->matrix[i][j-2];
                                board->matrix[i][j+2] = board->matrix[i][j-3];
                                placed=true;
                            }else if(board->matrix[i][j-1]=='}'){
                                board->matrix[i][j+1] = board->matrix[i][j-2];
                                board->matrix[i][j+2] = board->matrix[i][j-2];
                                placed=true;
                            }else if (board->matrix[i][j-2]=='{'){
                                board->matrix[i][j+1] = board->matrix[i][j-1];
                                board->matrix[i][j+2] = board->matrix[i][j-1];
                                placed=true;
                            }

                            //todo: caso in cui ho una tessera numerata diversa da [MR], [+1] o [00] devo controllare:
                            // -se su tavolo ho y} oppure y] che tile.x==y e che se board->matrix[i][j+4] != ' '
                            // che tile.y==board->matrix[i][j+4]
                        }else if((board->matrix[i][j-1]==']'||board->matrix[i][j-1]=='}')&&board->matrix[i][j-2]==tile.x
                        || board->matrix[i][j-1]==tile.x && board->matrix[i][j-2]=='{'){
                            if(board->matrix[i][j+4]==' ' || board->matrix[i][j+4]==tile.y){
                                for (int k = 0; k < 4; ++k) {
                                    board->matrix[i][j+k]=h[k];
                                }
                                placed = true;
                            }

                        }else if(board->matrix[i][j-2]=='{' && board->matrix[i][j-1]==tile.x){
                            if(board->matrix[i][j+4]==' ' || board->matrix[i][j+4]==tile.y){
                                for (int k = 0; k < 4; ++k) {
                                    board->matrix[i][j+k]=h[k];
                                }
                                placed=true;
                            }


                        }

                    }
                    if(!placed){
                        //todo se non entro in nessuno dei casi precedentemente elencati per aggiungere una tessera in
                        // orizzontale faccio ripartire la ricerca di find_blank. se aggiungendo 1 a j sforo le colonne
                        // riparto da i++ e j=0 quindi vado a ricercare su riga successiva.
                        if (j+1>=board->cols-1){
                            i++;
                            j=0;
                        }else{
                            j++;
                        }
                    }
                }
                free(h);

            }else if (tile.orientation == 'V'){
                if(tile.x=='M' && tile.y=='R'){
                    return false;
                }else{
                    char** ver= tile_to_vertical(tile);

                    if(i==0 && j==0){
                        for (int k = 0; k <2 ; ++k) {
                            for (int l = 0; l < 2; ++l) {
                                board->matrix[i+k][j+l]=ver[k][l];
                            }
                        }
                        placed=true;
                    }else{

                        //todo:controllo se sia disponibile a partire da matrix[i][j] una posizione 2x2 per aggiungere la
                        // tessera in verticale. Va controllato anche che la tessere venga posizionata vicino ad un
                        // altra tessera con un numero valido. e che se di fianco è presente un'altra tessera in
                        // verticale, tutti i numeri che vengono affiancati siano uguali.


                        if (check_blank(board,i,j,'V')){

                            //todo: sto aggiungendo su board in presenza 0], 0} oppure {0 oppure la tessera che io
                            // voglio aggiungere è [00]
                            if (((board->matrix[i][j-1]=='}'||board->matrix[i][j-1]==']') && board->matrix[i][j-2]=='0')
                            ||(board->matrix[i][j-2]=='{' && board->matrix[i][j-1]=='0') || (tile.x=='0'&&tile.y=='0')){
                                for (int k = 0; k < 2; ++k) {
                                    for (int l = 0; l< 2; ++l) {
                                        board->matrix[i+k][j+l]=ver[k][l];
                                    }
                                }
                                placed=true;
                            }else{
                                if (((board->matrix[i][j-1]==']' || board->matrix[i][j-1]=='}')&&
                                board->matrix[i][j-2]==tile.x) || (board->matrix[i][j-2]=='{'&&board->matrix[i][j-1]==tile.x)){

                                    if (((board->matrix[i+1][j-2]==tile.y || board->matrix[i+1][j-1]==tile.y||
                                    board->matrix[i+1][j-1]==' ') && board->matrix[i+1][j+2]==' ' || board->matrix[i+1][j+2]==tile.y) &&
                                    (board->matrix[i][j+2]==' ' || board->matrix[i][j+2]==tile.x || j+2==board->cols-1)){

                                        for (int k = 0; k < 2 ; ++k) {
                                            for (int l = 0; l < 2 ; ++l) {
                                                board->matrix[i+k][j+l]=ver[k][l];
                                            }
                                        }

                                        placed=true;

                                    }
                                }
                            }
                        }
                        if(!placed){
                            if (j+1>=board->cols-1){
                                i++;
                                j=0;
                            }else{
                                j++;
                            }
                        }
                    }


                    for (int k = 0; k < 2; ++k) {
                        free(ver[k]);
                    }
                    free(ver);
                }


            }
        }
    }
   return placed;
}


bool insert_left_2D(Matrix *board, Tile tile){
    bool placed=false;

    if(tile.x=='+' && tile.y=='1'){
        plus_one(board);
        placed=true;
    }else{
        if(tile.orientation=='O'){
            char *hor= tile_to_horizontal(tile);
            if (tile.x=='0'&&tile.y=='0'){
                move_board(board,1);
                for (int k = 0; k < 4; ++k) {
                    board->matrix[0][k]=hor[k];
                }
                placed=true;
            }
            free(hor);
        }else{
            char** ver = tile_to_vertical(tile);

            for (int i = 0; i < 2; ++i) {
                free(ver[i]);
            }
            free(ver);
        }


    }
    return placed;
}
