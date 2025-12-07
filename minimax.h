/*
Aquest header conté les funcions perquè l'ordenador calculi el millor moviment utilitzant un arbre de moviments (el creem de forma recursiva), la heuristica
(que assigna valors a cada moviment) i l'algorisme del minimax (que permet calcular el millor moviment).
*/

// Estructura que representa un estat del joc
typedef struct node {
	struct node * *fills; // node* fills[N_FILLS] (un vector que guarda les adreçes de memoria dels fills)
	int n_fills; //representa el nombre de fills guardats a *fills
	char tauler[N][N]; //el tauler ple de '0','1','2'
	double valor; //el valor assignat al tauler per la funció heurística
	int jugador; //guardem qui tira després d'este node
} Node;

//Convertim el número de fill a la columna corresponent i la retornem (de 0 a 7)
int calcularColumna(char tauler[N][N], int numDefill);

//Contem i retornem els fills d'un node
int calculaNumFills(Node *node);

// L'objectiu és assignar una puntuació a un tauler de joc (Node* inici) per determinar com de favorable és la situació per al jugador que té el torn.
// El que faig és comptar el numero de 4 en ratlles possibles que podria fer cada jugador com més, més punts.
// Osigue pleno tot el tauler a favor del jugador 1 i tot a favor del jugador 2 i faig la resta dels 4 en ratlles que pot fer cadascú.
// He afegit també donar punts a estar al centre (perquè sinó a l'inici tirava a la 1)
int heuristica (Node* inici);

// Creem un Node i posem quan valen les coses del node
// Recordem la profunditat cada cop que fem un fill disminueix 1 (6-5-4-3-2-1-0) i calcularem heuristica sol a les fulles (profunditat=0)
Node* creaNode(Node *pare,int numDeFill, int profunditat);

//Aquesta funció crea un nivell de l'arbre (creant un node per a cada fill)
void creaNivell(Node *pare, int profunditat);

// Genera els fills immediats del node actual (creaNivell)
// Després fa un bucle per entrar dins de cada fill i repetir el procés recursivament, baixant un pis de profunditat a cada passada.
void crearArbreRec(Node *arrel, int profunditat);

// Recorre recursivament els fills invertint-ne el valor (si és bo per al rival, és dolent per a mi) per trobar la jugada que et dona el màxim benefici.
// Finalment, guarda aquesta millor puntuació al node i retorna l'índex de la columna on has de tirar per aconseguir-la.
int minimax(Node*node);

// Utilitza recursivitat per esborrar l'arbre de baix a dalt
// Buida primer tota la descendència de cada fill abans de fer el free del fill mateix.
// Un cop buits els fills alliberem l'array de punters del node actual i posem p->fills NULL i p->n_fills 0.
void esborraArbre(Node *node);
