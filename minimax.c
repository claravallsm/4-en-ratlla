#include <stdio.h>
#include <stdlib.h>
#include "4enratlla.h"
#include "minimax.h"
// Convertim el número de fill a la columna corresponent i la retornem (de 0 a 7)
int calcularColumna(char tauler[N][N], int numDefill) {
    int columnes_buides[N]; //ens guardarem aqui els numeros de les columnes buides
    int n_buides = 0;
    //per vore si una columna esta plena sol cal mirar si està lliure dalt de tot
    for (int i = 0; i < N; i++) {
        if (tauler[0][i] == '0') {
            columnes_buides[n_buides] = i;
            n_buides++;
        }
    }
    return  columnes_buides[numDefill];
}

//Contem i retornem els fills d'un node
int calculaNumFills(Node *node){
    int n=0;
    for(int i=0;i<N;i++){
        if(node->tauler[0][i]=='0'){ // miro si les caselles de dalt estan buides
        n++;}
    }
   return n;
}

// L'objectiu és assignar una puntuació a un tauler de joc (Node* inici) per determinar com de favorable és la situació per al jugador que té el torn.
// El que faig és comptar el numero de 4 en ratlles possibles que podria fer cada jugador com més, més punts.
// Osigue pleno tot el tauler a favor del jugador 1 i tot a favor del jugador 2 i faig la resta dels 4 en ratlles que pot fer cadascú.
// He afegit també donar punts a estar al centre
int heuristica (Node* inici){

    int puntsjugador1=0; int puntsjugador2=0;

    int pesColumnes[N] = {1, 2, 3, 6, 6, 3, 2, 1};
   //  int pesColumnes[N] = {1, 2, 3, 6, 3, 2, 1}; cas N=7
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
        if(inici->tauler[i][j] == '1')  puntsjugador1 += pesColumnes[j];
        if(inici->tauler[i][j] == '2')  puntsjugador2 += pesColumnes[j];
        }
    }
    char taulerjugador1[N][N]; char taulerjugador2[N][N];
    copiaTauler(taulerjugador1,inici->tauler); //fem una copia sinó modificarem inici->tauler i serà un desastre!
    copiaTauler(taulerjugador2,inici->tauler);
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if(taulerjugador1[i][j]=='0'){
                taulerjugador1[i][j]='1';
                taulerjugador2[i][j]='2';
            }

        }
    }
    puntsjugador1 += comptaVictories(taulerjugador1,1);
    puntsjugador2 += comptaVictories(taulerjugador2,2);
    if(inici->jugador==1)return  puntsjugador1-puntsjugador2; //heuristica personalitzada (aixi al minimax sempre faig màxims)
    else return puntsjugador2-puntsjugador1;
}

// Creem un Node i posem quan valen les coses del node
// Recordem la profunditat cada cop que fem un fill disminueix 1 (6-5-4-3-2-1-0) i calcularem heuristica sol a les fulles (profunditat=0)
Node* creaNode(Node *pare,int numDeFill, int profunditat) {
	Node *p= malloc(sizeof(Node));
	p->valor=0; //inicialitzo a 0
	copiaTauler(p->tauler,pare->tauler); //pq sinó modificariem lo del pare!
    tiraFitxa(p->tauler, pare->jugador,calcularColumna(p->tauler,numDeFill) + 1); //el +1 ve de que calculacolumna() va de 0 a 7, i tirafitxa() de 1 a 8
    p->jugador = 3 - pare->jugador; // Canvi de torn (si pare->jugador 2=> p-jugador=1 i viceversa)
	//si trobem una SOLUCIÓ ACABEM!!
    if(comptaVictories(p->tauler,pare->jugador) > 0){
        p->valor = -10000-profunditat; //això és perquè l'heuristica és personalitzada, pel punt de vista del p és molt dolent
        //si té mes profunditat vull que acabi antes
        p->n_fills = 0;
        p->fills = NULL;
        return p;
    }
     //nomes mirem la heuristica baix de tot
	if (profunditat>0){
        p->n_fills=calculaNumFills(p);
        p->fills=malloc( p->n_fills * sizeof(Node*));
        return p;
	}
	else{
        p->valor=heuristica(p);
        p->n_fills=0;
        p->fills=NULL;
        return p;
    }
}

// Aquesta funció crea un nivell de l'arbre (creant un node per a cada fill)
void creaNivell(Node *pare, int profunditat) {
	for(int i=0 ; i<pare->n_fills ; i++) {
		pare->fills[i] = creaNode(pare,i, profunditat);
	}
}

// Genera els fills immediats del node actual (creaNivell)
// Després fa un bucle per entrar dins de cada fill i repetir el procés recursivament, baixant un pis de profunditat a cada passada.
void crearArbreRec(Node *arrel, int profunditat){
    creaNivell(arrel,profunditat-1);
    for(int i=0 ; i<arrel->n_fills ; i++) {
        crearArbreRec(arrel->fills[i],profunditat-1);
    }
}

//Recorre recursivament els fills invertint-ne el valor (si és bo per al rival, és dolent per a mi) per trobar la jugada que et dona el màxim benefici.
//Finalment, guarda aquesta millor puntuació al node i retorna l'índex de la columna on has de tirar per aconseguir-la.
int minimax(Node*node){ //no cal pasar la profunditat perque a profunditat 0 n_fills és 0 (fet al crear el node)
    if(node->n_fills==0){ //primer executarem la creació de l'arbre, i alli a les fulles poso el valor de la  heuristica
        return -1;
    }
    minimax(node->fills[0]);
    double max=-node->fills[0]->valor; //inicialitzem el maxim, menos perque canvia el punt de vista de jugador i aixi sempre faig maxims
    int millorfill=0;
    for(int i=1;i<node->n_fills;i++){
        minimax(node->fills[i]);
        double v=-node->fills[i]->valor;
        if(v>max){
            max=v;
            millorfill=i;
        }

    }
    node->valor=max;
    return millorfill;
}

// Utilitza recursivitat per esborrar l'arbre de baix a dalt
// Buida primer tota la descendència de cada fill abans de fer el free del fill mateix.
// Un cop buits els fills alliberem l'array de punters del node actual i posem p->fills NULL i p->n_fills 0.
void esborraArbre(Node *node){ // (p mai es null per hipotesis)
   if (node->n_fills==0) return; //pq no peti al fer free p->fills, return; la funció acaba aqui
    for (int i = 0; i < node->n_fills; i++){
        esborraArbre(node->fills[i]);  // primer destruim el contingut dels fills
        free(node->fills[i]); //borro els fills un per un
    }
    free(node->fills); // borro les adreçes de memòria dels fills
    node->fills = NULL;
    node->n_fills = 0;
}
