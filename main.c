#include "biblio.h"

#include<stdio.h>
#include<stdlib.h>


void menu()
{
	printf("Menu:\n");
	printf("0-Sortie\n");
	printf("1-Affichage\n");
	printf("2-Recherche morceaux uniques\n");
	printf("3-Recherche morceau par titre\n");
	printf("4-Recherche morceaux d'un artiste\n");
	printf("5-Recherche un morceau par son artiste (et titre)\n");
	printf("Votre choix : ");
}

int main(int argc, const char *argv[])
{

	if (argc != 3) {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>", argv[0]);
		return 1;
	}
	
	const char *nomfic = argv[1];
	int nlignes = atoi(argv[2]);
	char titre[249];
	char a[249];
	
	printf("Lecture :\n");
	Biblio *biblio = charge_n_entrees(nomfic, nlignes);
	
	int ch;
	do {
		menu();
		int lus = scanf("%d", &ch);
		if (lus == 0)
			ch = 0;
		
		switch(ch) {
			case 1 :
				printf("Affichage\n");
				affiche(biblio);
				break;
			case 2:
				{
					Biblio *Bunique = uniques(biblio);
					affiche(Bunique);
					libere_biblio(Bunique);
					break;
				}
			case 3 :
				{
					printf("Saisir le titre du morceau :\n");
					scanf(" %248[^\n]", titre);
					CellMorceau * r = rechercheParTitre(biblio, titre);
					if (r == NULL) printf("Aucun morceau de titre : %s!!!\n", titre);
					else afficheMorceau(r);
					break;
				}
				
			case 4 :
			{
				printf("Saisir le nom de l'artiste:\n");
				scanf(" %248[^\n]", a);
				Biblio *bib = extraireMorceauxDe(biblio, a);
				if (bib == NULL) printf("Aucun morceau de l'artiste : %s!!!\n", a);
				else affiche(bib);
				break;
			}
			
			case 5 :
			{
				printf("Saisir le nom de l'artiste:\n");
				scanf(" %248[^\n]", a);
				printf("Saisir le titre du morceau :\n");
				scanf(" %248[^\n]", titre);
				CellMorceau *cm = rechercheParArtiste(biblio, a, titre);
				if (cm == NULL) printf("morceau non trouvé : %s!!!\n", a);
				else afficheMorceau(cm);
				break;
			}
				
			default :
				ch = 0;
				break;
		
		}
		
	} while (ch != 0);
	
	libere_biblio(biblio);
	printf("Au revoir\n");
	
	return 0;
}
