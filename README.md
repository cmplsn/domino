# Domino
## Progetto di Introduzione alla Programmazione per A.A. 2022/2024

Viene richiesto di implementare il gioco del domino:
 - **Lineare** : tutte le tessere vengono utilizzate in orizzontale
 - **2D**: le tessere possono essere aggiunte sia in orizzontale sia in verticale


### Tessere
In entrambe le modalità ad inizio partità al giocatore vengono assegnate __*n*__ tessere con possibili ripetizioni fra 
queste:

- [11] [12] [13] [14] [15] [16] [22] [23] [24] [25] [26] [33] [34] [35] [36] [44] [45] [46] [55] [56] [66] [MR] [+1] 
[00]
#### Tessere Speciali
 - [00] : può essere posizionata anche a campo di gioco vuoto e in presenza di qualsiasi altra tessera 
 (da considerare come una specie di jolly) [12] **[00]** [66]
 - [+1] : va ad aumentare di 1 tutti i numeri delle tessere già presenti sul campo di gioco ad eccezione di 6 che diventa 1
==> [12][46] **[+1]**  -> [23][51]
 - 


Ogni tessera può essere posizionata sul campo di gioco solo se in presenza di un un numero uguale a quello già presente 
sul campo di gioco oppure in presenza della tessera speciale [00]

