#include "biblio_arbrelex.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//ok

Biblio *nouvelle_biblio(void)
{
   Biblio *b =malloc(sizeof(Biblio));
   b->nE =0;
   b->A = malloc(sizeof(Noeud));
   return b ;
}



//fonction insere
void insere(Biblio *B, int num, char *titre, char *artiste){

	int i =0;
	// Indice lisant nom
	Noeud * cour =B -> A ; // Pointeur courant
	Noeud * prec = cour ;
	// Pointeur sur la valeur precedant cour
	while ( ( cour != NULL ) && ( artiste [ i ]!= '\0' ) ) {
		prec = cour ;
		if ( cour -> car == artiste [ i ]) { // On a lu le bon caractere
			cour = cour -> car_suiv ;
			i ++;
		}
		else { // On tente un caractere alternatif
			cour = cour -> liste_car ;
		}
	}


	//creation du morceau
	CellMorceau* cm = malloc(sizeof(CellMorceau));
	cm->suiv = NULL;
	cm->num = num;
	cm->artiste = artiste;
	cm->titre = titre;



	if ( artiste [ i ]== '\0' ) {
		printf ( "La chaine %s est presente \n" , artiste ) ;


		//insertio en debut de liste_morceaux
		cm->suiv = prec->liste_morceaux;
		prec->liste_morceaux = cm;
		return;
	}


	else {
		printf ( "La chaine %s est presente jusqu’aucaractere: %c numero %d \n" , artiste , artiste[i-1] ,i -1) ;

		if ( artiste [i]== prec -> car ) { //   ( artiste [i -1]== prec -> car )  ????
			printf ( "La suite de la chaine peut etre inseree a la suite de la lettre %c \n" , prec-> car);
			//insertion verticale i++
			//le i pointe deja sur la derniere lettre trouvée

			cour=prec;
			while(artiste[i] != '\0'){ //on continue le prcours des lettres de l'artiste
				prec=cour;

				//creation d'un Noeud
				Noeud* nd = malloc(sizeof(Noeud));
				nd->liste_car = NULL;
				nd->car_suiv = NULL;
				nd->liste_morceaux = NULL;

				nd->car = artiste[i]; //il prend la lettre courante de l'artiste

				cour->car_suiv = nd;
				cour = nd; //on avance vers le carac suivant

				i++;
			}

			//insertion du morceau
			cm->suiv = cour->liste_morceaux;
			cour->liste_morceaux = cm;
			return;


		}else {
			printf ( "La suite de la chaine peut etre inseree en alternative a la lettre %c \n" , prec-> car);
			//insertion horizontatle une fois, puis le reste verticale

			//creation d'un Noeud Horizontal
			Noeud* nd = malloc(sizeof(Noeud));
			nd->liste_car = NULL;
			nd->car_suiv = NULL;
			nd->liste_morceaux = NULL;

			nd->car = artiste[i]; //il prend la lettre courante de l'artiste

			prec->liste_car = nd; //

			//on avance
			prec=nd;
			i++;

			//insertion de tous les autres noeuds s'ils existent
			cour=prec;
			while(artiste[i] != '\0'){ //on continue le parcours des lettres de l'artiste
				prec=cour;

				//creation d'un Noeud
				Noeud* nd = malloc(sizeof(Noeud));
				nd->liste_car = NULL;
				nd->car_suiv = NULL;
				nd->liste_morceaux = NULL;

				nd->car = artiste[i]; //il prend la lettre courante de l'artiste

				cour->car_suiv = nd;
				cour = nd; //on avance vers le carac suivant

				i++;
			}

			//insertion du morceau
			cm->suiv = cour->liste_morceaux;
			cour->liste_morceaux = cm;
			return;

		}
	}



}







//recherche artiste
Noeud* recherche_artiste ( Biblio *B , char * artiste ) {

	int i =0;
	// Indice lisant nom
	Noeud * cour =B -> A ; // Pointeur courant
	Noeud * prec = cour ;
	// Pointeur sur la valeur precedant cour
	while ( ( cour != NULL ) && ( artiste [ i ]!= '\0' ) ) {
		prec = cour ;
		if ( cour -> car == artiste [ i ]) { // On a lu le bon caractere
			cour = cour -> car_suiv ;
			i ++;
		}
		else { // On tente un caractere alternatif
			cour = cour -> liste_car ;
		}
	}


	if ( artiste [ i ]== '\0' ) {
		printf ( "Artiste %s trouvé \n" , artiste ) ;
		return prec;
	}

	printf ( "Artiste %s NON trouvé \n" , artiste ) ;
	return NULL;



}




