#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "biblio.h"
#include "biblio_liste.h"



void afficheMorceau(CellMorceau* cm){

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
		afficheMorceau(cm);
		cm=cm->suiv;
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

	return bib;
}


void insere(Biblio *B, int num, char *titre, char *artiste){
	/*suppose que B est deja une biblio*/
	CellMorceau* cm = malloc(sizeof(CellMorceau));
	cm-> suiv= NULL;
	cm-> num = num;
	cm-> titre = titre;  //ne pas dupliquer, on recupere celle du parser
	cm-> artiste = artiste; //aussi

	//si premier elem
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
CellMorceau* rechercheParNum(Biblio* B, int n){

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
CellMorceau* rechercheParTitre(Biblio* B, char* titre){

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


//recherche tous les morceaux d'un meme artiste (renvoi une Biblio* )
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

			//inserer un duplicata de cm dans la bib
			insere(bib, cm->num, strdup(cm->titre), strdup(cm->artiste)) ;

		}
		cm= cm-> suiv;
	}

	return bib;
}


//insertion d'un nouveau morceau -> on l'a deja


//suppression d'un morceau
int supprimeMorceau(Biblio *B, int num){

	if(! B->L){
		printf("bibliotheque vide");
		return 0;
	}

	//si c'est le premier element
	if(B->L -> num == num ){
			//on le supprime
			CellMorceau* asuppr = B->L;
			B->L = B->L->suiv;
			//free
			free(asuppr->artiste);
			free(asuppr->titre);
			asuppr->suiv=NULL;
			free(asuppr);

			return 1;
		}

	//si plusieur elements de la liste
	CellMorceau* cm= B->L;
	while(cm->suiv){ //cm==morceau  ne marche pas sur duplicata
		if( cm -> num == num){
			//on le supprime
			CellMorceau* asuppr = cm->suiv;
			cm->suiv = cm->suiv->suiv;
			//free
			free(asuppr->artiste);
			free(asuppr->titre);
			asuppr->suiv=NULL;
			free(asuppr);

			return 1; //on supprime la premiere occurence
		}
		cm= cm-> suiv;
	}

	return 1;
}




Biblio *uniques(Biblio *B){

	if(! B->L){
		printf("bibliotheque vide");
		return NULL;
	}

	Biblio* bib = nouvelle_biblio();


	CellMorceau* tmp= B->L;
	CellMorceau * tmp2 ;
	for(int i = 0 ; i<B->nE;i++){
		tmp2 = tmp -> suiv;
		int doubl = 0;
		while(tmp2){
			if(strcmp(tmp->titre,tmp2->titre)==0 ){
				printf("doublon trouvé \n");
				doubl = 1;
				break;
			}
			tmp2 = tmp2 -> suiv ;
		}
		// on insere que les elems qui n'ont pas de double devant eux
		if(doubl== 0 ){
			insere(bib , tmp->num,strdup(tmp->titre),strdup(tmp->artiste));
		}
		tmp = tmp -> suiv;
	}

	return bib;
}



Biblio *extraireMorceauxDe(Biblio *B, char * artiste){
	Biblio* bib= nouvelle_biblio();

	if(! B->L){
		printf("bibliotheque vide");
		return NULL;
	}

	CellMorceau* cm= B->L;
	//on parcours la liste et on insere les elems de l'artiste
	while(cm){
		if(strcmp(artiste, cm->artiste) == 0){
			insere(bib, cm->num, cm->titre, cm->artiste);
		}
		cm= cm-> suiv;
	}

	return bib;
}
