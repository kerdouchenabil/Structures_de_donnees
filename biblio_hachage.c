#include "biblio_hachage.h"
#include "math.h"


/*----------------fonctions hachage-------------*/

unsigned int fonction cle(const char *artiste){
	
	int s=0; //somme des codes ascii
	
	int i=0;
	while(artiste[i] != '\0'){ //parcours les lettres de artiste
		s+= artiste[i];
	}	
	
	return s;
}


unsigned int fonction hachage(unsigned int cle, int m){

	float A= (sqrt(5)-1)/2 ;
	// a completer...
	
}



/*----------------------------------------------*/


Biblio *nouvelle_biblio(void) 
{
	Biblio* bib= malloc(sizeof(Biblio));
	bib->nE=0;
	bib->m=50; // taille de la table de hachage
	bib->T = malloc( m * sizeof(CellMorceau*)); //a verifier
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
    for (int i=0; i<m; i++){ //parcours la table de hachage
    	libere_morceaux(B->T[i]);
    	//freeB->T[i]; //fait aussi par libere_morceaux
    }
    
    free(B->T);
    free(B);
}


void insere(Biblio *B, int num, char *titre, char *artiste)
{
    
}

void afficheMorceau(CellMorceau *cell)
{
	printf("§§ %8d § %-32.32s § %-32.32s §§\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B)
{
    
}



Biblio *uniques (Biblio *B)
{
    
}

CellMorceau * rechercheParNum(Biblio *B, int num)
{

}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{

}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{

}

void insereSansNum(Biblio *B, char *titre, char *artiste)
{

}


int supprimeMorceau(Biblio *B, int num)
{

}





































