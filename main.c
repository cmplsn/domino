#include "player.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>



int main(void) {
    system("clear");
    int n = choose_valid_n();
    /*todo: scelgo numero di tessere con cui inizia il gioco*/
    Tile* tessere_giocatore = assegna(n);
    tessere_giocatore[n-1].x='M';tessere_giocatore[n-1].y='R';
    Matrix board;
    int remain=n;
    if(select_mode()==1){
        board= newMatrix(1,n*4);
        while(remain>0 && available_moves_linear(&board, tessere_giocatore,remain, n)){
            /*if(!available_moves_linear(&board, tessere_giocatore, remain,n)){
                remain=0;
                break;
            }*/
            printf("Score: %d\n", get_score(&board));
            print_board(&board);
            print_hand(tessere_giocatore,remain);
            Tile x= select_tile(tessere_giocatore,remain,n);
            char* tile= tile_to_horizontal(x);
            if(select_pos()=='D'){
                if (insert_right(&board,tile,remain,n)==true){
                    remain--;
                }else{
                    system("clear");
                    printf("mossa non possibile, riprova\n\n");
                }
            }else{
                if(insert_left(&board, tile, remain, n)==true){
                    remain--;
                }else{
                    system("clear");
                    printf("mossa non possibile, riprova\n\n");
                }
            }
            free (tile);
        }
    }else{
        board= newMatrix(2*n,4*n);
        while(remain>0){

            remain--;
        }
    }


    end_game(&board);


    /*while(remain>0){
        if(!available_moves_linear(&board, tessere_giocatore, remain,n)){
            remain=0;
            system("clear");
            printf("GAME OVER\n");
            print_board(&board);
            printf("il tuo punteggio finale è: %d\n", get_score(&board));
            break;
        }
        printf("Score: %d\n", get_score(&board));
        print_board(&board);
        print_hand(tessere_giocatore,remain);
        Tile x= select_tile(tessere_giocatore,remain,n);
        char* tile= tile_to_horizontal(x);
        if(select_pos()=='D'){
            if (insert_right(&board,tile,remain,n)==true){
                remain--;
            }else{
                system("clear");
                printf("mossa non possibile, riprova\n\n");
            }
        }else{
            if(insert_left(&board, tile, remain, n)==true){
                remain--;
            }else{
                system("clear");
                printf("mossa non possibile, riprova\n\n");
            }
        }
        free (tile);
    }*/

    /*if(x.orientation=='O'){
        char* a =tile_to_horizontal(x);
    }else if(x.orientation=='V'){
        char** b= tile_to_vertical(x);
    }*/


    /*todo: operazione di free finale per evitare memory leaks*/
    free(tessere_giocatore);
    free_board(&board);

    return 0;
}
