#include "player.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    system("clear");

    int n = choose_valid_n();
    //todo: scelgo numero di tessere con cui inizia il gioco

    Tile* deck = assegna(n);
    /*deck[0].x='M'; deck[0].y='R';
    deck[1].x='+'; deck[1].y='1';*/


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
        while(remain>0  /* && available_move_2D todo: aggiungere && available moves*/){
            print_screen(&board, deck, remain);
            Tile x= select_tile(deck, remain,n,2);
            if(x.x=='+' && x.y=='1' && x.orientation=='V'){
                printf("[+1] non può essere utilizzata in verticale\n");
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
