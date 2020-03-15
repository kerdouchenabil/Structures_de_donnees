#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "biblio.h"
#include "biblio_liste.h"



void affiche_morceau(CellMorceau* cm){

	if(! cm){
		printf("morceau vide");
	}

	printf("Morceau: num=%d; titre=%s; artiste=%s \n",
	cm->num, cm->titre, cm->artiste);	

}



void affiche(Biblio* B){

	if(! B->L){
		printf("bibliotheque vide");
		return;
	}

	CellMorceau* cm= B->L;
	while(cm){
		affiche_morceau(cm);
	}

}




void libere_biblio(Biblio *B){

	if(! B->L){
		printf("bibliotheque vide");
		return ;
	}

	CellMorceau* cm= B->L;
	while(cm){
		free(cm->artiste);
		free(cm->titre);
		B->L = B->L->suiv;
		cm ->suiv =NULL;
		free(cm);
		cm = B->L;
	}

}


Biblio *nouvelle_biblio(void){
	Biblio* bib= malloc(sizeof(*bib));

	bib->L = NULL;
	bib-> nE = 0;
}


void insere(Biblio *B, int num, char *titre, char *artiste){
	/*suppose que B est deja une biblio*/
	CellMorceau* cm = malloc(sizeof(CellMorceau));
	cm-> suiv= NULL;
	cm-> num = num;
	cm-> titre = titre;  //ne pas dupliquer, on recupere celle du parser
	cm-> artiste = artiste; //aussi


	if(! B-> L){
		B-> L = cm;
	}
	else{ //insere au debut

		cm->suiv = B->L;
		(B->nE)++;
		B->L = cm;
	}
}



// ex1 q1.6

//recherce un morceau par son num
CellMorceau* chercher_num(Biblio* B, int n){

	if(! B->L){
		printf("bibliotheque vide");
		return NULL;
	}

	CellMorceau* cm= B->L;
	while(cm){
		if(cm-> num == n){
			return cm;
		}
		cm= cm-> suiv;
	}

	return NULL; //si on ne trouve rien
}


//recherce un morceau par son titre
CellMorceau* chercher_titre(Biblio* B, char* titre){

	if(! B->L){
		printf("bibliotheque vide");
		return NULL;
	}

	CellMorceau* cm= B->L;
	while(cm){
		if(strcmp(titre, cm->titre) == 0){
			return cm;
		}
		cm= cm-> suiv;
	}

	return NULL; //si on ne trouve rien
}


//recherche tous les morceaux d'un meme artiste (renvoi une Biblio* ?)
Biblio* chercher_artiste(Biblio* B, char* artiste){

	if(! B->L){
		printf("bibliotheque vide");
		return NULL;
	}

	//creer la bib a retourner (liste de morceaux)
	Biblio* bib = nouvelle_biblio();


	CellMorceau* cm= B->L;
	while(cm){
		if(strcmp(artiste, cm->artiste) == 0){

			//inserer un duplicata de cm dans la bib ??
			insere(bib, cm->num, strdup(cm->titre), strdup(cm->artiste)) ;

		}
		cm= cm-> suiv;
	}

	return bib;
}


//insertion d'un nouveau morceau -> on l'a deja


//suppression d'un morceau
Biblio* supprimer_morceau(Biblio* B, CellMorceau* morceau){

	if(! B->L){
		printf("bibliotheque vide");
		return NULL;
	}

	//si c'est le premier element
	if( (strcmp( (morceau->titre), (B->L->titre) ) == 0) &&
			(strcmp( (morceau->artiste), (B->L->artiste) ) ==0) &&
			(morceau->num == B->L->num)
		){
			//on le supprime
			CellMorceau* asuppr = B->L;
			B->L = B->L->suiv;
			//free
			free(asuppr->artiste);
			free(asuppr->titre);
			asuppr->suiv=NULL;
			free(asuppr);

			return B;
		}

	//si plusieur elements de la liste
	CellMorceau* cm= B->L;
	while(cm->suiv){ //cm==morceau  ne marche pas sur duplicata
		if( (strcmp( (morceau->titre), (cm->suiv->titre) ) == 0) &&
			(strcmp( (morceau->artiste), (cm->suiv->artiste) ) ==0) &&
			(morceau->num == cm->suiv->num)
		){
			//on le supprime
			CellMorceau* asuppr = cm->suiv;
			cm->suiv = cm->suiv->suiv;
			//free
			free(asuppr->artiste);
			free(asuppr->titre);
			asuppr->suiv=NULL;
			free(asuppr);

			return B; //on supprime la premiere occurence
		}
		cm= cm-> suiv;
	}

}




Biblio *uniques(Biblio *B){
	/*
	if(! B->L){
		printf("bibliotheque vide");
		return NULL;
	}

	Biblio* bib = nouvelle_biblio();


	CellMorceau* cm= bib->L;
	while(cm){
		affiche_morceau(cm);
	}
	*/
	return NULL;
}





