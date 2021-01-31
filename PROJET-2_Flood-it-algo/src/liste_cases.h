#ifndef LISTE_CASES_H
#define LISTE_CASES_H

/* Liste simplement chainee de case reperee par les coordonnees entieres i,j */
typedef struct ElementListe {
  int i,j;
  struct ElementListe *suiv;
} ElementListe;

typedef ElementListe* ListeCases;

/* Initialise une liste vide */
void init_liste(ListeCases *L);

/* Ajoute un element en tete de liste */
void ajoute_en_tete(ListeCases *L, int i, int j);

/* teste si une liste est vide */
int test_liste_vide(ListeCases *L);

/* Supprime l element de tete et retourne les valeurs en tete */
/* Attention: il faut que la liste soit non vide */
void enleve_en_tete(ListeCases *L, int *i, int *j);

/* Detruit tous les elements de la liste */
void detruit_liste(ListeCases *L);

#endif /* LISTE_CASES_H */
