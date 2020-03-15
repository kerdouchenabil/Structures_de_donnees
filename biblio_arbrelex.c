#include "biblio_arbrelex.h"
#include<stdio.h>
#include<stdlib.h>

//ok

Biblio *nouvelle_biblio(void)
{
   Biblio *b =malloc(sizeof(Biblio));
   b->nE =0;
   b->A = malloc(sizeof(Noeud));
   return b ;
}




void insere(Biblio *B, int num, char *titre, char *artiste){

	Noeud * cour = B->A;
	Noeud * prec = cour;

	int i = 0;
	while (artiste[i]!='\0'){ //pour chaque lettre de l'artiste
		if(cour==NULL){
		
			//creation du noeud
			Noeud * n = malloc(sizeof(Noeud*)); //sizeof(Noeud) ??
			
			n->car = artiste[i]; //noeud contient la lettre i de l'artiste
			
			n->liste_morceaux=NULL;
			n->car_suiv=NULL;
			n->liste_car=NULL;
			printf("noeud créé: %c\n", artiste[i]);
			
			//insertion du noeud
			if(B->A==NULL){
				B->A=n;
			}
			if(prec!=NULL){
				prec->liste_car=n;
			}
			
			cour=n;
			
		}
		else if(cour->car == artiste[i]){ //vertical
			printf("bon carac lu: %c (avance vertical i=%d)\n", artiste[i], i);
			prec=cour;
			cour=cour->car_suiv;
			i++;
		}else{					//horizontal
			printf("on tente un carac alternatif  %c \n", artiste[i]);
			prec=cour;
			cour=cour->liste_car;
		}
	}
	
	
	//insertion du morceau au dernier noeud(artiste)
	
		CellMorceau * cm = malloc(sizeof(CellMorceau));
		cm -> num = num;
		cm -> titre = titre;
		cm -> artiste = artiste ;
		cm -> suiv = NULL;
	
	if (prec->liste_morceaux== NULL){
		prec->liste_morceaux = cm;
		cm -> suiv = NULL;
	 }else{
	 	cm->suiv=prec->liste_morceaux;
	 	prec->liste_morceaux=cm;
	 }
	 B->nE=(B->nE)+1;
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
