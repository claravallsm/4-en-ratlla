# 4 en Ratlla: IA amb Algorisme Minimax
Aquest projecte és una implementació completa en C del clàssic joc d'estratègia 4 en Ratlla. El programari permet partides entre dos jugadors humans o contra una Intel·ligència Artificial (IA) basada en l'algorisme **Minimax**, capaç de calcular moviments òptims mitjançant un arbre de decisions recursiu i una avaluació heurística personalitzada.

# Característiques Principals:
* Tauler: Joc desenvolupat sobre una matriu de dimensions $8 \times 8$ (constant `N=8`).
* Modes de Joc:
    *  Humà vs. Humà: Mode local per a dos jugadors.
       Humà vs. Màquina: Repte contra la IA amb selecció de torn inicial.
* **Dificultat Adaptativa:** Selecció de la profunditat de l'arbre de cerca de la IA:
    * *Fàcil:* Profunditat 2.
    * *Mitjana:* Profunditat 4.
    * *Difícil:* Profunditat 6.

# Instal·lació i Compilació
El projecte està dissenyat per ser compilat amb `gcc`. Segueix els passos següents per construir l'executable:
1.  Clona el repositori o descarrega els fitxers font.
2.  Obre la terminal al directori del projecte.
3.  Executa la següent comanda de compilació:
gcc main.c 4enratlla.c minimax.c -o 4enratlla
I executa'l a Windows fent: 4enratlla.exe
A Linux/Mac fent: ./4enratlla
