#ifndef GRAPHE_H
#define GRAPHE_H
#include "api_grille.h"
#include<stdlib.h>
#include<stdio.h>
#include "liste_cases.h"
#include"fonctions.h"
typedef struct sommet Sommet ;

/* Element d’une liste cha\^in\’ee de pointeurs sur Sommets */
typedef struct cellule_som {
	Sommet * sommet ;
	struct cellule_som * suiv ;
} Cellule_som ;

/*un sommet represente un certain nombre de cases adjacentes de meme couleur (une zone)*/
struct sommet {
	int num ; /* Numero du sommet (sert uniquement a l’affichage) */
	int cl ; /* Couleur d’origine du sommet-zone */
	ListeCases cases ; /* Listes des cases du sommet-zone */
	int nbcase_som ; /* Nombre de cases de cette liste */

	Cellule_som * sommet_adj ; /* Liste des ar\eteses pointeurs sur les sommets
	adjacents */
	
	/* exo 5 */
	int marque; // 0=dans zoneSG ; 1=dans bordure ; 2=non visité

	/* exo 6 */
	int distance ; /* Nombre d’aretes reliant ce sommet a la racine du parcours en largeur */
	Sommet* pere ; /* Pere du sommet dans l’arborescence du parcours en largeur */
};

/*le graphe servira a representer la grille*/
typedef struct graphe_zone {
	int nbsom ; /* Nombre de sommets dans le graphe */
	Cellule_som * som ; /* Liste chainee des sommets du graphe */
	Sommet *** mat ; /* Matrice de pointeurs sur les sommets indiquant a quel sommet appartient une case (i,j) de la grille */
} Graphe_zone;


/*affiche un graphe*/
void affiche_graphe(Graphe_zone *G);

/*retourne vrai si la case ne sort pas de la grille*/
int dans_grille2(int dim, int i, int j);

/*crée un sommet en initialisant ses parametres donnés et retourne son pointeur*/
Sommet * cree_sommet(int num ,int cl ,ListeCases * l, int nbcase_som, Cellule_som* sommet_adj);

/*ajoute le sommet s a la liste csm*/
void ajoute_liste_sommet(Cellule_som * csm,Sommet * s);

/*detruit une liste de sommets*/
void detruit_liste_sommet(Cellule_som * csm);

/*ajoute s1 dans la liste des voisins de s2 et ajoute s2 dans les voisins de s1*/
void ajoute_voisin(Sommet *s1,Sommet *s2);

/*retourne vrai si deux sommets sont adjacents*/
int adjacent(Sommet *s1,Sommet *s2);

/*detruit un sommet*/
void detruit_sommet(Sommet * s);

/*detruit le graphe*/
void detruit_graphe(Graphe_zone * gr,int dim);

/*cree un graphe_zone selon une matrice donnée et le retourne*/
Graphe_zone * cree_graphe_zone(int **M, int dim);






#endif







