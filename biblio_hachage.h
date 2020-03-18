#ifndef _BIBLIO_HACHAGE_H_
#define _BIBLIO_HACHAGE_H_

#include "biblio.h"
#include <math.h>

#define TAILLE_TABLE 600000
#define A 0.6180339887498949


typedef struct CellMorceau {
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
    unsigned int cle;
} CellMorceau;


struct Biblio {
    int nE;
    int m;
    CellMorceau **T;    
};


unsigned int fonctio__cle(const char *artiste);

int h(int k);

unsigned int fonction_hachage(unsigned int cle, int m);

Biblio *nouvelle_biblio(void) ;

void libere_un_morceau(CellMorceau * cm );

void libere_biblio(Biblio *B);

void insere(Biblio *B, int num, char *titre, char *artiste);

void afficheMorceau(CellMorceau *cell);

void affiche(Biblio *B);

CellMorceau * rechercheParNum(Biblio *B, int num);

CellMorceau *rechercheParTitre(Biblio *B, char * titre);

Biblio *extraireMorceauxDe(Biblio *B, char * artiste);

void insereSansNum(Biblio *B, char *titre, char *artiste);

int supprimeMorceau(Biblio *B, int num);

Biblio *uniques (Biblio *B);








#endif
