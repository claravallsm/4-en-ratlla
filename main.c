#include <stdio.h>
#include <stdlib.h>
#include "4enratlla.h"
#include "minimax.h"

int main(void) {
    int n=0,opcio;
    printf("Com vols jugar?\n");
    printf("1: Dos persones (Huma vs Huma)\n");
    printf("2: Contra l'ordinador (Huma vs Maquina)\n");
    printf("Selecciona una opcio (1 o 2): ");
    scanf("%d", &opcio);
    if (opcio == 1) { //huma contra humà
        char tauler [N][N]; //incialitzem el tauler
        for (int i=0;i<N;i++){
             for (int j=0;j<N;j++){
                    tauler[i][j]='0';
            }
        }
        imprimirTauler(tauler);
        int jugador=1; //spg comença el jugador 1
        while(n<64){
            int jugadoractual=jugador; //hem guardo el jugador que tira perque al tirar se canvia de jugador i vull mirar l'altre
            jugador=tiraFitxaiCanviJugador(tauler,jugador);
            if(jugadoractual!=jugador) n++;
            if(comptaVictories(tauler,jugadoractual)>=1){
                printf("Ha guanyat el jugador %d",jugadoractual);
                break;
            }
        }
        if(n==64) printf("Ha hagut un empat");
        return 0;
    }
    else if (opcio == 2) {
        int columna;
        Node *arrel = malloc(sizeof(Node));
        arrel->fills = NULL;
        arrel->n_fills = 0;
        for(int i=0;i<N; i++) {
            for (int j = 0; j < N; j++) { //fico tot 0 al inici de la matriu
                arrel->tauler[i][j]='0';
            }
        }
        printf("Qui vols que comence? \n");
        printf("1: L'huma \n");
        printf("2: La maquina \n");
        printf("Selecciona una opcio (1 o 2): ");
        scanf("%d", &arrel->jugador);
        if(arrel->jugador!=1 && arrel->jugador!=2)printf("Opcio no valida") ;
        int dificultat,profunditat;
        printf("Quina dificultat vols?\n");
        printf("1:facil \n");
        printf("2:mitja \n");
        printf("3 dificil \n");
        printf("Selecciona una opcio (1, 2 o 3): ");
        scanf("%d", &dificultat);
        if(dificultat==1) profunditat=2;
        if(dificultat==2) profunditat=4;
        if(dificultat==3) profunditat=6;
        else printf("Opcio no valida");
        imprimirTauler(arrel->tauler);
        while(n<64){
            int jugadoractual=arrel->jugador; //hem guardo el jugador que tira perque al tirar (en tirafitxaicanvijugador) se canvia de jugador i vull mirar l'altre
            if(arrel->jugador==1){
                arrel->jugador=tiraFitxaiCanviJugador(arrel->tauler,arrel->jugador);
                if(arrel->jugador!=1) n++;
                system("cls"); //netejo la pantalla antes de imprimir lo nou tauler
                imprimirTauler(arrel->tauler);
            } //tira la fitxa la persona
            else {
                n++;
                esborraArbre(arrel);  // abans de reconstruir l'arbre, esborrem l'anterior
                arrel->n_fills=calculaNumFills(arrel);
                arrel->fills=malloc( arrel->n_fills * sizeof(Node*));
                crearArbreRec(arrel,profunditat); //valors heuristica sol a les fulles
                int m=minimax(arrel); //aqui sassignen els valors de cada node de l'arbre
                int columna=calcularColumna(arrel->tauler,m); //cal calcular la columna real ja que el minimax ens dona el numero de fill
                tiraFitxa(arrel->tauler, arrel->jugador, columna+1); //a l'hora de tirar poso columna-1!!
                arrel->jugador=1;
                system("cls");
                imprimirTauler(arrel->tauler);
                printf("\nLa maquina tira a la columna %d\n", columna+1);
            }
            if( comptaVictories(arrel->tauler,jugadoractual)>=1 ){  //notem que la funcio valia >=1 quan algu guanyava
                if(jugadoractual==1){
                    printf("Ha guanyat l'huma");
                    break;
                }
                else {
                    printf("Ha guanyat la maquina");
                    break;
                }
            }
    }
    free(arrel);
    if(n==64) printf("Ha hagut un empat");
    return 0;
    }
    else {
        printf("\nError: Opcio no valida.\n");
        return 1; // sortim amb error
    }
}
