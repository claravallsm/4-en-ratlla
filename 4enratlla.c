#include <stdio.h>
#include <stdlib.h>
#include "4enratlla.h"

// Mostra per pantalla l’estat actual del tauler de joc. El tauler és una matriu de '0' (casella buida), '1' (jugador 1) i '2' (jugador 2).
// S'imprimeix posant '0':. '1':X i '2':0 i al final mostra la numeració de les columnes perquè els humans sàpiguen on tirar.
void imprimirTauler(char tauler[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tauler[i][j] == '0') printf(".  ");
            else if (tauler[i][j] == '1') printf("X  ");
            else printf("O  ");
        }
        printf("\n");
    }
    // numeració de columnes
    for (int j = 1; j <= N; j++) printf("%d  ", j);
    printf("\n");
}

// Tira una fitxa del jugador especificat a la columna especificada seguint la gravetat
// Retorna: 1 si la fitxa s'ha pogut colocar correctament i 0 si no s'ha pogut
int tiraFitxa(char tauler[N][N], int jugador, int columna){
    for (int i = N-1 ; i > -1; i--) { // per gravetat primer miro sota de tot
        if (tauler[i][columna-1] == '0') { //poso -1 ja que la columna va de 1 a 8 i a la les columnes de la matriu van de 0 a 7
            if(jugador==1){
                 tauler[i][columna-1] ='1'; //posem la fitxa
            }
            else { //si jugador no és 1 vol dir que és 2
                 tauler[i][columna-1] ='2';
            }
            return 1;
        }
    }
    return 0;
}

// Es gestiona la jugada de l'humà:  demana la columna, valida l’entrada i si és vàlida executa tirafitxa().
// Retorna: El número del jugador que haurà de jugar a continuació (1 o 2) i  és el mateix si la jugada no s’ha pogut realitzar.
int tiraFitxaiCanviJugador(char tauler[N][N], int jugador) {
    int columna;
    printf("Jugador %d, en quina columna vols posar la fitxa (1-%d)? ", jugador, N);
    if (scanf("%d", &columna) != 1) { //scanf conta el número de caracters vàlids
        printf("Entrada no valida.\n");
        while (getchar() != '\n'); // limpiar el buffer fins enter
        return jugador;
    }
    if (columna < 1|| columna > N){
            printf("Numero no valid.\n");
            return jugador;
    }  // columna invàlida pq no estem dintre del tauler
    if(tiraFitxa(tauler, jugador, columna) == 1){  // com tirafitxa retorna 1 si pot tirar la fitxa
        system("cls");
        imprimirTauler(tauler);
        if (jugador == 1) return 2; //canvi de jugador
        else return 1;
    }
    printf("Columna plena! Torna-ho a provar.\n");
    return jugador;
}

// Mira si hi ha un 4 en ratlla vertical a favor del jugador especificat
// He afegit la variable punts per contar els 4 en ratlles a la heuristica.
// Retorna: El nombre de 4 en ratlles verticals
int quatreVertical(char tauler[N][N], int jugador) {
    int punts=0;
    char fitxa;
    if(jugador==1) fitxa='1';
    else fitxa='2';
    for (int i = 0; i < N-3; i++) {  // només fins a N-3 files (començo a la 0 i miro les 3 seguents pos quan miro la 4 miro fins la 7 i iasta)
        for (int j = 0; j < N; j++) {
            if (tauler[i][j] == fitxa &&
                tauler[i+1][j] == fitxa&&
                tauler[i+2][j] == fitxa &&
                tauler[i+3][j] == fitxa) {
                punts++;
            }
        }
    }
    return punts;
}

// Mira si hi ha un 4 en ratlla hortizontal a favor del jugador especificat
// He afegit la variable punts per contar els 4 en ratlles a la heuristica.
// Retorna: El nombre de 4 en ratlles horitzontal
int quatreHoritzontal(char tauler[N][N], int jugador) {
    int punts=0;
    char fitxa;
    if(jugador==1) fitxa='1';
    else fitxa='2';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N-3; j++) { // només fins a N-3 columnes (començo a la 0 i miro les 3 seguents pos quan miro la 4 miro fins la 7 i iasta)
            if (tauler[i][j] == fitxa &&
                tauler[i][j+1] == fitxa &&
                tauler[i][j+2] == fitxa &&
                tauler[i][j+3] == fitxa) {
                punts++;
            }
        }
    }
    return punts;
}

// Mira si hi ha un 4 en ratlla diagonal "\" a favor del jugador especificat
// He afegit la variable punts per contar els 4 en ratlles a la heuristica.
// Retorna: El nombre de 4 en ratlles diagonals "\"
int quatreDiagonal1(char tauler[N][N], int jugador) {
    int punts=0;
    char fitxa;
    if(jugador==1) fitxa='1';
    else fitxa='2';
    for (int i = 0; i < N-3; i++) { //poso N-3 i N-3 perque sino me surtire per la dreta baix
        for (int j = 0; j < N-3; j++) {
            if (tauler[i][j] == fitxa &&
                tauler[i+1][j+1] == fitxa &&
                tauler[i+2][j+2] == fitxa&&
                tauler[i+3][j+3] == fitxa) {
                punts++;
            }
        }
    }
    return punts;
}

// Mira si hi ha un 4 en ratlla diagonal "/" a favor del jugador especificat
// He afegit la variable punts per contar els 4 en ratlles a la heuristica.
// Retorna: El nombre de 4 en ratlles diagonals "/"
int quatreDiagonal2(char tauler[N][N], int jugador) {
    int punts=0;
    char fitxa;
    if(jugador==1) fitxa='1';
    else fitxa='2';
     for (int i = 3; i < N; i++) { //poso a partir de la tercera fila i fins N-3 com sino surto per dreta dalt
        for (int j = 0; j < N-3; j++) {
            if (tauler[i][j] == fitxa  &&
                tauler[i-1][j+1] == fitxa &&
                tauler[i-2][j+2] == fitxa &&
                tauler[i-3][j+3] == fitxa) {
                punts++;}
        }
     }
    return punts;
}

// Retorna el nombre de 4 en ratlles a un tauler a favor d'un jugador especificat
int comptaVictories(char tauler[N][N],int jugador){
    return quatreVertical(tauler,jugador)+quatreHoritzontal(tauler,jugador)+quatreDiagonal1(tauler,jugador)+quatreDiagonal2(tauler,jugador);
}

// Copia el segon tauler al primer tauler (terme a terme)
void copiaTauler(char llocacopiar[N][N],char copiat[N][N]){
    for (int i=0; i<N;i++){
        for (int j=0; j<N;j++){
        llocacopiar[i][j]=copiat[i][j];
        }
    }
}
