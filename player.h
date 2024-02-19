//
// Created by Alessandro on 13/02/24.
//

#ifndef PROJECT_IAP_PLAYER_H
#define PROJECT_IAP_PLAYER_H

#include <time.h>

int* assegna_tessere(int n){
    int* deck= malloc(n*sizeof(int));

    int tessere[21]={11,12,13,14,15,16,22,23,24,25,26,
                     33,34,35,36,44,45,46,55,56,66};

    srand(time(NULL));  //todo: seeding di rand ogni esecuzione crea una diversa sequenza di indici randomici.
                        // senza questa istruzione la sequenza random generata è sempre la stessa.

    for (int i = 0; i < n; i++) { //todo: popolo il deck del giocatore con n tessere (con rep) scelte casualmente
        int x=rand()%21;
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

void free_deck(int* deck){
    free(deck);
}

#endif //PROJECT_IAP_PLAYER_H
