
#include"ex5.h"

	
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
	


	
