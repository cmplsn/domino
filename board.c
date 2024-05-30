//
// Created by Alessandro on 14/03/24.
//
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include <unistd.h>

/*!
 * select_mode():
 *
 * nessun parametro e tipo di ritorno int
 *
 * Viene chiesto al giocatore di dare in input da tastiera o 1(Domino Lineare) o 2 (Domino 2D). variabile int x impostata
 * inizialmente a -1 e viene eseguito un ciclo while all'interno del quale eseguendo scanf viene assegnato ad x il valore
 * ricevuto in input da tastiera.
 * Fino a quando x non avrà uno dei due valori previsti (1/2), viene richiesto il rinserimento da tastiera dell'input.
 * Per esperienza di gioco più pulita prima del return viene eseguita una system("clear") per liberare lo schermo del terminale
 * prima dell'azione successiva.
 * */
int select_mode(void){
    printf("seleziona modalità di gioco\n1: Domino Lineare\n2: Domino 2D\n");
    int x=-1;
    while(x!=1 && x!=2){
        scanf(" %d", &x);
    }
    system("clear");
    return x;
}

/*!
 * init_board(int rows, int cols)
 *
 * tipo di ritorno: char** -> all'interno della struct Matrix utilizzata per il tavolo di gioco, viene salavato il campo
 * char** board e ad inizio partità il campo viene solamente dichiarato, una volta selezionato il numero di tessere, board
 * viene ridimensionata in base al numero di tessere nella mano del giocatore.
 *
 * parametri: int rows, int cols.
 *
 * - Domino Lineare: per le partite in questa modalità in numero di righe sarà sempre pari ad 1, le tessere vengono
 * utilizzate solo in orizzontale
 *
 *
 * */
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
            printf("%c",board->m[i][j]);
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
    a.m=initboard(a.rows,a.cols);
    return a;
}

void free_board(Matrix* board){
    if (board->rows>0){
        for (int i = 0; i <board->rows ; ++i) {
            free(board->m[i]);
        }
        free(board->m);
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
            switch (board->m[i][j]) {
                default:
                    break;
                case '1' ... '5':
                    board->m[i][j]++;
                    break;
                case '6':
                    board->m[i][j] = '1';
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
                board->m[i][j]=board->m[i][j-4];
            }
            for (int j = 0; j < 4; ++j) {
                board->m[i][j]=' ';
            }
        }
    }else{
        for (int i = 0; i < board->rows; ++i) {
            for (int j = board->cols-1; j >=2 ; --j) {
                board->m[i][j]=board->m[i][j-2];
            }
            for (int j = 0; j < 2; ++j) {
                board->m[i][j]=' ';
            }
        }

    }
}

bool insert_right(Matrix *board, Tile tile) {
    bool ok=false;
    int i=0;
    while(board->m[0][i]!= ' ' && i<board->cols){
        i++;
    }
    if((tile.x=='M' && tile.y=='R') && i>3){ //tessere Mirror può essere utilizzata solo se è presente almeno
        // un altra tessera
        board->m[0][i]='[';
        board->m[0][i+1]=board->m[0][i-2];
        board->m[0][i+2]=board->m[0][i-3];
        board->m[0][i+3]=']';
        ok=true;
    }else if((tile.x=='+' && tile.y=='1') && i>3){
        plus_one(board);
        ok=true;
    }else if(i==0 ||(board->m[0][i-2]==tile.x || board->m[0][i-2]=='0'||(tile.x=='0'&& tile.y=='0')) ){
        board->m[0][i]='[';
        board->m[0][i+1]=tile.x;
        board->m[0][i+2]=tile.y;
        board->m[0][i+3]=']';
        ok=true;
    }
    //system("clear");
    return ok;
}

