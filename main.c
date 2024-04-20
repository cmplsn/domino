#include "player.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    system("clear");

    int n = choose_valid_n();
    //todo: scelgo numero di tessere con cui inizia il gioco

    Tile* deck = assegna(n);
    deck[0].x='4'; deck[0].y='6';
    deck[1].x='4'; deck[1].y='6';
    deck[2].x='3'; deck[2].y='3';
    //deck[2].x='M'; deck[2].y='R';
    /*deck[3].x='4'; deck[3].y='4';
    deck[4].x='M'; deck[4].y='R';
    deck[5].x='1'; deck[5].y='6';
    deck[6].x='1'; deck[6].y='1';
    deck[7].x='1'; deck[7].y='4';
    deck[8].x='0'; deck[8].y='0';*/

    for (int i = 2; i < 4; ++i) {
        deck[i].x='3'; deck[i].y='3';
    }


    Matrix board;
    int remain=n;

    if( select_mode() == 1){
        board= newMatrix(1,n*4);
        while(remain>0 && available_moves_linear(&board, deck, remain, n)){
            print_screen(&board, deck, remain);
            Tile tile= select_tile(deck,remain,n,1);
            if(select_pos()=='D'){
                if (insert_right(&board,tile)==true){
                    remain--;
                }else{
                    system("clear");
                    printf("mossa non possibile, riprova\n\n");
                }
            }else{
                if(insert_left(&board, tile)==true){
                    remain--;
                }else{
                    system("clear");
                    printf("mossa non possibile, riprova\n\n");
                }
            }
        }
    }else {
        board= newMatrix(2*n,4*n);
        while(remain>0  && available_moves_2D(&board, deck,remain, n)){ //todo: aggiungere && available moves*/){
            print_screen(&board, deck, remain);
            Tile x= select_tile(deck, remain,n,2);
            if(((x.x=='+' && x.y=='1') || (x.x=='M' && x.y=='R')) && x.orientation=='V'){
                printf("[%c%c] non può essere utilizzata in verticale\n", x.x,x.y);
                continue;
            }
            if(select_pos()=='D'){
                if(insert_right_2D(&board, x)==true){
                    remain--;
                }else{
                    system("clear");
                    printf("mossa non possibile, riprova\n\n");
                }
            }else{
                if(insert_left_2D(&board, x)==true){
                    remain--;
                }else{
                    system("clear");
                    printf("mossa non possibile, riprova\n\n");
                }
            }
        }
    }


    end_game(&board);

    /** operazione di free finale per evitare memory leaks*/
    free(deck);
    free_board(&board);

    return 0;
}
