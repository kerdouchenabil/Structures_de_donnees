#ifndef _BIBLIO_TAB_DYN_H_
#define _BIBLIO_TAB_DYN_H_

#include "biblio.h"

struct CellMorceau{
    int num;
    char *titre;
    char *artiste;
};

struct Biblio {
    int nE;
    int capacite;
    CellMorceau *T;    
};

/*
Biblio *nouvelle_biblio(void) ;

void libere_morceau(CellMorceau* cm);

void libere_biblio(Biblio *B);

void insere(Biblio *B, int num, char *titre, char *artiste);

void afficheMorceau(CellMorceau *cell);

void affiche(Biblio *B);

CellMorceau * rechercheParNum(Biblio *B, int num);

CellMorceau *rechercheParTitre(Biblio *B, char * titre);

CellMorceau * rechercheParNum_indice(Biblio *B, int num, int* indice);

int supprimeMorceau(Biblio *B, int num);

void insereSansNum(Biblio *B, char *titre, char *artiste);

Biblio *extraireMorceauxDe(Biblio *B, char * artiste);

Biblio *uniques (Biblio *B);
*/

#endif




