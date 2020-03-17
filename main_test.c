#include "biblio_hachage.h"
//#include "biblio_arbrelex.h"
//#include "biblio.h"

#include<stdio.h>
#include<stdlib.h>


int main (){

	
	int x = h(2);
	printf("x=%d\n", x);
	
	Biblio* bib = NULL;
	insere(bib, 01, "blabla", "art");
	
	//Biblio* biblio = charge_n_entrees("BiblioMusicale.txt", 10);  //OK ?
	
	affiche(bib); //OK
	
	/*
	printf("\n--------test extraireMorceauxDe-------\n");
	Biblio* bibArtiste = extraireMorceauxDe(biblio, "Echosmith");
	//affiche(bibArtiste);
	
	
	
	
	printf("\n--------test afficheMorceau-------\n");
	afficheMorceau( rechercheParNum(biblio, 5) );	//OK
	
	libere_biblio(biblio);  //OK
	*/
	
	return 0 ;
}
