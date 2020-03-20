#ifndef _BIBLIO_ARBRE_LEX_H_
#define _BIBLIO_ARBRE_LEX_H_

#include "biblio.h"

struct CellMorceau{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};


typedef struct Noeud {
    struct Noeud *liste_car;
    struct Noeud *car_suiv;
    CellMorceau *liste_morceaux;
    char car;
} Noeud;


struct Biblio {
    int nE;
    Noeud *A;
};

/*
void afficheMorceau(CellMorceau *cell);

void affiche_Noeud(Noeud * A);

Noeud *  recherche_ou_cree_artiste ( Biblio *B , char * artiste );

void insere(Biblio *B, int num, char *titre, char *artiste);

Biblio *nouvelle_biblio(void);

Biblio *extraireMorceauxDe(Biblio *B, char * artiste);

Noeud *  recherche_ou_cree_artiste ( Biblio *B , char * artiste );

void libere_biblio(Biblio *B);

void insereSansNum(Biblio *B, char *titre, char *artiste);

CellMorceau * rechercheParNum(Biblio *B, int num);

*/


#endif
