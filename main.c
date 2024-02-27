#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "board.h"



int main() {
    int n = choose_valid_n(); /*todo: scelgo numero di tessere con cui inizia il gioco*/
    int *tessere_giocatore = assegna_tessere(n);
    Matrix board = newMatrix();

    /*todo: operazione di free finale per evitare memory leaks*/
    free_deck(tessere_giocatore, n);
    free_board(board.matrix, board.rows);

    return 0;
}


    //Matrix a;
    /*int remain=n;
    int tile =choose_tile(tessere_giocatore,remain);
    char c =choose_orientation(tile);
    //place_tile(board,c,tile);
    board.matrix[0][0]=1;
    board.matrix[0][1]=2;
    print_board(board);
    while(!(c=='V' || c=='O')){
        printf("input non corretto\n");
        c = choose_orientation(tile);
    }*/
    /*while(remain >0){
        printf("le tue tessere sono:\n");
        mostra_tessere(tessere_giocatore, remain);
        int t = choose_tile(tessere_giocatore,remain);
        char o = choose_orientation(t);
        char p=choose_position();
        if(p=='D') addRight(); else addLeft();

        if(remain==n){
            if(o=='O'){
                place_orizzontale(t,board);
            }else if(o=='V'){
                place_verticale(t,board);
            }
        }
        remain--;
    }*/
