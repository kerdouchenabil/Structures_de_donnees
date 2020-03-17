#ifndef _BIBLIO_LISTE_H_
#define _BIBLIO_LISTE_H_

#include "biblio.h"


struct CellMorceau{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};

struct Biblio {
    CellMorceau *L;
    int nE;
};

/*
void affiche_morceau(CellMorceau* cm);

void affiche(Biblio* B);

void libere_biblio(Biblio *B);

Biblio *nouvelle_biblio(void);

void insere(Biblio *B, int num, char *titre, char *artiste);

CellMorceau* chercher_num(Biblio* B, int n);

CellMorceau* chercher_titre(Biblio* B, char* titre);

Biblio* chercher_artiste(Biblio* B, char* artiste);

Biblio* supprimer_morceau(Biblio* B, CellMorceau* morceau);

Biblio *uniques(Biblio *B);
*/




#endif
