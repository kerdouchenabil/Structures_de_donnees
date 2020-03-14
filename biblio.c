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


void vider_buffer(){ //ne fonctionne pas !! utiliser un printf a la place
	int c=0;
	while (c!='\n' && c!=EOF) {
		c= getchar();
	}

}
