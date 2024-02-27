//
// Created by Alessandro on 13/02/24.
//

#ifndef PROJECT_IAP_PLAYER_H
#define PROJECT_IAP_PLAYER_H

#include <time.h>
/*int** assegna(int n){
    int** deck=(int**)malloc(n* sizeof(int*));
    for (int i = 0; i < n; ++i) {
        deck[i]= (int*) malloc(2* sizeof(int));
    }

    int tessere [23][2]={{1,1},{1,2},{1,3},{1,4},{1,5},
                         {1,6},{2,2},{2,3},{2,4},{2,5},
                         {2,6},{3,3},{3,4},{3,5},
                         {3,6},{4,4},{4,5},{4,6},
                         {5,5},{5,6},{6,6},
                         {12,21},{11,11}};

    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        int x=rand()%23;
        deck[i][0]=tessere[x][0];
        deck[i][1]=tessere[x][1];
    }
    return deck;
}*/

int* assegna_tessere(int n){
    int* deck= malloc(n*sizeof(int));

    int tessere[23]={11,12,13,14,15,16,22,23,24,25,26,
                     33,34,35,36,44,45,46,55,56,66,1111,1221};


    srand(time(NULL));  //todo: seeding di rand ogni esecuzione crea una diversa sequenza di indici randomici.
                        // senza questa istruzione la sequenza random generata è sempre la stessa.

    for (int i = 0; i < n; i++) { //todo: popolo il deck del giocatore con n tessere (con rep) scelte casualmente
        int x=rand()%23;
        deck[i]=tessere[x];
    }

    return deck;
}

void mostra_tessere(int* deck, int n){ //todo: print formattato come [xy] delle tessere nel deck del giocatore
    for (int i = 0; i < n; i++) {
        printf("[%d] ",deck[i]);
    }
    printf("\n");
}

int choose_valid_n(){
    printf("scegliere numero tessere con cui giocare:\n");
    int n;
    int res=scanf("%d",&n);
    while(res!=1 || n<1 || n>256){
        printf("NON VALIDO. Inserisci input nel formato richiesto:\n");
        res= scanf("%d",&n);
    }
    printf("si è scelto di giocare con -- %d -- tessere\n",n);
    return n;
}

void free_deck(int* deck,int n){
    free(deck);
}

#endif //PROJECT_IAP_PLAYER_H
