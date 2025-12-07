/*
Aquest header conté totes les funcions bàsiques per jugar al 4 en ratlla hi ha funcions per fer moviments, copiar taulers, comprovar victòries
i imprimir taulers.
*/
#define N 8 //aquest és el nombre de peçes per cada fila i cada columna del tauler del 4 en ratlla

// Mostra per pantalla l’estat actual del tauler de joc. El tauler és una matriu de '0' (casella buida), '1' (jugador 1) i '2' (jugador 2).
// s'imprimeix posant '0':. '1':X i '2':0 i al final mostra la numeració de les columnes perquè els humans sàpiguen on tirar.
void imprimirTauler(char tauler[N][N]);

// Tira una fitxa del jugador especificat a la columna especificada seguint la gravetat
// Retorna: 1 si la fitxa s'ha pogut colocar correctament i 0 si no s'ha pogut
int tiraFitxa(char tauler[N][N], int jugador, int columna);

// Es gestiona la jugada de l'humà:  demana la columna, valida l’entrada i si és vàlida executa tirafitxa().
// Retorna: El número del jugador que haurà de jugar a continuació (1 o 2) i  és el mateix si la jugada no s’ha pogut realitzar.
int tiraFitxaiCanviJugador(char tauler[N][N], int jugador);

// Mira si hi ha un 4 en ratlla vertical a favor del jugador especificat
// He afegit la variable punts per contar els 4 en ratlles a la heuristica.
// Retorna: El nombre de 4 en ratlles verticals
int quatreVertical(char tauler[N][N], int jugador);

// Mira si hi ha un 4 en ratlla hortizontal a favor del jugador especificat
// He afegit la variable punts per contar els 4 en ratlles a la heuristica.
// Retorna: El nombre de 4 en ratlles horitzontals
int quatreHoritzontal(char tauler[N][N], int jugador);

// Mira si hi ha un 4 en ratlla diagonal "\" a favor del jugador especificat
// He afegit la variable punts per contar els 4 en ratlles a la heuristica.
// Retorna: El nombre de 4 en ratlles diagonals "\"
int quatreDiagonal1(char tauler[N][N], int jugador);

// Mira si hi ha un 4 en ratlla diagonal "/" a favor del jugador especificat
// He afegit la variable punts per contar els 4 en ratlles a la heuristica.
// Retorna: El nombre de 4 en ratlles diagonals "/"
int quatreDiagonal2(char tauler[N][N], int jugador);

// Retorna el nombre de 4 en ratlles a un tauler a favor d'un jugador especificat
int comptaVictories(char tauler[N][N], int jugador);

// Copia el segon tauler al primer tauler (terme a terme)
void copiaTauler(char llocacopiar[N][N],char copiat[N][N]);
