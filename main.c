#include "board.c"



int main() {
    int n = choose_valid_n();
    /*todo: scelgo numero di tessere con cui inizia il gioco*/
    Tile* tessere_giocatore = assegna(n);
    Matrix board;
    if(select_mode()==1){
        board= newMatrix(1,n*4);

    }else{
        board= newMatrix(2*n,4*n);
    }

    //tessere_giocatore[n-1].x='+'; tessere_giocatore[n-1].y='1';
    int remain=n;

    while(remain>0){
        print_hand(tessere_giocatore,remain);
        Tile x = select_tile(tessere_giocatore,remain,n);
        char pos;
        pos=select_pos();
        char* tile= tile_to_horizontal(x);
        if(pos=='D'){
            insert_right(&board, tile, board.cols);
        }else if(pos=='S'){
            //insert_left(&board,tile);
        }

        free(tile);

        print_board(&board);

        remain--;
    }

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