void afficheMorceau(CellMorceau *cell)
{
	printf("|A| num: %8d | titre: %-32.32s | artiste: %-32.32s |A|\n", cell->num, cell->titre, cell->artiste);
}


void affiche_Noeud(Noeud * A){
  if (A == NULL){
	return;
  }
  if (A-> liste_morceaux !=NULL){
	CellMorceau * cm = A -> liste_morceaux;
	while (cm!= NULL) {
	  afficheMorceau(cm);
	  cm = cm -> suiv;
	}
  }
  affiche_Noeud(A->liste_car);
  affiche_Noeud(A->car_suiv);
}


void affiche(Biblio *B)
{
  if (B ==NULL){
	printf("bibliotheque vide\n" );
	return;
  }

  printf("----------affichage_bibliotheque-----------\n");

  Noeud * temp = B->A;
  affiche_Noeud(temp);

}




Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	int i = 0; // Indice lisant nom
	Noeud *cour = B->A; // Pointeur courant
	Noeud *prec = cour; // Pointeur sur la valeur precedant cour

	while ((cour != NULL) && (artiste[i] != '\0')) {
		prec = cour;

		if (cour->car == artiste[i]) { // On a lu le bon caractere
			cour = cour->car_suiv;
			i++;
		}
		else { // On tente un caractere alternatif
			cour = cour->liste_car;
		}
	}

	Biblio *bib = nouvelle_biblio();

	if (artiste[i] == '\0'){
		printf("artiste trouvé\n");

		//insertion des morceaux
		CellMorceau *cm = prec->liste_morceaux;
		while (cm) {
			insere(bib, cm->num, strdup(cm->titre), strdup(cm->artiste));
			cm = cm->suiv;
		}
	}
	else {
		printf("artiste non trouvé.\n");
	}

	return bib;
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


void libere_Noeud(Noeud* A){
	if (A == NULL){
		return;
	}

	libere_Noeud(A->liste_car);
	libere_Noeud(A->car_suiv);

	if (A-> liste_morceaux !=NULL){
		libere_morceaux(A->liste_morceaux);
	}

}


void libere_biblio(Biblio *B)
{
	if (B ==NULL){
	printf("bibliotheque vide\n" );
	return;
  }

  libere_Noeud(B->A); //recursive
  free(B);
  printf("bibliotheque libérée\n");

}



void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	int n = 0;
	if(B!=NULL){
		n = B->nE;
	}

	insere(B, n, titre, artiste);
}



CellMorceau* rechercheParNum_Noeud(Noeud* A,int num){

	if( A==NULL )
		return NULL;

  if (A->liste_morceaux != NULL){ //si y'a des morceaux dans le noeud, parcours la liste_morceaux
  	CellMorceau * cm = A -> liste_morceaux;
	while (cm!= NULL) {
	  if(cm->num == num){ //trouvé !
	  	return cm;
	  }
	  cm = cm -> suiv;
	}
  }

  //si pas de morceaux dans le noeud
  CellMorceau* cm = rechercheParNum_Noeud(A->car_suiv, num);
  if(cm)
  	return cm;

  return rechercheParNum_Noeud(A->liste_car, num);

}


CellMorceau * rechercheParNum(Biblio *B, int num)
{
  if (B ==NULL){
	printf("bibliotheque vide\n" );
	return NULL;
  }

  CellMorceau * cm = rechercheParNum_Noeud(B->A, num);	//recursive

  if( ! cm ){
  	printf("morceau non trouvé\n");
  	return NULL;
  }

  return cm;

}



CellMorceau* rechercheParTitre_Noeud(Noeud* A, char* titre){

	if( A==NULL )
		return NULL;

  if (A->liste_morceaux != NULL){ //si y'a des morceaux dans le noeud, parcours la liste_morceaux
  	CellMorceau * cm = A -> liste_morceaux;
	while (cm!= NULL) {
	  if( strcmp(cm->titre, titre)==0 ){ //trouvé !
	  	return cm;
	  }
	  cm = cm -> suiv;
	}
  }

  //si pas de morceaux dans le noeud
  CellMorceau* cm = rechercheParTitre_Noeud(A->car_suiv, titre);
  if(cm)
  	return cm;

  return rechercheParTitre_Noeud(A->liste_car, titre);

}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
  if (B ==NULL){
	printf("bibliotheque vide\n" );
	return NULL;
  }

  CellMorceau * cm = rechercheParTitre_Noeud(B->A, titre);	//recursive

  if( ! cm ){
  	printf("morceau non trouvé\n");
  	return NULL;
  }

  return cm;
}






int supprimeMorceau(Biblio *B, int num)
{

}






Biblio *uniques (Biblio *B)
{

}
