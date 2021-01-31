#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "api_grille.h"
#include "liste_cases.h"

/* récursif: Retourne dans L la liste des cases de meme couleur que la case i, j
   et met -1 dans ces cases */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille,
                     ListeCases *L);

/* Algorithme tirant au sort une couleur :
   il utilise la fonction recursive pour determiner la Zsg */
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);


/* ------------------------- exo 2 ----------------------------*/

/* impératif: trouve_zone_rec dérécursifiée */
void trouve_zone_imp(int **M, int dim, int i, int j, int *taille,
                     ListeCases *L);

/* impératif: sequence_aleatoire_rec dérécursifiée */
int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff);


/* ------------------------- exo 3 ----------------------------*/

/*Struct permettant de gerer la zone superieure gauche au cours du jeu*/
typedef struct{
	int dim; //dim de la grille
	int nbcl; //nombre de couleurs
	
	ListeCases Lzsg; //Liste des cases de la zone Zsg
	ListeCases* B; //Tableau de listes de cases de la bordure
	int **App; //matrice des appartenances (0: zsg  1:bordure  2:non visitée)
} S_Zsg;


/* initialise la struct S_Zsg */
S_Zsg* init_zsg(int dim, int nbcl);

/*ajoute la case i,j a la zsg*/
void ajoute_Zsg (S_Zsg * szsg,int i ,int j);

/*ajoute la case i,j a la bordure (selon sa couleur cl)*/
void ajoute_Bordure(S_Zsg* szsg, int i, int j, int cl);

/*renvoi vrai si la case i,j appartient a la zsg*/
int appartient_Zsg(S_Zsg* szsg, int i, int j);

/*renvoi vrai si la case i,j appartient est dans la bordure*/
int appartient_Bordure(S_Zsg* szsg, int i, int j, int cl);

/*agrandit la zsg (un coup joué) avec la couleur cl et met a jour la zsg et bordure. retourne le nombre de cases ajoutées a la zone*/
int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l);

/*lance le jeu en representant la grille avec la struct S_Zsg et agrandit la zone en boucle en tirant les couleurs aléatoirement jusqu'a la fin*/
int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff);




#endif /* FONCTIONS_H */








