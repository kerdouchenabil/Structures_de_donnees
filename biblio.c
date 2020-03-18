#include<stdio.h>
#include<stdlib.h>
#include "parser.h"
#include "biblio.h"

Biblio *charge_n_entrees(const char *nom_fichier, int n){

	Biblio* bib= nouvelle_biblio();

	FILE* f= fopen(nom_fichier, "r");

	if(! f) {
		printf("erreur ouverture fichier !");
		return NULL;
	}


	int nb=1;
	while(end_of_file(f)==0 && nb<=n){

		int num;
		char* titre = NULL; //TRES IMPORTANT D'INITIALISER A NULL !!!
		char* artiste = NULL;
		char c;

		int ntitre;
		int nartiste;


		if(parse_int(f, &num) == 0){
			printf("erreur format");
			return NULL;
		}


		if(parse_char(f, '\t') == 0){
			printf("erreur format");
			return NULL;
		}


		if(parse_string(f, &titre, &ntitre, '\t') == 0){
			printf("erreur format");
			return NULL;
		}


		if(parse_char(f, '\t') == 0){
			printf("erreur format");
			return NULL;
		}

		//printf(" \n");//////////////////erreur buffer ! reglé: initialise a NULL !

		if(parse_string(f, &artiste, &nartiste, '\n') == 0){
			printf("erreur format");
			return NULL;
		}

		if(parse_char(f, '\n') == 0){
			printf("erreur format");
			return NULL;
		}

		//ajout du morceau
		insere(bib, num, titre, artiste);
		//insere(bib, num, titre, strdup(artiste)); ///strdup() rique fuite memoire !

		nb++;

	}

	fclose(f);
	printf("fin lecture, fermeture fichier\n");
	return bib;

}



/*recherche par artiste  commune a toutes les structures*/
CellMorceau *rechercheParArtiste(Biblio *B, char * artiste, char* titre){
	
	return rechercheParTitre( extraireMorceauxDe(B, artiste) , titre );

}



void vider_buffer(){ //ne fonctionne pas !! utiliser un printf a la place
	int c=0;
	while (c!='\n' && c!=EOF) {
		c= getchar();
	}
}



/*---------------------- jeux de tests -----------------------------*/



	
	void temps_rechercheParNum(Biblio *B, int num){
	
		printf("temps recherche par numero\n");
		temps_initial = clock () ;
		CellMorceau* cm = rechercheParNum(B, num);
		temps_final = clock () ;
		temps_cpu = (( double ) ( temps_final - temps_initial ) ) /CLOCKS_PER_SEC;
		printf ( "temps_rechercheParNum= %f \n", temps_cpu ) ;
		
	}
	

	void temps_rechercheParTitre(Biblio *B, char* titre){
	
		printf("temps recherche par titre\n");
		temps_initial = clock () ;
		CellMorceau* cm = rechercheParTitre(B, titre);
		temps_final = clock () ;
		temps_cpu = (( double ) ( temps_final - temps_initial ) ) /CLOCKS_PER_SEC;
		printf ( "temps_recherchePartitre= %f \n", temps_cpu ) ;
		
	}
	
	
	void temps_rechercheParArtiste(Biblio *B, char* artiste, char* titre){
	
		printf("temps recherche par artiste\n");
		temps_initial = clock () ;
		CellMorceau* cm = rechercheParArtiste(B, artiste, titre);
		temps_final = clock () ;
		temps_cpu = (( double ) ( temps_final - temps_initial ) ) /CLOCKS_PER_SEC;
		printf ( "temps_rechercheParArtiste= %f \n", temps_cpu ) ;
		
	}
	

































