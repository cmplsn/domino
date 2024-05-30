#include "player.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>

/*! Funzione MAIN:
 *
 * Funzione principale da cui inizia l'esecuzione di tutto il gioco. All'interno di main viene selezionata la durata
 * ed il numero di tessere con cui si svolgerà la partita tramite choose_valid_n(). Successivamente:
 * - viene creato e riempito l'array delle tessere del giocatore (Tile* deck) tramite la funzione assegna().
 * - viene selezionata la modalità di gioco (Lineare/2D) della partita tramite select_mode()
 * - viene selezionata la tipologia di partità (Interattiva/AI) tramite select_autoplay();
 *
 * In base alla modalità di gioco selezionata si entrerà poi in uno dei due rami if-else che adatta i controlli, la
 * dimensione e il formata del tavolo gioco (Matrix board) in base alla necessità della modalità.
 * All'interno di entrambi i rami dell'if-else vengono eseguite diverse azioni anche in base alla tipologia di partità
 * selezionata.
 * Se la tipologia di partita è stata impostata su Interattiva all'ora verrano ripetute le operazioni di controllo e
 * di selezione in un ciclo lungo quanto la dimensione del deck del giocatore.
 */
int main(void) {
    system("clear");

    int n = choose_valid_n();
    //todo: scelgo numero di tessere con cui inizia il gioco

    Tile* deck = assegna(n);
    int mode=select_mode();
    bool autplay=select_autoplay();

    Matrix board;
    int remain=n;

    if( mode == 1){
        board= newMatrix(1,n*4);
        if(!autplay) {
            while (remain > 0 && available_moves_linear(&board, deck, remain, n)) {
                print_screen(&board, deck, remain);
                Tile tile = select_tile(deck, remain, n, 1);
                if (select_pos() == 'D') {
                    if (insert_right(&board, tile) == true) {
                        remain--;
                    } else {
                        system("clear");
                        printf("mossa non possibile, riprova\n\n");
                    }
                } else {
                    if (insert_left(&board, tile) == true) {
                        remain--;
                    } else {
                        system("clear");
                        printf("mossa non possibile, riprova\n\n");
                    }
                }
            }
        }else{
            autoplay(&board,deck,remain,n,1);
        }
    }else {
        board= newMatrix(2*n,4*n);
        if(!autplay) {
            while (remain > 0 && available_moves_2D(&board, deck, remain, n)) {
                print_screen(&board, deck, remain);
                Tile x = select_tile(deck, remain, n, 2);
                if (((x.x == '+' && x.y == '1') || (x.x == 'M' && x.y == 'R')) && x.orientation == 'V') {
                    printf("[%c%c] non può essere utilizzata in verticale\n", x.x, x.y);
                    continue;
                }
                if (select_pos() == 'D') {
                    if (insert_right_2D(&board, x) == true) {
                        remain--;
                    } else {
                        system("clear");
                        printf("mossa non possibile, riprova\n\n");
                    }
                } else {
                    if (insert_left_2D(&board, x) == true) {
                        remain--;
                    } else {
                        system("clear");
                        printf("mossa non possibile, riprova\n\n");
                    }
                }
            }
        }else{
            autoplay(&board, deck, remain,n,2);
        }
    }


    end_game(&board);

    /** operazione di free finale per evitare memory leaks*/
    free(deck);
    free_board(&board);

    return 0;
}
