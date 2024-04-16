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
    print_board(board);
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
    system("clear");
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
    while(*row< board->rows){
        while(*col<board->cols){
            if(board->m[*row][*col]==' '){
                return;
            }else{
                if(*col+1 >= board->cols){
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

                    if(i==0 && j==0){
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
                                    board->m[i+1][j-1]==' ') && board->m[i+1][j+2]==' ' || board->m[i+1][j+2]==tile.y) &&
                                    (board->m[i][j+2]==' ' || board->m[i][j+2]==tile.x || j+2==board->cols-1)){

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

/*void find_blank_left(Matrix *board, int *row, int *col){
    bool found=false;
    while(*row <board->rows-1 && !found){
        while(*col<= board->cols-1 && !found){

            //todo: se i==0 e j==0: ritorno subito quei valore perchè board è vuota
            if(*row==0 && *col==0 && board->m[*row][*col]==' '){
                found=true;
            }else{

                //todo: se trovo una cella ' ' e la sua successiva è diversa da ' ' e IN-BOUND ritorna perchè
                // vuol dire che ho trovato una cella a cui attaccarmi A SINISTRA. restituisco come posizione
                // la prima cella occupata a dx di ' '

                if(*row!=0 && *col==0 && board->m[*row][*col]!=' '){
                    found=true;

                }else if(board->m[*row][*col]==' ' && *col+1<=board->cols-1 && board->m[*row][*col+1]!=' '){
                    *col=*col+1;
                    found=true;
                }else{

                    //todo: se *col+1 out of bound faccio ripartire la ricerca da *row+1 *col=0 altrimenti *col+1
                    if(*col+1>=board->cols){
                        *row=*row+1;
                        *col=0;
                    }else{
                        *col=*col+1;
                    }
                }
            }
        }
    }
}*/

/*bool check_blank_left(Matrix *board, int i, int j, char orientation){
    bool ok=true;
    if(orientation=='O' && j>=3){
        //todo: se i 4 char del blank che ho trovato sono tutti liberi allora ok resta a true e posso inserire lì una
        // tessera in orizzontale
        for (int k = j; k >= j-3 && ok; --k) {
            if(board->m[i][k]!=' '){
                ok=false;
            }
        }
    }else if(orientation=='V' && j>=1){
        //todo: aggiungere stessa cosa per tessera in verticale quindi due for o due while annidati
        for (int k = 0; k <2 && ok; ++k) {
            for (int l = j; l >=j-1 && ok ; ++l) {
                if(board->m[i+k][l]==' '){
                    ok=false;
                }
            }
        }

    }
    return ok;
}*/

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
    while ( !found && *row <= board->rows - 1 && *col <= board->cols - 2) {
        if(*row==0 & *col==0 && first_empty(board)){
            found=true;
        }else{
            if((*col==0 && board->m[*row][*col]!=' ') ||(board->m[*row][*col]==' ' && board->m[*row][*col+1]!=' ')){
                found=true;
            }
        }

        if(!found){
            if(*col+1<=board->cols-1){
                *row=*row+1;
                *col=0;
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
    }
    return empty;

}

int count_blank(Matrix *board){
    int j=0;
    while(board->m[0][j]==' '){
        j++;
    }
    return j;
}

bool insert_left_2D(Matrix *board, Tile tile){
    bool placed =false;
    if(tile.x=='+' && tile.y=='1'){
        plus_one(board);
        placed=true;
    }else{
        int i=0; int j=0;

        find_blank_left(board, &i, &j);
        if(tile.orientation=='O') {
            char *hor = tile_to_horizontal(tile);
            while(!placed && i<=board->rows-1 ) {
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
                    if(board->m[0][0]!=' '){
                        move_board(board,1);
                    }else{
                        if(count_blank(board)==2){
                            move_board(board,2);
                        }
                    }
                    if(tile.x=='M') {
                        if (board->m[0][4] == '[') {
                            hor[1] = board->m[0][6]; hor[2] = board->m[0][5];
                        } else if (board->m[0][4] == '{') {
                            hor[1] = board->m[0][5]; hor[2] = board->m[0][5];
                        } else if (board->m[0][5] == '}') {
                            hor[1] = board->m[0][4]; hor[2] = board->m[0][4];
                        }
                    }
                    for (int k = 0; k < 4; ++k) {
                        board->m[0][k]=hor[k];
                    }
                    placed=true;

                } else if (((board->m[i][j] == '[' || board->m[i][j] == '{') && (board->m[i][j + 1] == tile.y ||
                board->m[i][j + 1] == '0')) || ((board->m[i][j] == tile.y || board->m[i][j] == '0')
                && board->m[i][j + 1] == '}')) {
                    if(j==0){
                        move_board(board,1);
                        j=j+4;
                    }else if(j-2==0 && count_blank(board)==2){
                        move_board(board,2);
                        j=j+2;
                    }
                    if(check_blank_left(board,i,j,'O')) {
                        if((j>=5 && board->m[i][j-5]==' ') || j-4==0 ||(j>=8 && (board->m[i][j-5]==']' &&
                        (board->m[i][j-6]==tile.x || board->m[i][j-6]=='0'))) || (j>=6 && (board->m[i][j-5]==tile.x ||
                        (board->m[i][j-5]=='}' && (board->m[i][j-6]==tile.x || board->m[i][j-6]=='0'))))  ) {
                            for (int k = 0; k < 4; ++k) {
                                board->m[i][j-4+k] = hor[k];
                            }
                            placed = true;
                        }

                    }
                }else{
                    //todo:DA COMPLETARE
                }

                if(!placed){
                    if(j+1>=board->cols-1){
                        i++;
                        j=0;
                    }else{
                        j++;
                    }
                }
            }
            free(hor);
        }else{

            //todo: AGGIUNTA VERTICALE

        }
    }
    return placed;
}

/*bool insert_left_2D(Matrix *board, Tile tile){
    bool placed=false;
    if(tile.x=='+'&&tile.y=='1'){
        plus_one(board);
        placed=true;
    }else{
        int  i=0; int j=0;
        while(!placed && i<=board->rows-1 && j<=board->cols-1){
            find_blank_left(board, &i, &j);
            if(tile.orientation=='O'){
                char *h= tile_to_horizontal(tile);
                //todo: se la board è vuota e la tessera è diversa da [MR]
                if(i==0 && j==0){
                    if(!(tile.x=='M' && tile.y=='R')) {
                        for (int k = 0; k < 4; ++k) {
                            board->m[0][k] = h[k];
                        }
                        placed = true;
                    }

                }else if(tile.x=='0' && tile.y=='0'){
                    //todo: se la tessera == [00] viene inserita a sinistra sempre sulla prima riga
                    if(j==0){
                        move_board(board,1);
                        for (int k = 0; k < 4; ++k) {
                            board->m[i][k]=h[k];
                        }
                        placed=true;
                    }else if(check_blank_left(board,i,j,'O')){
                        for (int k = 0; k < 4; ++k) {
                            board->m[i][j-4+k]=h[k];
                        }
                        placed=true;
                    }

                }else if(tile.x=='M'&& tile.y=='R'){
                    // todo: se tessera == [MR] viene inserita sempre su prima riga.
                    if(j==0 && board->m[i][j]!= ' '){
                        h[1]=board->m[i][2];
                        h[2]=board->m[i][2];
                        move_board(board,1);
                        for (int k = 0; k < 4; ++k) {
                            board->m[i][k]=h[k];
                        }
                        placed=true;
                    }else if(check_blank_left(board,i,j,'O')){
                        if(board->m[i][j]=='['){
                            h[1]=board->m[i][j+2];
                            h[2]=board->m[i][j+1];
                        }else if(board->m[i][j]=='{'){
                            h[1]=board->m[i][j+1];
                            h[2]=board->m[i][j+1];
                        }else if(board->m[i][j+1]=='}'){
                            h[1]=board->m[i][j];
                            h[2]=board->m[i][j];
                        }
                        for (int k = 0; k < 4; ++k) {
                            board->m[i][j-4+k]=h[k];
                        }
                        placed=true;
                    }

                }else if(j<=board->cols-2 && (((board->m[i][j]=='{'|| board->m[i][j]=='[')&&(board->m[i][j+1]==tile.y
                || board->m[i][j]=='0'))|| (board->m[i][j+1]=='}'&&
                (board->m[i][j]==tile.y|| board->m[i][j]=='0')))){
                    //todo: controllo se c'è almeno un char dopo j (quindi 2 char dopo l'ultimo ' '
                    // perchè devo fare controlli su j+1) e se c'è e trovo [x {x oppure x} tali che x==tile.y oppure x==0

                    if(j==0) {

                        //todo: se j==0 vuol dire che mi trovo all'inizio della riga quindi dovrò ricopiare la
                        // board spostata di 4 verso dx

                        move_board(board, 1);
                        for (int k = 0; k < 4; ++k) {
                            board->m[i][k] = h[k];
                        }
                        placed = true;
                    }else{

                        //todo: altrimenti controllo che i 4 char antecedenti j siano tutti a blank per permettere
                        // inserimento tessera
                        if(check_blank_left(board,i,j-1,'O')){

                            //todo: infine inserisco tessera solo se il char antecedente ai 4 char dove vado a
                            // posizionare la tessera è == ' ' oppure se trovo y] y} o {y tale che x==tile.x
                            if(j-4==0 || board->m[i][j-5]==' ' ||((board->m[i][j-5]=='}'
                            || board->m[i][j-5]==']') && board->m[i][j-6]==tile.x)|| board->m[i][j-5]==tile.x){
                                for (int k = 0; k <4 ;++k) {
                                    board->m[i][j-4+k]=h[k];
                                }
                                placed=true;
                            }
                        }
                    }

                }
                free(h);
            }else{
                char **ver= tile_to_vertical(tile);
                if(i==0 && j==0){
                    if(tile.x!='M' && tile.y!='R') {
                        for (int k = 0; k < 2; ++k) {
                            for (int l = 0; l < 2; ++l) {
                                board->m[k][l] = ver[k][l];
                            }
                        }
                        placed = true;
                    }

                }else if(tile.x=='0'&& tile.y=='0'){

                    move_board(board,2);
                    for (int k = 0; k < 2; ++k) {
                        for (int l = 0; l < 2; ++l) {
                            board->m[k][l]=ver[k][l];
                        }
                    }
                    placed=true;

                //todo: la cella dove sto attaccando si presenta come {y [y oppure y} dove y==tile.x oppure y=='0'
                }else if(i+1<=board->rows-1 && j<=board->cols-2 && (((board->m[i][j]=='{'|| board->m[i][j]=='[') &&
                (board->m[i][j+1]==tile.x||board->m[i][j+1]=='0') )|| (board->m[i][j+1]=='}'&&
                (board->m[i][j]==tile.x || board->m[i][j]=='0') ))){

                    //todo: attaccando a SINISTRA ma in verticale devo controllare con gli stessi controlli di sopra ma
                    // su tile.y anche la cella sottostante quella dove ho trovato il blank
                    if(board->m[i+1][j]==' ' || (((board->m[i+1][j]=='{'|| board->m[i+1][j]=='[') &&
                    (board->m[i+1][j+1]==tile.y||board->m[i+1][j+1]=='0'))|| (board->m[i+1][j+1]=='}'
                    && (board->m[i+1][j]==tile.y || board->m[i+1][j]=='0')))){

                        //todo: se il blank è stato trovato in corrispondenza di j==0 sposto board e attacco ad inizio board.
                        if(j==0){

                            move_board(board,2);
                            for (int k = 0; k < 2; ++k) {
                                for (int l = 0; l < 2; ++l) {
                                    board->m[i+k][l]=ver[k][l];
                                }
                            }

                            placed=true;
                        }else{
                            if(check_blank_left(board, i,j-1,'V')){

                                //todo: a destra della tessera o finisce la board oppure troviamo ' ' oppure y] y} o {y
                                // tale che y==0 oppure y==tile.x
                                if( j-2==0 ||( j-3>=0 && (board->m[i][j-3]==' ' || ((board->m[i][j-2]==']'||
                                board->m[i][j-2]=='}')&&(board->m[i][j-3]==tile.x||board->m[i][j-3]=='0'))
                                ||(board->m[i][j-3]=='{' && (board->m[i][j-2]==tile.x ||
                                board->m[i][j-2]=='0'))))){

                                    //todo: a destra della tessera nella riga sotto stessa cosa della riga sopra.
                                    if( i+1<=board->rows-1 && (j-2==0 || (j-3>=0 &&(board->m[i+1][j-3]==' '||
                                    ((board->m[i+1][j-2]==']'|| board->m[i+1][j-2]=='}')&&
                                    (board->m[i+1][j-3]==tile.y || board->m[i+1][j-3]=='0')) ||
                                    (board->m[i+1][j-3]=='{' && (board->m[i+1][j-2]==tile.y ||
                                    board->m[i+1][j-2]=='0')))))){
                                        for (int k = 0; k <2 ; ++k) {
                                            for (int l = 0; l <2 ; ++l) {
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

                for (int k = 0; k < 2; ++k) {
                    free(ver[k]);
                }
                free(ver);
            }
            if (!placed){
                if(j+1>board->cols-1){
                    i++;
                    j=0;
                }else{
                    j++;
                }
            }

        }
    }


    return placed;
}*/

//todo: AGGIUNGERE AVAILABLES_MOVES_2D
