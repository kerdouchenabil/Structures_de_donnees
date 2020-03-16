#include "biblio_tabdyn.h"
//#include "biblio_arbrelex.h"
//#include "biblio.h"

#include<stdio.h>
#include<stdlib.h>


int main (){

	Biblio* biblio = charge_n_entrees("BiblioMusicale.txt", 10);  //OK ?
	
	affiche(biblio); //OK
	
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
