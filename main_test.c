#include "biblio_tabdyn.h"
//#include "biblio_arbrelex.h"
//#include "biblio.h"

#include<stdio.h>
#include<stdlib.h>


int main (){
	
	
	Biblio* bib = charge_n_entrees("BiblioMusicale.txt", 10);  //OK ?
	
	affiche(bib);
	
	CellMorceau* cm = rechercheParNum(bib, 5);
	printf("affich du morceau-----\n");
	afficheMorceau(cm);
	
	int ind;
	cm = rechercheParNum_indice(bib, 5, &ind);
	afficheMorceau(&bib->T[ind]);
	printf("ind= %d\n\n", ind);
	
	affiche(bib);
	
	/*
	printf("\n--------test extraireMorceauxDe-------\n");
	Biblio* bibArtiste = extraireMorceauxDe(bib, "Echosmith");
	//affiche(bibArtiste);
	
	
	
	
	printf("\n--------test afficheMorceau-------\n");
	afficheMorceau( rechercheParNum(bib, 5) );	//OK
	
	libere_biblio(bib);  //OK
	*/
	
	return 0 ;
}
