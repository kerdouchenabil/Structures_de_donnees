#include "liste_cases.h"

#include <stdlib.h>

/* Initialise une liste vide */

void init_liste(ListeCases *L) {
  *L = NULL;
}

/* Ajoute un element en tete de liste */
void ajoute_en_tete(ListeCases *L, int i, int j) {
  ElementListe *element;
  element = malloc(sizeof(*element));
  if(element == NULL) {
    exit(1);
  }
  element->suiv = *L;
  element->i = i;
  element->j = j;
  *L = element;
}

/* teste si une liste est vide */
int test_liste_vide(ListeCases *L) {
  return (*L) == NULL;
}

/* Supprime l element de tete et retourne les valeurs en tete */
/* Attention: il faut que la liste soit non vide */
void enleve_en_tete(ListeCases *L, int *i, int *j) {
  ElementListe *temp;
  *i = (*L)->i;
  *j = (*L)->j;
  temp = *L;
  *L = (*L)->suiv;
  free(temp);
}

/* Detruit tous les elements de la liste */
void detruit_liste(ListeCases *L) {
  ElementListe *cour,*temp;
  cour = *L;
  while(cour != NULL) {
    temp = cour;
    cour = cour->suiv;
    free(temp);
  }
  *L = NULL;
}
