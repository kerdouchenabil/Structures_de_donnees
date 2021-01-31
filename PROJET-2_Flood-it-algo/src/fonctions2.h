#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "api_grille.h"
#include "liste_cases.h"
#include "fonctions.h"
#include "graphe.h"

/*struct permettant de gérer la grille avec un graphe, à tout moment on a les sommets de la zone, la bordure d'une couleur donnée et son nombre de cases*/
typedef struct{
	int dim; //dim de la grille
	int nbcl; //nombre de couleurs
	
	Graphe_zone* G; //le graphe_zone
	
	Cellule_som* Szsg; //Liste des sommets de la zone zsg
	
	Cellule_som** Bordure_g; //Tableau de listes de sommets de la bordure (selon les couleurs)
	
	int* taille_bordure; //tableau du nombre de cases pour chaque couleur dans la Bordure_g (taille de la liste Bordure_g[i])
	
} G_zsg;

/*struct file ou FIFO first IN first OUT*/
typedef struct{
	Cellule_som* last; //pointeur vers le dernier element (pour l'insertion rapide)
	Cellule_som* sommets; //liste des sommets (pointeur vers le premier element)
} File;


/*affiche la struct G_zsg*/
void affiche_zsg(G_zsg* gz);

/*affiche la bordure ainsi que son tableau taille_bordure*/
void affiche_bordure(G_zsg* gz);

/*affiche un tableau donné*/
void affiche_tab(int* tab, int taille);

/*initialise la struct G_zsg*/
G_zsg* init_gzsg(Graphe_zone* G, int dim, int nbcl);

/*detruit la struct G_zsg*/
void detruit_gzsg(G_zsg* gz,int dim);

/*renvoi vrai si le jeu est fini*/
int fin_jeu(G_zsg* gz);

/*cherche le max d'un tableau d'entiers et retourne l'indice*/
int cherche_max(int* tab, int taille);

/*agrandit la zone avec la couleur cl et met à jour la bordure et sa taille_bordure*/
void maj_bordure_g(G_zsg* gz, int cl);

/*strategie se basant sur la struct G_zsg, agrandit la zone intélligement en choisissant la couleur la mieux présente en bordure et retourne le nombre de coups*/
int max_bordure(Graphe_zone* G, int dim, int nbcl, Grille* grille, int aff);


/* ------------------- exo 6 ------------------ */

/*cree une file vide et la retourne*/
File* cree_file();

/*enfile le sommet s dans la file f*/
void enfiler(File* f, Sommet* s);

/*défile un sommet dans f et le retourne*/
Sommet* defiler(File* f);

/*cherche le plus court chemin entre deux sommet et retourne un tableau de couleurs (int) representant le chemin pour aller de racine vers dest*/
int* cherche_chemin(Sommet* racine, Sommet* dest);

/*strategie qui se base aussi sur la struct G_zsg, divise la grille en deux en jouant les couleurs qui font le plus court chemin entre la case superieur gauche et celle du bas droite, puis continue avec le meme principe de max_bordure*/
int parcours_largeur(Graphe_zone* G, int dim, int nbcl, Grille* grille, int aff);




#endif