bool insert_left(Matrix* board, Tile tile){
    bool ok=false;
    int i=0;
    while(board->m[0][i] != ' ' && i<board->cols) {
        i++;
    }
    if(i==0 && !((tile.x == 'M' && tile.y == 'R')||(tile.x == '+' && tile.y == '1'))){
        board->m[0][0]='[';
        board->m[0][1]=tile.x;
        board->m[0][2]=tile.y;
        board->m[0][3]=']';
        ok=true;
    }else{
        if(tile.x == '+' && tile.y == '1'){
            plus_one(board);
            ok=true;
        }else if((tile.x=='M'&& tile.y=='R') ||board->m[0][1]==tile.y || board->m[0][1]=='0'||tile.y=='0'){
            move_board(board,1);
            board->m[0][0]='[';
            board->m[0][3]=']';
            if(tile.x == 'M' && tile.y == 'R'){
                board->m[0][1]=board->m[0][6];
                board->m[0][2]=board->m[0][5];
            }else{
                board->m[0][1]=tile.x;
                board->m[0][2]=tile.y;
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
            switch (board->m[i][j]) {
                default:
                    break;
                case '0' ... '6':
                    char_to_int=board->m[i][j]-'0';
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
        while(board->m[0][i]!=' '){
            i++;
        }
        while(!found && j<deck_size){
            if((deck[j].x=='0'&& deck[j].y=='0')
               || (deck[j].x=='M' && deck[j].y=='R')
               || (deck[j].x=='+' && deck[j].y=='1')){
                found=true;
            }else if(board->m[0][i-2]=='0' || board->m[0][1]=='0'){
                found=true;
            }else if(deck[j].x==board->m[0][i-2]||deck[j].x==board->m[0][1]||
                     deck[j].y==board->m[0][i-2] ||deck[j].y==board->m[0][1]){
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
    while(*row <= board->rows-1){
        while(*col<board->cols){
            if(*row==0 && *col==0 && first_empty(board)){
                return;
            }else if(board->m[*row][*col]!=' ' && board->m[*row][*col+1]==' '){
                *col=*col+1;
                return;
            }else{
                if(*col+1 >= board->cols){
                    if(*row+1<=board->rows-1){
                        *row=*row+1;
                        *col=0;
                    }else{
                        *col=board->cols;
                        *row=board->rows;
                    }
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
            if(j+k <= board->cols-1 && board->m[i][j+k] == ' '){
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
                    if (board->m[i + k][j + l] != ' ' || i + k >= board->rows || j + l >= board->cols) {
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


                if (i==0 && j==0 && first_empty(board) ){

                    //todo: se find_blank trova la board completamente vuota e la tile è diversa da [MR]
                    if( !(tile.x=='M' && tile.y=='R')){
                        for (int k = 0; k < 4; ++k) {
                            board->m[i][k]=h[k];
                        }
                        placed = true;
                    }else{

                    }
                }else{
                    if(check_blank(board,i,j,'O')){

                        //todo: caso in cui la tessera sia [00] oppure sia presente sul tavolo {0, 0} o 0]
                        if(tile.x=='0' ||(board->m[i][j-2]=='{' && board->m[i][j-1]=='0') ||
                           (board->m[i][j-2]=='0'&&(board->m[i][j-1]=='}' || board->m[i][j-1]==']'))){

                            for (int k = 0; k < 4; ++k) {
                                board->m[i][j+k]=h[k];
                            }
                            placed=true;

                        }else if((tile.x=='M'&&tile.y=='R') ){

                            //todo: caso in cui la tessera sia [MR], suddiviso in altri tre casi: tessere posta in
                            // orizzontale, pezzo di tessera in verticale {x e pezzo tessera in verticale y}

                            board->m[i][j] = '[';
                            board->m[i][j+3] = ']';

                            if(board->m[i][j-1]==']'){
                                board->m[i][j+1] = board->m[i][j-2];
                                board->m[i][j+2] = board->m[i][j-3];
                                placed=true;
                            }else if(board->m[i][j-1]=='}'){
                                board->m[i][j+1] = board->m[i][j-2];
                                board->m[i][j+2] = board->m[i][j-2];
                                placed=true;
                            }else if (board->m[i][j-2]=='{'){
                                board->m[i][j+1] = board->m[i][j-1];
                                board->m[i][j+2] = board->m[i][j-1];
                                placed=true;
                            }

                            //todo: caso in cui ho una tessera numerata diversa da [MR], [+1] o [00] devo controllare:
                            // -se su tavolo ho y} oppure y] che tile.x==y e che se board->m[i][j+4] != ' '
                            // che tile.y==board->m[i][j+4]
                        }else if((board->m[i][j-1]==']'||board->m[i][j-1]=='}')&&board->m[i][j-2]==tile.x ||
                                 board->m[i][j-1]==tile.x && board->m[i][j-2]=='{'){

                            if(board->m[i][j+4]==' ' || board->m[i][j+4]==tile.y){
                                for (int k = 0; k < 4; ++k) {
                                    board->m[i][j+k]=h[k];
                                }
                                placed = true;
                            }

                        }else if(board->m[i][j-2]=='{' && board->m[i][j-1]==tile.x){
                            if(board->m[i][j+4]==' ' || board->m[i][j+4]==tile.y){
                                for (int k = 0; k < 4; ++k) {
                                    board->m[i][j+k]=h[k];
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

                    if(i==0 && j==0 && first_empty(board) ){

                        for (int k = 0; k <2 ; ++k) {
                            for (int l = 0; l < 2; ++l) {
                                board->m[i+k][j+l]=ver[k][l];
                            }
                        }
                        placed=true;

                    }else{

                        //todo:controllo se sia disponibile a partire da m[i][j] una posizione 2x2 per aggiungere la
                        // tessera in verticale. Va controllato anche che la tessere venga posizionata vicino ad un
                        // altra tessera con un numero valido. e che se di fianco è presente un'altra tessera in
                        // verticale, tutti i numeri che vengono affiancati siano uguali.


                        if (check_blank(board,i,j,'V')){

                            //todo: sto aggiungendo su board in presenza 0], 0} oppure {0 oppure la tessera che io
                            // voglio aggiungere è [00]
                            if (((board->m[i][j-1]=='}'||board->m[i][j-1]==']') && board->m[i][j-2]=='0')
                            ||(board->m[i][j-2]=='{' && board->m[i][j-1]=='0') || (tile.x=='0'&&tile.y=='0')){

                                for (int k = 0; k < 2; ++k) {
                                    for (int l = 0; l< 2; ++l) {
                                        board->m[i+k][j+l]=ver[k][l];
                                    }
                                }

                                placed=true;

                            }else{
                                if (((board->m[i][j-1]==']' || board->m[i][j-1]=='}')&&
                                board->m[i][j-2]==tile.x) || (board->m[i][j-2]=='{'&&board->m[i][j-1]==tile.x)){

                                    if (((board->m[i+1][j-2]==tile.y || board->m[i+1][j-1]==tile.y||
                                    board->m[i+1][j-1]==' ') && board->m[i+1][j+2]==' ' || board->m[i+1][j+2]==tile.y)
                                    && (board->m[i][j+2]==' ' || board->m[i][j+2]==tile.x || j+2==board->cols-1)){

                                        for (int k = 0; k < 2 ; ++k) {
                                            for (int l = 0; l < 2 ; ++l) {
                                                board->m[i+k][j+l]=ver[k][l];
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

bool first_empty(Matrix *board){
    bool empty =true;
    for (int i = 0; i < board->cols && empty; ++i) {
        if(board->m[0][i]!=' '){
            empty=false;
        }
    }
    return empty;
}

void find_blank_left(Matrix *board, int *row, int *col){
    bool found=false;
    while ( !found && *row <= board->rows - 1 && *col <= board->cols-2) {
        if(*row==0 & *col==0 && first_empty(board)){
            found=true;
        }else{
            if((*col==0 && board->m[*row][*col]!=' ') ||(board->m[*row][*col-1]==' ' && board->m[*row][*col]!=' ')){
                found=true;
            }
        }
        if(!found){
            if(*col+1>=board->cols-1){
                if(*row+1<=board->rows-1) {
                    *row = *row + 1;
                    *col = 0;
                }else{
                    *row=board->rows;
                    *col=board->cols;
                }
            }else{
                *col = *col+1;
            }
        }

    }
}

bool check_blank_left(Matrix *board, int i, int j, char orientation){
    bool empty=true;
    if(orientation=='O') {
        if (j < 4) {
            empty=false;
        } else {
            int cont = 0;
            while (cont < j  && empty) {
                if (board->m[i][j-cont-1]!=' '){
                    empty=false;
                }else{
                    j--;
                }
            }
        }
    }else if(orientation=='V'){
        if(j<2){
            empty =false;
        }else {
            for (int k = 0; k < 2 && empty; ++k) {
                for (int l = 0; l < 2 && empty; ++l) {
                    if(board->m[i+k][j-2+l]!=' '){
                        empty=false;
                    }
                }

            }
        }
    }
    return empty;

}

int count_blank(Matrix *board,int i, int j){
    int count=0;
    j=j-1;
    while(j>=0 && board->m[i][j]==' '){
        j--;
        count++;
    }
    return count;
}

bool insert_left_2D(Matrix *board, Tile tile){
    bool placed =false;
    if(tile.x=='+' && tile.y=='1'){
        plus_one(board);
        placed=true;
    }else{
        int i=0; int j=0;


        if(tile.orientation=='O') {
            char *hor = tile_to_horizontal(tile);
            while(!placed && i<=board->rows-2 ) {
                find_blank_left(board, &i, &j);
                if (i == 0 & j == 0 && first_empty(board)) {

                    //todo: se la board è vuota  le tessera è diversa da [MR] inserisco nei primi 4 char. non controllo
                    // per [+1] perchè ho già considerato in precedenza

                    if (tile.x != 'M' && tile.y != 'R') {
                        for (int k = 0; k < 4; ++k) {
                            board->m[0][k] = hor[k];
                        }
                        placed = true;
                    }

                }else if((tile.x=='M' && tile.y=='R') || (tile.x=='0' && tile.y=='0')){

                    //todo: se la tessera da aggiungere è [MR] oppure [00] aggiungo sempre e solo su prima riga ma
                    // controllo se m[0][0] != ' ' sposto di 4 se count blank trova solo due spazzi altrimenti appendo
                    // altrimenti ho già 4 spazi liberi per aggiungere
                    if(board->m[0][0]!=' '){
                        move_board(board,1);
                    }else{
                        if(count_blank(board,i,j)==2){
                            move_board(board,2);
                        }
                    }
                    //todo: mi posiziono su prima m[0][j] != ' '
                    while(board->m[0][j]==' '){
                        j++;
                    }

                    //todo:
                    if(tile.x=='M') {
                        if (board->m[0][j] == '[') {
                            hor[1] = board->m[0][j+2]; hor[2] = board->m[0][j+1];
                        } else if (board->m[0][j] == '{') {
                            hor[1] = board->m[0][j+1]; hor[2] = board->m[0][j+1];
                        } else if (board->m[0][j+1] == '}') {
                            hor[1] = board->m[0][j]; hor[2] = board->m[0][j];
                        }
                        placed=true;
                    }

                    for (int k = 0; k < 4 ; ++k) {
                        board->m[0][j-4+k]=hor[k];
                    }
                    placed=true;



                } else if (j+1<=board->cols-1 && (((board->m[i][j] == '[' || board->m[i][j] == '{') && (board->m[i][j + 1] == tile.y ||
                board->m[i][j + 1] == '0')) || ((board->m[i][j] == tile.y || board->m[i][j] == '0')
                && board->m[i][j + 1] == '}'))) {
                    //todo: aggiunta tessera orizzontale if esterno guarda se a dx della tessera c'è numero che combacia
                    // con tile.y oppure 0

                    if(j==0){

                        //todo: se sto aggiungendo in testa alla riga sposto tutta la board di 4 ma non sono necessari
                        // altri controlli perchè so già che numero a dx combacia -> aggiungo OK

                        move_board(board,1);
                        for (int k = 0; k < 4; ++k) {
                            board->m[i][k]=hor[k];
                        }
                        placed=true;

                    }else if(j-2==0 && count_blank(board,i,j)==2){

                        //todo: se invece j-2 =0 e i due char prima di j sono entrambi ' ' devo spostare la board solo
                        // di 2 e per come per j==0 no controlli aggiuntivi richiesti -> aggiungo OK

                        move_board(board,2);
                        for (int k = 0; k < 4; ++k) {
                            board->m[i][k]=hor[k];
                        }
                        placed=true;
                    }else{
                        //todo: in questo caso prima controllo che siano disponibili 4 char ' ' prima di j con chec_blank
                        if(check_blank_left(board,i,j,'O')) {

                            //todo: se sono disponibili controllo anche che o il char prima deli 4 blank sia anch'esso
                            // vuoto o che la tessera venga in testa ma non era necessario muovere la board perchè erano
                            // già vuoti i char oppure che la tessera a sinistra del blank sia [00] oppure il num
                            // combaci con tile.x

                            if((j>=5 && board->m[i][j-5]==' ') || j-4==0 ||(j>=8 && (board->m[i][j-5]==']' &&
                            (board->m[i][j-6]==tile.x || board->m[i][j-6]=='0'))) || (j>=6 && (board->m[i][j-5]==tile.x
                            || (board->m[i][j-5]=='}' && (board->m[i][j-6]==tile.x || board->m[i][j-6]=='0'))))  ) {

                                for (int k = 0; k < 4; ++k) {
                                    board->m[i][j-4+k] = hor[k];
                                }
                                placed = true;
                            }
                        }
                    }
                }

                if(!placed){
                    if(j+1>=board->cols-1){ i++; j=0;}
                    else{ j++; }
                }
            }
            free(hor);
        }else{
            char** ver= tile_to_vertical(tile);
            while(!placed && i<=board->rows-2){

                find_blank_left(board,&i,&j);

                if(i==0 && j==0 && first_empty(board)){
                    for (int k = 0; k < 2; ++k) {
                        for (int l = 0; l < 2; ++l) {
                            board->m[l][k]=ver[l][k];
                        }
                    }
                    placed=true;
                }else if(tile.x=='0' && tile.y=='0'){

                    if(j==0 && board->m[i][j] !=' '){

                        move_board(board,2);
                        for (int k = 0; k < 2; ++k) {
                            for (int l = 0; l < 2; ++l) {
                                board->m[i+k][l]=ver[k][l];
                            }
                        }
                        placed=true;
                    }

                }else if(j<=board->cols-2 && (((board->m[i][j]=='[' || board->m[i][j]=='{')&&(board->m[i][j+1]==tile.x
                || board->m[i][j+1]=='0'))|| (board->m[i][j+1]=='}' && (board->m[i][j]==tile.x ||
                board->m[i][j]=='0')))) {

                    if(i<=board->rows-2 && (board->m[i+1][j]==' ' || ((board->m[i+1][j]=='[' || board->m[i+1][j]=='{') &&
                    (board->m[i+1][j+1]==tile.y|| board->m[i+1][j+1]=='0')) ||(board->m[i+1][j+1]=='}' &&
                    (board->m[i+1][j]==tile.y ||board->m[i+1][j]=='0')))){

                        if(j==0){

                            move_board(board,2);

                            for (int k = 0; k < 2; ++k) {
                                for (int l = 0; l < 2; ++l) {
                                    board->m[i+k][l]=ver[k][l];
                                }
                            }

                            placed=true;

                        }else{
                            if(check_blank_left(board,i, j,'V')){
                                if(j-2==0){
                                    for (int k = 0; k < 2; ++k) {
                                        for (int l = 0; l < 2; ++l) {
                                            board->m[i+k][l]=ver[k][l];
                                        }
                                    }
                                    placed=true;
                                }else if(j>=4 && (board->m[i][j-3]==' '||((board->m[i][j-3]==']'||board->m[i][j-3]=='}')
                                && (board->m[i][j-4]==tile.x|| board->m[i][j-4]=='0')) || (board->m[i][j-4]=='{' &&
                                (board->m[i][j-3]==tile.x || board->m[i][j-3]=='0')))){

                                    if(board->m[i+1][j-3]==' ' || ((board->m[i+1][j-3]==']'||board->m[i+1][j-3]=='}') &&
                                    (board->m[i+1][j-4]==tile.y||board->m[i+1][j-4]=='0')) || (board->m[i+1][j-4]=='{'&&
                                    (board->m[i+1][j-3]==tile.y || board->m[i+1][j-3]=='0'))){

                                        for (int k = 0; k < 2; ++k) {
                                            for (int l = 0; l < 2; ++l) {
                                                board->m[i+k][j-2+l]=ver[k][l];
                                            }
                                        }
                                        placed=true;
                                    }
                                }
                            }
                        }
                    }
                }
                if(!placed){
                    if(j+1>=board->cols-1){ i++; j=0;}
                    else{ j++; }
                }
            }
            for (int k = 0; k < 2; ++k) {
                free(ver[k]);
            }
            free(ver);
        }
    }
    return placed;
}

void copy_board(Matrix *destination, Matrix *source){
    for (int i = 0; i < source->rows; ++i) {
        for (int j = 0; j < source->cols; ++j) {
            destination->m[i][j]=source->m[i][j];
        }
    }
}

bool available_moves_2D(Matrix* board, Tile* deck, int remain, int n){
    bool avail = false;
    Matrix copy;

    if(remain==n){
        avail=true;
    }else{
        copy= newMatrix(board->rows,board->cols);
        copy_board(&copy, board);
        int i=0;
        while(!avail && i < remain ) {
            Tile o=deck[i]; o.orientation='O';
            Tile v=deck[i]; v.orientation='V';
            if(deck[i].x=='M' || deck[i].x=='0'||deck[i].x=='+'){
                avail=true;
            }else if(insert_right_2D(&copy,o) ||insert_left_2D(&copy,o) ||
            insert_right_2D(&copy,v)|| insert_left_2D(&copy,v)){
                avail=true;
            }else{
                i++;
            }

        }
        free_board(&copy);
    }


    return avail;
}

bool select_autoplay(void){
    printf("Selezionare Partita:\n1: Interattiva\n2: IA\n");
    int x=-1;
    while(x!=1 && x!=2){
        scanf(" %d", &x);
    }
    system("clear");
    if(x==1){
        return false;
    }else{
        return true;
    }
}

void switch_tile(Tile* x){
    char tmp=x->y;
    x->y=x->x;
    x->x=tmp;
}

void autoplay(Matrix *board, Tile* deck, int remain, int n, int mode){
    bool inserted =false;
    //todo:mode==1 -> Domino Lineare
    if(mode==1){
        int i=0;
        print_screen(board,deck,remain);
        while(remain>0 && i<remain && available_moves_linear(board,deck, remain, n) ){
            if(inserted){
                print_screen(board,deck,remain);
                inserted=false;
            }
            sleep(3);
            if(deck[i].x=='M' || deck[i].x=='+'){
                if(remain<n){
                    Tile chosen=deck[i];
                    if(insert_right(board,chosen) || insert_left(board, chosen)){
                        inserted=true;
                    }
                }
            }else{
                Tile a=deck[i];
                Tile b; b.x=deck[i].y; b.y=deck[i].x;

                if(insert_right(board,a)|| insert_left(board,a)|| insert_right(board,b)|| insert_left(board,b)){
                    inserted=true;
                }
            }
            if(inserted){
                Tile tmp=deck[i];
                deck[i]=deck[remain-1];
                deck[remain-1]=tmp;
                remain--;
                i=0;
            }else{
                i++;
            }
        }
    }else{
        int i=0;
        print_screen(board,deck,remain);
        while( remain>0 && i<remain && available_moves_2D(board,deck,remain,n)){
            if(inserted){
                print_screen(board,deck,remain);
                inserted=false;
            }
            sleep(2);
            if(deck[i].x=='+'){
                Tile chosen=deck[i]; chosen.orientation='O';
                if(remain<n && insert_right_2D(board,chosen)){
                    inserted=true;
                }
            }else if(deck[i].x=='M'){
                Tile chosen=deck[i]; chosen.orientation='O';
                if(remain< n && (insert_right_2D(board, chosen)|| insert_left_2D(board,chosen))){
                    inserted=true;
                }
            }else{
                Tile a_o=deck[i];a_o.orientation='O';
                Tile b_o=a_o; switch_tile(&b_o);
                Tile a_v=a_o; a_v.orientation='V';
                Tile b_v=b_o; b_v.orientation='V';

                if(insert_right_2D(board,a_v) || insert_right_2D(board,a_o) || insert_right_2D(board,b_v) ||
                insert_right_2D(board,b_o) || insert_left_2D(board,a_v) || insert_left_2D(board,a_o) ||
                insert_left_2D(board,b_v) || insert_left_2D(board,b_o)){
                    inserted=true;
                }

            }
            if(inserted){
                Tile tmp=deck[i];
                deck[i]=deck[remain-1];
                deck[remain-1]=tmp;
                remain--;
                i=0;
            }else{
                i++;
            }
        }
    }
    print_board(board);
}
