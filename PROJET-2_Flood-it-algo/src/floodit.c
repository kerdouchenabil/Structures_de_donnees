#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "api_grille.h"
#include "api_genere_instance.h"

#include "graphe.h"
#include "fonctions2.h"

int main(int argc, char *argv[]) {
  clock_t temps_initial;  /* Temps initial en micro-secondes */
  clock_t temps_final;    /* Temps final en micro-secondes */
  float temps_cpu;        /* Temps total en secondes */
 
  if(argc != 7) {
    printf("Usage:%s  dim  nbCouleurs  difficulte  graine  Strategie:1|2|3|4|5|6  aff:0|1\n", argv[0]);
    return 1;
  }

  int dim = atoi(argv[1]);
  int nbcl = atoi(argv[2]);
  int nivdif = atoi(argv[3]);
  int graine = atoi(argv[4]);
  
  int strategie = atoi(argv[5]);  /*-- modifications choisir strategie et affichage --*/
  int aff = atoi(argv[6]);

  /* Generation de l'instance */
  int **M = malloc(dim * sizeof(*M));
  if(M == NULL) {
    exit(1);
  }

  int i;
  for(i = 0; i < dim; i++) {
    M[i] = malloc(dim * sizeof(*M[i]));
    if(M[i] == NULL) {
      exit(1);
    }
  }

  gi_genere_matrice(dim, nbcl, nivdif, graine, M);

  /* Affichage de la grille */

  Grille *G = grille_init(dim,nbcl, 500);

  grille_ouvre_fenetre(G);

  for(i = 0;i<dim;i++) {
    int j;
    for(j = 0; j < dim; j++) {
      grille_attribue_couleur_case(G, i, j, M[i][j]);
    }
  }
  grille_redessine(G);
  
  
  /* Floodit partie 2: choix de strategies différentes */
  int cpt=0;
  Graphe_zone* gr=NULL;
  temps_initial = clock();

  /* exo4 */
  if(strategie >= 4){
	  printf("Creation du graphe \n");
	  gr = cree_graphe_zone(M,dim);
	  if(aff)affiche_graphe(gr);
  }
  
  /* exo 5 */
  if(strategie == 5){
  	  printf("Strategie max_bordure_________________________ \n");
	  cpt = max_bordure(gr, dim, nbcl, G, aff);
	  printf("cpt= %d\n",cpt);
  }

  /* exo6 */
  if(strategie == 6){
  	  printf("Strategie parcours_largeur_________________________ \n");
	  cpt = parcours_largeur(gr, dim, nbcl, G, aff);
	  printf("cpt= %d\n",cpt);
  }
  
  /* partie 1 de FloodIt */
  /* exo 1 */
  if(strategie == 1) {
    printf("cpt= %d essais recursifs,  ", sequence_aleatoire_rec(M, G, dim, nbcl, aff));
  }
  
  /* exo 2 */
  if(strategie == 2) {
    printf("cpt= %d essais imperatifs,  ", sequence_aleatoire_imp(M, G, dim, nbcl, aff));
  }
  
  /* exo3 */
  if(strategie == 3) {
    printf("cpt= %d essais rapides,  ", sequence_aleatoire_rapide(M, G, dim, nbcl, aff));
  }
  
  /*calcul du temps*/
  temps_final = clock();
  temps_cpu = (temps_final - temps_initial) * 1e-6;
  printf("Temps = %f \n\n", temps_cpu);

  
//-------------------------------------------------------------------//	
  grille_attente_touche();
  grille_ferme_fenetre(G);
  grille_free(G);

  return 0;
}












