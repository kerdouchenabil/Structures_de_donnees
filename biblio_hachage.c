#include "biblio_hachage.h"
#include "math.h"
#include "string.h"
#include<stdio.h>
#include<stdlib.h>

/*----------------fonctions hachage-------------*/

unsigned int fonction_cle(const char *artiste){

	unsigned int s=0; //somme des codes ascii

	int i=0;
	while(artiste[i] != '\0'){ //parcours les lettres de artiste
		s+= artiste[i];
		i++;
	}


	return s;
}

int h(int k){ //la fonction qui change, on teste differents fonctions pour eviter les collisions

	float x= k*A;
	int y= (int)(x);
	return (int)(TAILLE_TABLE * (x-y));//a MODIFIER chercher une bonne fonction


}

unsigned int fonction_hachage(unsigned int cle, int m){

	int x = h(cle); //calcul du hach

	return abs( x ) % m ; //retourne l'indice de la case ou inserer
}



/*----------------------------------------------*/


Biblio *nouvelle_biblio(void)
{
	Biblio* bib= malloc(sizeof(Biblio));
	bib->nE=0;
	bib->m=TAILLE_TABLE; // taille de la table de hachage
	bib->T = malloc( TAILLE_TABLE * sizeof(CellMorceau*)); //a verifier

	for(int i = 0 ;i < TAILLE_TABLE; i++){
		bib->T[i]= NULL; //cases vides pas de morceaux

	}

	return bib ;
}



void libere_morceaux(CellMorceau* cm){

	while (cm!= NULL) {
		CellMorceau* tmp = cm->suiv;
		free(cm->artiste);
		free(cm->titre);
		free(cm);
		cm=tmp;
	}
}


void libere_biblio(Biblio *B)
{
    for (int i=0; i<B->m; i++){ //parcours la table de hachage
    	libere_morceaux(B->T[i]);
    }

    free(B->T);
    free(B);
}


void insere(Biblio *B, int num, char *titre, char *artiste)
{

	if(! B){
		printf("Biblio vide.. creation\n");
		B = nouvelle_biblio();
	}


	int k = fonction_cle(artiste);

	int ind = fonction_hachage(k, B->m);

	printf("insertion..  k=%d, ind=%d \n", k, ind);

	CellMorceau* cm = malloc(sizeof(CellMorceau));
	cm->num = num;
	cm->titre = titre;
	cm->artiste = artiste;
	cm->suiv = NULL;

	if(B->T[ind] == NULL){ //inserer directement comme premier element

		B->T[ind] = cm;
		//printf("morceau inséré PREMIER ELEM: ");	afficheMorceau(cm);

	}else{//inserer en debut de liste

		cm->suiv = B->T[ind];
		B->T[ind] = cm;
		//printf("morceau inséré DEBUT LISTE: ");	afficheMorceau(cm);
	}

    (B->nE)++;

}



void afficheMorceau(CellMorceau *cell)
{
	printf("§§ %8d § %-32.32s § %-32.32s §§\n", cell->num, cell->titre, cell->artiste);
}



void affiche(Biblio *B)
{

    if(! B){
		printf("Biblio vide ! \n");
		return;
	}

	printf("--------affichage de la bibliotheque-------------\n");

    for(int i=0; i< B->m; i++){

    	//printf("T[%d]  \n", i); //juste pour voir toutes les cases ////

    	CellMorceau* tmp = B->T[i];
    	while(tmp){
    		afficheMorceau(tmp);
    		tmp = tmp->suiv;
    	}
    }

}





CellMorceau * rechercheParNum(Biblio *B, int num)
{
	if(!B) {
		return NULL;
	}
	if(!B->T){
		return NULL;
	}

	for(int i=0; i< B->m; i++){
    	CellMorceau* tmp = B->T[i];
    	while(tmp){
    		if(tmp->num == num){
    			return tmp;
    		}
    		tmp = tmp->suiv;
    	}
    }

    return NULL;

}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
	if(! B){
		printf("Biblio vide \n");
		return NULL;
	}

	for(int i=0; i< B->m; i++){
    	CellMorceau* tmp = B->T[i];
    	while(tmp){
    		if( strcmp(tmp->titre, titre) == 0 ){
    			return tmp;
    		}
    		tmp = tmp->suiv;
    	}
    }

    return NULL;
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	if(! B){
		printf("Biblio vide ! \n");
		return NULL;
	}

	int k = fonction_cle(artiste);

	int ind = fonction_hachage(k, B->m);

	if(!B->T[ind]){
		return NULL;
	}

	CellMorceau * liste = B->T[ind];
	Biblio * bib = nouvelle_biblio();

	afficheMorceau(liste);

	//parcourir la liste
	while(liste){
		if(strcmp(liste->artiste, artiste)==0){
			insere(bib,liste->num,strdup(liste->titre),strdup(liste->artiste));
		}

		liste=liste->suiv;
	}
	return bib ;

}



void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	insere(B,B->nE,titre,artiste);
}



void libere_un_morceau(CellMorceau * cm ){
		CellMorceau* tmp = cm->suiv;
		free(cm->artiste);
		free(cm->titre);
		free(cm);
		cm=tmp;
}


int supprimeMorceau(Biblio *B, int num)
{
	if(!B) {
		return 0;
	}
	if(!B->T){
		return 0;
	}

	for(int i=0; i< B->m; i++){ //parcours la table pour chercher l'element

    	CellMorceau* tmp = B->T[i];

    	if(tmp->suiv==NULL){ // un seul element dans la liste

    		if(tmp -> num == num){ //si c'est le bon element
    			libere_un_morceau(tmp);
    			return 1;
    		}//sinon il n'existe pas
    		return 0;
    	}

    	//si la liste contient plusieur elements
    	CellMorceau * prec = tmp; //besoin du precedent pour le chainage
    	while(tmp){//parcours la liste
    		if(tmp->num == num){ //si c'est l'element qu'on cherche
    			prec -> suiv = tmp -> suiv;
    			libere_un_morceau(tmp);
    			return 1 ;
    		}
    		//sinon continue la recherche
    		prec = tmp ;
    		tmp = tmp->suiv;
    	}

	}
	//element non trouvé
	return 0  ;
}






Biblio *uniques (Biblio *B)
{

	Biblio* bib = nouvelle_biblio();

	//doublon = meme artiste && meme titre
	/*meme artiste veux dire meme cle et meme case dans la table de hachage*/

	if(! B){
		printf("Biblio vide ! \n");
		return NULL;
	}

	for(int i=0; i<B->m; i++){

		if(B->T[i]!=NULL){ //liste vide
			CellMorceau* tmp= B->T[i];
			CellMorceau * tmp2 ;
			while(tmp){
				tmp2 = tmp -> suiv;//PAS SUR A A VERIFIER
				int doubl = 0;
				while(tmp2){
					if(strcmp(tmp->titre,tmp2->titre)==0 ){
					printf("doublon trouvé \n");
					doubl = 1;
					break;
					}
					tmp2 = tmp2 -> suiv ;
				}
				if(doubl== 0 ){
					insere(bib , tmp->num,strdup(tmp->titre),strdup(tmp->artiste));
				}
				tmp = tmp -> suiv;
			}


		}

	}

	return bib;


}
