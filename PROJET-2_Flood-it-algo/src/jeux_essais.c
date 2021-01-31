#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "api_grille.h"
#include "api_genere_instance.h"

#include "graphe.h"
#include "fonctions2.h"
int cherche_max2(int* tab, int taille){
	int max=tab[0];
	int ind=0;
	for(int i=0; i<taille; i++){
		if(tab[i]>max){
			max=tab[i];
			ind=i;
		}
	}
	tab[ind] = -1;
	return ind;
}

int main(int argc, char *argv[]) {
  clock_t temps_initial;  /* Temps initial en micro-secondes */
  clock_t temps_final;    /* Temps final en micro-secondes */
  float temps_cpu;        /* Temps total en secondes */
 
  if(argc != 5) {
    printf("Usage:%s  dim  nbCouleurs  difficulte  graine  \n", argv[0]);
    return 1;
  }

  int dim = atoi(argv[1]);
  int nbcl = atoi(argv[2]);
  int nivdif = atoi(argv[3]);
  int graine = atoi(argv[4]);
  


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
  
  float * temps = malloc(5*sizeof(float));
  int * coups = malloc(5*sizeof(int));
  /* Floodit partie 2: choix de strategies différentes */

  Graphe_zone* gr=NULL;
  temps_initial = clock();
  temps_final = clock();
  temps_cpu = (temps_final - temps_initial) * 1e-6;
  printf("Temps = %f \n\n", temps_cpu);

  /* exo4 */
   	  temps_initial = clock();
	  printf("Creation du graphe \n");
	  gr = cree_graphe_zone(M,dim);
	  //if(aff)affiche_graphe(gr);
 	  temps_final = clock();
	  float creegraphe = (temps_final - temps_initial) * 1e-6;
  	  printf("temps cree graphe = %f \n\n",creegraphe);
  
  /* exo 5 */
	  temps_initial = clock();
  	  printf("Strategie max_bordure_________________________ \n");
	  coups[3] = max_bordure(gr, dim, nbcl, G, 0);
  	  temps_final= clock();
	  temps[3]=(temps_final - temps_initial) * 1e-6 + creegraphe;

  /* exo6 */
	
	gi_genere_matrice(dim, nbcl, nivdif, graine, M);
	Graphe_zone* gre = cree_graphe_zone(M,dim);
  	  temps_initial= clock();
  	  printf("Strategie parcours_largeur_________________________ \n");
	  coups[4] = parcours_largeur(gre, dim, nbcl, G, 0);
	  temps_final = clock();
  	  temps[4]=(temps_final - temps_initial) * 1e-6 + creegraphe;
  
  /* partie 1 de FloodIt */
  /* exo 1 */
 	 gi_genere_matrice(dim, nbcl, nivdif, graine, M);
  	 temps_initial=clock();
     	 coups[0]=sequence_aleatoire_rec(M, G, dim, nbcl, 0);
  	 temps_final=clock();
	 temps[0]=(temps_final - temps_initial) * 1e-6 ;
  
  /* exo 2 */
	gi_genere_matrice(dim, nbcl, nivdif, graine, M);
  	 temps_initial=clock();
     coups[1]=sequence_aleatoire_imp(M, G, dim, nbcl, 0);
  	 temps_final=clock();
	 temps[1]=(temps_final - temps_initial) * 1e-6 ;
  
	  /* exo3 */
	gi_genere_matrice(dim, nbcl, nivdif, graine, M);
  	 temps_initial=clock();
         coups[2]=sequence_aleatoire_rapide(M, G, dim, nbcl, 0);
  	 temps_final=clock();
	 temps[2]=(temps_final - temps_initial) * 1e-6 ;


	printf("temps exo %d = %f \n\n",1,temps[0]); 
	printf("temps exo %d = %f \n\n",2,temps[1]);
	printf("temps exo %d = %f \n\n",3,temps[2]);
	printf("temps exo %d = %f \n\n",5,temps[3]);
	printf("temps exo %d = %f \n\n",6,temps[4]);

	printf("coups exo %d = %d \n\n",1,coups[0]); 
	printf("coups exo %d = %d \n\n",2,coups[1]);
	printf("coups exo %d = %d \n\n",3,coups[2]);
	printf("coups exo %d = %d \n\n",5,coups[3]);
	printf("coups exo %d = %d \n\n",6,coups[4]);

  
//-------------------------------------------------------------------//	
  grille_attente_touche();
  grille_ferme_fenetre(G);
  grille_free(G);

  return 0;
}












