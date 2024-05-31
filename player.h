//
// Created by Alessandro on 14/03/24.
//

#ifndef PROJECT_IAP_PLAYER_H
#define PROJECT_IAP_PLAYER_H
#include <stdbool.h>

/*!
 *  Ogni tessera è rappresentata come un oggetto di tipo struct Tile contenente due char che andranno ad identificare i
 *  numeri sulla tessera (x ed y) ed un altro char orientation che da informazioni sulla disposizione della tessera sul
 *  tavolo di gioco.
 * */
typedef struct Tile{

    /*!
     * nel caso di tessera posizionata in orizzontale rappresenta il numero più a sinistra, nel caso di tessere
     * in verticale rappresenta il numero sulla riga più in alto.
     * */
    char x;

    /*!
     * nel caso di tessera posizionata in orizzontale rappresenta il numero più a destra, nel caso di tessere
     * in verticale rappresenta il numero sulla riga più in basso.
     * */
    char y;

    /*!
     * Assume due possibili valori:
     * - O: indica che la tessera verrà posizionata in Orizzontale
     * - V: indica che la tessera verrà posizionata in Verticale.
     * */
    char orientation;
}Tile;

/*!
 * Tipo: Tile*
 *
 * Parametri: int n
 *
 * All'interno della funzione viene definito l'array contenente tutte e 24 le possibili tessere del domino viene allocato
 * spazio per un array di n Tiles, dove n è il numero di tessere con il quale si è deciso di iniziare la partita tramite
 * choose_valid_n(). Viene poi utilizzata la funzione srand(time(NULL)) per far si che la funzione rand() utilizzata
 * successivamente crei ogni volta una sequenza di estrazione effettivamente casuale.
 * L'array hand, che rappresenta la mano di tessere che avrà il giocatore, viene riempito con inserimento di tessere
 * scelte casualmente, anche con ripetizioni, dall'array deck. Resituisce l'array hand riempito.
 * */
Tile* assegna(int n);

/*!
 * Tipo: void
 *
 * Parametri:
 * - Tile *hand: mano di tessere del giocatore.
 * - int n: numero di elementi da stampare dell'array hand.
 *
 * Stampa a schermo le n tessere rimanenti nella mano del giocatore
 * */
void print_hand(Tile* hand,int n);

/*!
 * Tipo: int
 *
 * Parametri: nessuno
 *
 * Viene richiesto al giocatore di selezionare tramite input da tastiera la durata della partita.
 * - Input == 1: viene selezionata partita "corta" e verrà creato con la funzione assegna() una mano di 5 tessere.
 * - Input == 2: viene selezionata partita "intermedia" e verrà creato con la funzione assegna() una mano di 10 tessere.
 * - Input == 3: viene selezionata partita "lunga" e verrà creato con la funzione assegna() una mano di 15 tessere.
 *
 * Se l'input ricevuto è diverso da 1,2 o 3 viene richiesto il rinserimento fino alla ricezione di un'opzione valida.
 * */
int choose_valid_n(void);

/*!
 * Tipo: bool
 *
 * Parametri:
 * - Tile *deck: mano di tessere del giocatore.
 * - int size: dimensione rimanente dell'array deck.
 * - Tile tile: tessera selezionata dal giocatore per essere inserita
 * - int n: dimensione iniziale dell'array deck, numero di tessere ricevute all'inizio della partita.
 *
 * La funzione verifica se la tessera selezionata tramite select_tile() è valida, ovvero, se fa effettivamente parte
 * della mano del giocatore.
 * Se il deck è ancora pieno (size==n) quindi sta per essere posizionata la prima tessera, la funzione impedisce l'utilizzo
 * delle tessere speciali [+1] e [MR].
 * Se invece è stata selezionata una tessere diversa dalle due appena citate controlla, scorrendo il deck una tessera
 * alla volta se tile è uguale a una tessera del deck oppure se è una tessera del deck con le cifre scambiate (il giocatore
 * può usare le tessera del deck [xy] anche in ordine inverso ovvero [yx]).
 * Se la tessera selezionata fa match con una tessera del deck allora la funzione ritorna True altrimenti restituisce False
 * e viene nuovamente richiesto di selezionare una tessere valida.
 * */
bool valid_tile(Tile* deck, int size, Tile tile, int n);

/*!
 * Tipo: Tile
 *
 * Parametri:
 * - Tile *deck: mano delle tessere del giocatore
 * - int size: dimensione rimanente dell'array deck.
 * - int n: dimensione iniziale dell'array deck, numero di tessere ricevute all'inizio della partita.
 * - int mode: definisce la modalità di gioco scelta per la partita (Lineare /2D)
 *
 * Viene chiesto di inserire in input da tastiera i due char corrispondenti ai simboli presenti sulla tessera che il giocatore
 * vuole selezionare. Se per esempio si volesse selezionare la tessera [4 6], il giocatore dovrà immettere in input 46.
 * La tessera può anche essere utilizzata con le cifre scambiate ovvero se il giocatore da in input 64, tramite la funzione
 * valid_tile() viene fatto il controllo sulle cifre scambiate e ne viene concesso l'utilizzo.
 * Nel caso in cui la tessera non sia presente nella mano del giocatore, viene nuovamente richiesto l'inserimento di una
 * tessera valida effettivamente presente nella mano del giocatore.
 *
 * Una volta selezionata una tessera valida, nel caso in cui si stia giocando una partita in modalità 2D (quindi mode==2),
 * viene richiesto al giocatore di selezionare l'orientamento con il quale vuole posizionare la tessera sul campo da gioco.
 * */
Tile select_tile(Tile* deck, int size, int n,int mode);

#endif //PROJECT_IAP_PLAYER_H
