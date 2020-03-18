
#ifndef _BIBLIO_H_
#define _BIBLIO_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include <time.h>

typedef struct CellMorceau CellMorceau;

typedef struct Biblio Biblio;

/* Alloue et retourne l'adresse d'une nouvelle Biblio */
Biblio *nouvelle_biblio(void);

/* Charge au plus n morceaux par lecture du fichier nom_fichier */
Biblio *charge_n_entrees(const char *nom_fichier, int n);

/*Libère intégralement la biblio */
void libere_biblio(Biblio *B);

/* Insère le morceau dont les caractéristiques sont num, titre et artiste*/
void insere(Biblio *B, int num, char *titre, char *artiste);

/*Affiche les morceaux contenus dans la Biblio */
void affiche(Biblio *B);

/*Affiche un morceau */
void afficheMorceau(CellMorceau *);

/* Retourne une nouvelle biblio contenant les morceaux de B sans doublons */
Biblio *uniques(Biblio *B);

/* Retourne le seul morceau de numéro num */
CellMorceau * rechercheParNum(Biblio *B, int num);

/* Retourne un morceau de titre titre */
CellMorceau *rechercheParTitre(Biblio *B, char * titre);

/* Retourne une nouvelle biblio qui contient uniquement les morceaux de l'artiste artiste */
Biblio *extraireMorceauxDe(Biblio *B, char * artiste);

/* Réalise l'insertion d'un nouveau morceau (de titre titre et dont le nom de l'interprète est artiste).
   Attention le numéro associé au morceau doit être différent de celui de tous les morceaux 
   présents dans B */
void insereSansNum(Biblio *B, char *titre, char *artiste);

/* Supprime le morceau de numéro num de la Biblio B */
int supprimeMorceau(Biblio *B, int num);

/*recherche par artiste*/
CellMorceau *rechercheParArtiste(Biblio *B, char * artiste, char* titre);


/*---------------  jeux de tests ---------------------*/


	
clock_t temps_initial ; /* Temps initial en micro-secondes */
clock_t temps_final ;
/* Temps final en micro-secondes */
double temps_cpu ;
/* Temps total en secondes */


void temps_rechercheParNum(Biblio *B, int num);

void temps_rechercheParTitre(Biblio *B, char* titre);

void temps_rechercheParArtiste(Biblio *B, char* artiste, char* titre);

void temps_uniques(char* nom_fichier);








#endif








////////////////////////////////////////////////////////// ancien .h
/*
#ifndef biblio_h
#define biblio_h

typedef struct Biblio Biblio;
typedef struct CellMorceau CellMorceau;


void affiche_morceau(CellMorceau* cm);

Biblio *nouvelle_biblio(void);
Biblio *charge_n_entrees(const char *nom_fichier, int n);
void libere_biblio(Biblio *B);

void insere(Biblio *B, int num, char *titre, char *artiste);
void affiche(Biblio *B);
Biblio *uniques(Biblio *B);

CellMorceau* chercher_num(Biblio* B, int n);
CellMorceau* chercher_titre(Biblio* B, char* titre);
Biblio* chercher_artiste(Biblio* B, char* artiste);
Biblio* supprimer_morceau(Biblio* B, CellMorceau* morceau);

#endif

*/

 /* biblio_h */
