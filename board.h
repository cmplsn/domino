//
// Created by Alessandro on 14/03/24.
//

#ifndef PROJECT_IAP_BOARD_H
#define PROJECT_IAP_BOARD_H
#include "player.h"

typedef struct Matrix{
    int rows;
    int cols;
    char** m;
}Matrix;

Matrix newMatrix(int rows, int cols);

void free_board(Matrix* board);

void switch_tile(Tile* x);


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
int select_mode(void);

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
 * utilizzate solo in orizzontale. Per quanto riguarda le colonne invece, essendo ogni tessera rappresentata da 4 char,
 * viene impostata come lunghezza 4*n dove n rappresenta il numero di carte con cui si è iniziata la partita.
 *
 * - Domino 2D: in questa modalità le tessere possono essere utilizzate sia in orizzontale che in verticale. quindi
 * viene impostato come numero di righe 2*n (una tessera in verticale occuperà 2 char in altezza) e 4*n colonne.
 *
 * Dopo aver fatto la malloc per dare la dimensione al tavolo di gioco, tutte le celle vengono inizializzate con un blank
 * ' '.
 *
 *
 * */
char** initboard(int rows, int cols);

/*!
 * print_board(Matrix* board)
 *
 * tipo di ritorno void
 *
 * parametri: Matrix* board
 *
 * Viene preso in input l'oggetto board contente: il tavolo di gioco utilizzato (char** m), il numero di righe ed il
 * numero di colonne e viene stampato il contenuto del tavolo da gioco con le pedine posizionate fino a quel momento
 * */
void print_board(Matrix* board);

/*!
 * Tipo di ritorno: char**. la funzione restituisce doppio puntatore ad un array 2*2 di char che conterrà la tessera
 * selezionata per l'inserimento nella board già in formato verticale.
 *
 * Parametri: tessera di tipo struct Tile
 *
 * Viene creato un char** 2*2 che conterra in posizione [0][1] il valore di t.x ed in posizione [1][0] il valore di t.y.
 * */
char** tile_to_vertical(Tile t);

/*!
 * Tipo di Ritorno: char*
 *
 * Parametri: tessera t di tipo struct Tile.
 *
 * La funzione restituisce un puntatore ad un array di char di dimensione 4 che conterra la tessera selezionata per
 * l'inserimento nella board in formato orizzontale. Viene allocato un char* 1*4 che conterra in posizione [0][1] il
 * valore salvato in t.x ed in posizione [0][2] il valore salvato in t.y
 * */
char* tile_to_horizontal(Tile t);

/*!
 * Tipo di ritorno: char
 *
 * Parametri: nessuno
 *
 * La funzione viene utilizzata per chiedere al giocatore se inserire la tessera a sinistra o a destra nel campo di gioco.
 * Viene quindi chiesto di inserire il carattere D (destra) o S (sinistra) e viene ritornato il carattere ricevuto in input
 * se valido altrimenti viene richiesto il rinserimento.
 * */
char select_pos(void);

/*!
 * Tipo di ritorno: bool
 *
 * Parametri: Matrix *board, Tile tile
 *
 * Funzione utilizzata per l'inserimento di una tessera sulla destra del tavolo di gioco in modalità Domino Lineare.
 * */
bool insert_right(Matrix *board, Tile tile);

bool insert_left(Matrix* board, Tile tile);

bool insert_left_2D(Matrix* board, Tile tile);

bool insert_right_2D(Matrix* board, Tile tile);

int get_score(Matrix* board);

bool available_moves_linear(Matrix* board, Tile* deck,int deck_size, int n);

void end_game(Matrix* board);

void print_screen(Matrix* board, Tile* deck, int decksize);

bool first_empty(Matrix *board);

void find_blank(Matrix *board, int *row, int *col);

void find_blank_left(Matrix *board, int *row, int *col);

int count_blank(Matrix *board, int i, int j);

bool check_blank(Matrix *board, int i, int j, char orientation);

bool check_blank_left(Matrix *board, int i, int j, char orientation);

void copy_board(Matrix* destination, Matrix* source);

bool available_moves_2D(Matrix* board, Tile* deck, int remain, int n);

bool select_autoplay(void);

void autoplay(Matrix *board, Tile* deck, int remain, int n, int mode);

void plus_one(Matrix *board);

void move_board(Matrix *board, int mode);



#endif //PROJECT_IAP_BOARD_H
