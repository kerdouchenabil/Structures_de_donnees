#include "biblio_arbrelex.h"
#include<stdio.h>
#include<stdlib.h>


Biblio *nouvelle_biblio(void)
{
   Biblio *b =malloc(sizeof(Biblio));
   b->nE =0;
   b->A = malloc(sizeof(Noeud));
   return b ;
}


Noeud *  recherche_ou_cree_artiste ( Biblio *B , char * artiste ) {
  int i =0; // Indice lisant nom
  Noeud * cour =B -> A ; // Pointeur courant
  Noeud * prec = cour ; // Pointeur sur la valeur precedant cour
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
  
  
  if(artiste[i]=='\0'){
	printf("artiste trouvé\n");
	if (cour != NULL){
	  printf("trouvé dans Noeud cour!!! \n");
	}else{
		printf("trouvé dans Noeud prec!!! \n");
	}
	
	
  }
  else{
	if(artiste[i-1]==prec->car)/*le cour est a null !!*/{
		printf("artiste non trouvé 1, cour=%p ; prec=%p \n", cour, prec);
	  while (artiste[i]!='\0') {
		//création des Noeud
		Noeud *temp = malloc(sizeof(Noeud));
		temp -> car = artiste[i];
		prec -> car_suiv = temp ;
		temp -> car_suiv = NULL;
		temp -> liste_car =NULL;
		temp -> liste_morceaux = NULL;
		temp = prec ;
		i++;
	  }
	  return prec ;
	}
	else{
		printf("artiste non trouvé (2), cour=%p ; prec=%p \n", cour, prec);
	  //création des Noeud
	  Noeud *temp = malloc(sizeof(Noeud));
	  temp -> car = artiste[i];
	  prec -> liste_car = temp ; //a vérifier
	  temp -> car_suiv = NULL;
	  temp -> liste_car =NULL;
	  temp -> liste_morceaux=NULL;
	  temp = prec ;
	  while (artiste[i]!='\0') {
		Noeud *temp = malloc(sizeof(Noeud));
		temp -> car = artiste[i];
		prec -> car_suiv = temp ;
		temp -> car_suiv = NULL;
		temp -> liste_car =NULL;
		temp -> liste_morceaux = NULL;
		temp = prec ;
		i++;
	  }
	  return prec ;
	}
  }
}





void insere(Biblio *B, int num, char *titre, char *artiste)
{
	if(!B){
		printf("bibliotheque vide, creation...\n");
		B = nouvelle_biblio();
	}
	
	
  Noeud* temp = recherche_ou_cree_artiste(B,artiste);
  CellMorceau * cm = malloc(sizeof(CellMorceau));
  cm -> artiste = artiste;
  cm -> num = num;
  cm -> titre = titre ;
  cm -> suiv = NULL;
  if(temp -> liste_morceaux == NULL){
	temp->liste_morceaux = cm ;
  }else{
	cm -> suiv = temp->liste_morceaux;
	temp ->liste_morceaux = cm ;
  }
  
  //nombre d'elements ++ dans la Biblio
  B->nE = (B->nE)+1 ;

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
  
  Noeud * temp = B->A;
  affiche_Noeud(temp);

}



Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
  int i =0; // Indice lisant nom
  Noeud * cour =B -> A ; // Pointeur courant
  Noeud * prec = cour ; // Pointeur sur la valeur precedant cour
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
  
  if(artiste[i]=='\0'){
  	printf("artiste trouvé\n");
	if (cour != NULL){
	  printf("trouvé dans Noeud cour!!! \n");
	}else{
		printf("trouvé dans Noeud prec!!! \n");
	}
	
	if(cour==NULL || cour->liste_morceaux==NULL){
		printf("pas de morceaux pour cet artiste\n");
		return NULL;	
	}
	
	//creation d'une Biblio de tous les morceaux de l'artiste
	Biblio* bibArtiste = nouvelle_biblio();
	
	CellMorceau* cm = cour->liste_morceaux;
	while(cm){
		insere(bibArtiste, cm->num, cm->titre, cm->artiste);
		cm = cm->suiv; 
	}
	
  }
  else{ //artiste n'existe pas
	printf("artiste non trouvé\n");
	return NULL;
  }
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
		return NULL; // a verifier ??
	
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
	return;
  }
  
  Noeud * cm = rechercheParNum_Noeud(B->A, num);	//recursive
  
  if( ! cm ){
  	printf("morceau non trouvé\n");
  	return NULL;
  }
  
  return cm;
  
}



CellMorceau* rechercheParTitre_Noeud(Noeud* A, char* titre){
	
	if( A==NULL )
		return NULL; // a verifier ??
	
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
	return;
  }
  
  Noeud * cm = rechercheParNum_Noeud(B->A, titre);	//recursive
  
  if( ! cm ){
  	printf("morceau non trouvé\n");
  	return NULL;
  }
  
  return cm;
}



Biblio *uniques (Biblio *B)
{

}










int supprimeMorceau(Biblio *B, int num)
{

}
