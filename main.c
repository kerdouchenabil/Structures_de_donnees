#include "biblio_arbrelex.h"
#include<stdio.h>
#include<stdlib.h>
#include "biblio.h"

int main (){

	Biblio* biblio = charge_n_entrees("BiblioMusicale.txt", 50);
	affiche(biblio);
	
	Biblio* bibArtiste = extraireMorceauxDe(biblio, "Rihanna");
	affiche(bibArtiste);
	
	libere_biblio(biblio);
	
	
	
	printf("\n--------test-------\n");
	afficheMorceau( rechercheParNum(biblio, 0) );	
	
	return 0 ;
}
