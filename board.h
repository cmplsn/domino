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
 * parametri: Matrix *board
 *
 * Viene preso in input l'oggetto board contente: il tavolo di gioco utilizzato (char** m), il numero di righe ed il
 * numero di colonne e viene stampato il contenuto del tavolo da gioco con le tessere posizionate fino a quel momento
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
 * Funzione utilizzata per l'inserimento di una tessera a destra sul tavolo di gioco in modalità Domino Lineare.
 * Viene impostata variabiel bool ok a false che viene cambiata a true solo dopo aver effettivamente inserito la tessera
 * sul campo da gioco. un ciclo while incrementa la variabile i utilizzata come contatore fino quando non trova una cella
 * della board contenente uno spazio ' ' per sapere la posizione in cui iniziare a posizionare la tessera sulla board.
 *
 * - Prima sezione: controlla se la tessera da inserire è una tessera speciale [MR] e se è già stata inserita almeno
 * un'altra tessera sul campo di gioco (i>3). In caso le condizioni siano valide, la tessera viene inserita e come da
 * specifica, la nuova tessera inserita avrà caratteri uguali ma specchiati rispetto alla tessera a cui si sta attaccando.
 * [12][MR] -> [12][21].
 *
 * - Seconda sezione: controlla se la tessera è una tessera speciale (+1) e che sia già stata inserita almeno uno tessera
 * ed in caso positivo, richiama la funzione plus_one() sulla board.
 *
 * - Terza sezione: controllo se la tessera è la prima che stiamo inserendo, se la tessera è tessera speciale [00] oppure
 * se il carattere sinistro della tessera che stiamo aggiungendo è compatibile con il carattere destro della tessera a
 * cui si sta attaccando ed in caso positivo esegue l'inserimento.
 *
 * la funzione ritorna il valore della variabile booleana ok che viene utilizzata come guida nella funzione main per
 * sapere se la tessera è stata correttamente inserita o meno
 * */
bool insert_right(Matrix *board, Tile tile);

/*!
 * Tipo di ritorno: bool
 *
 * Parametri: Matrix *board, Tile tile
 *
 * Esegue gli stessi controlli di insert_right() però, se i controlli sulla tessera
 * sono validi e può effettivamente essere inserita, in caso la tessera sia diversa dalla tessera speciale [+1], il campo
 * da gioco viene spostato verso destra con la funzione move_board() così da non sovrascriverlo.
 * */
bool insert_left(Matrix* board, Tile tile);

/*!
 * Tipo di ritorno: bool
 *
 * Parametri: Matrix *board, Tile tile
 *
 * Per la tessera speciale [+1] viene richiamata la funzione plus_one().
 * Altrimenti in base al verso in cui si vuole inserire la tessera (orizzontale/verticale, salvato come campo orientation in Tile)
 * la funzione verrà eseguita sul corrispondente ramo di if-else nel quale verranno richiamate rispettivamente tile_to_horizontal() o
 * tile_to_vertical(). Entrambi i rami eseguono un ciclo while per la ricerca di una posizione disponibile per
 * l'inserimento della tessera tramite find_blank_left().
 *
 * - Tessera da posizionare in ORIZZONTALE: se l'inserimento viene fatto a ridosso del lato sinistro del tavolo di gioco,
 * quest'ultimo verrà spostato verso destra con la funzione move_board(). Altrimenti, con la possibilità che la tessera
 * venga inserita in uno spazio libero tra altre due tessere, vengono fatti controlli sia  sul numero sinistro della
 * tessera a cui sta per essere attaccata quella nuova, sia sulla cella a destra dello spazio dove sta per essere attaccata.
 *
 * - Tessera da posizionare in VERTICALE: allo stesso modo dell'inserimento in orizzontale, dato lo spazio disponibile per il
 * possibile inserimento, verranno controllati la compatibilità del numero della tessera alla sua destra ma anche la
 * compatibilità a sinistra dello spazio libero. Da che la tessera viene inserita in verticale, verranno eseguiti gli
 * stessi controlli anche  per la riga sottostante dove verrà posizionata la seconda parte della tessera.
 *
 * Viene ritornato un valore booleano che funge da guida per la funzione main per sapere se la tessera è stata inserita e
 * quindi rimuovere la tessera dal deck del giocatore oppure se la tessera non rispetta le condizioni e quindi non è stata inserita.
 * */
bool insert_left_2D(Matrix* board, Tile tile);

/*!
 * Tipo di ritorno: bool
 *
 * Parametri: Matrix *board, Tile tile
 *
 * Alla stessa maniera di insert_left_2D() ricerca su ciclo while un posto disponibile per l'inserimento della tessera
 * in verticale o orizzontale. Esegue i controlli di compatibilità sia a destra che a sinistra dello spazio disponibile
 * e nel caso in cui la tessera debba essere posta in verticale controlla su tutte due le righe dove avverrà l'inserimento.
 * Viene eseguito anche controllo di inserimento non out-of-bound della riga.
 * */
bool insert_right_2D(Matrix* board, Tile tile);

/*!
 * Tipo di ritorno: int
 *
 * Parametri: Matrix *board
 *
 * La funzione scorre tutto il tavolo di gioco e somma riga per riga i numeri delle tessere posizionate.
 * Restituisce il totale che rappresenta il punteggio accumulato fino a quel momento della partita.
 * */
int get_score(Matrix* board);

/*!
 * Tipo di ritorno: bool
 *
 * Parametri: Matrix *board, Tile *deck, int deck_size, int n;
 * - Tile *deck: puntatore alla mano di tessere del giocatore
 * - int deck_size: dimensione del deck al momento della chiamata a funzione. man mano che la partita procede, deck_size diminuisce.
 * - int n: dimensione del deck del giocatore all'inizio della partita
 *
 *
 * */
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
