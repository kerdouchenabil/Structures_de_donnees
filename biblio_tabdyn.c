#include "biblio_tabdyn.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


Biblio *nouvelle_biblio(void)
{
   Biblio* bib= malloc(sizeof(Biblio));
   bib->nE=0;
   bib->capacite=50;
   bib->T= malloc( (bib->capacite)*sizeof(CellMorceau ));

   return bib;
}


void libere_morceau(CellMorceau* cm){
	free(cm->artiste);
	free(cm->titre);
	free(cm);
}


void libere_biblio(Biblio *B)
{
	for(int i=0; i< B->nE; i++){
		libere_morceau(&(B->T[i])); /*si probleme a l'execution changer
        l'argument et mettre des . a la place des fleches  */
	}

   free(B->T);
   free(B);
}


void insere(Biblio *B, int num, char *titre, char *artiste)
{
    if(!B){
    	B= nouvelle_biblio();
    }

    if(B->nE >= B->capacite){
    	int * p =(int*)realloc( B->T , 2*(B->capacite)*sizeof(CellMorceau ) );
    	printf("reallocation\n");
    }

    //creation du morceau
    CellMorceau * cm = malloc(sizeof(CellMorceau ));
    cm->titre=titre;
    cm->artiste=artiste;
    cm->num=num;

    //insertion dans la case libre (nE)
    B->T[B->nE] = *cm;
    B->nE = B->nE+1;

}


void afficheMorceau(CellMorceau  *cell)
{
	printf("*T* %8d * %-32.32s * %-32.32s *T*\n", cell->num, cell->titre, cell->artiste);
}



void affiche(Biblio *B)
{
	for(int i=0; i<B->nE; i++){
		afficheMorceau(&B->T[i]);
	}
}




CellMorceau  * rechercheParNum(Biblio *B, int num)
{
	for(int i=0; i< B->nE; i++){
		if(B->T[i].num  ==  num ){
			return &B->T[i];
		}
	}
	printf("morceau non trouvé\n");
	return NULL;
}


CellMorceau  *rechercheParTitre(Biblio *B, char * titre)
{
	for(int i=0; i< B->nE; i++){
		if(strcmp(B->T[i].titre , titre)  ==  0 ){
			return &B->T[i];
		}
	}
	printf("morceau non trouvé\n");
	return NULL;
}




CellMorceau  * rechercheParNum_indice(Biblio *B, int num, int* indice)
{
	for(int i=0; i< B->nE; i++){
		if(B->T[i].num  ==  num ){
			*indice= i;
			return &B->T[i];
		}
	}
	printf("morceau non trouvé\n");
	return NULL;
}


int supprimeMorceau(Biblio *B, int num)
{
	int ind;
	CellMorceau * cm = rechercheParNum_indice(B, num, &ind);

	if(cm){ //element a supprimer trouvé
		//supprimer le morceau
		libere_morceau(cm); // cm == B->T[ind]

		//decaler tous les autres morceaux
		for(int i=ind; i< (B->nE)-1; i++){  //pour aller jusqua T[B->nE-2]
			B->T[i] = B->T[i+1];
		}
		//a la fin on supprime le dernier morceau en doublon
		libere_morceau(&B->T[B->nE-1]);
		//nE--
		B->nE = B->nE -1;

		printf("morceau supprimé\n");
		return 1;
	}

	printf("morceau non trouvé\n");
	return 0;
}



void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	int n = B->nE;
	insere(B, n, titre, artiste);
}





Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
    if(!B){
        return NULL;
    }
    if(!artiste){
        return NULL ;
    }
    Biblio *bib  = nouvelle_biblio();
    for(int i =0 ; i< B->nE;i++){
        if(strcmp((B->T[i].artiste),artiste)==0){
            insereSansNum(bib,strdup(B->T[i].titre),strdup(B->T[i].artiste));
        }
    }
    return bib;
}





Biblio *uniques (Biblio *B)
{

   for(int i = 0 ; i<B->nE-1;i++){
     CellMorceau  * m = rechercheParTitre(B,B->T[i].titre);
     if (m) {
         supprimeMorceau(B,m->num);
     }
   }
   return B ;
}
