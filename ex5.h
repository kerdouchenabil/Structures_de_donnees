#ifndef _EX5_H_
#define _EX5_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include"biblio.h"


	
	clock_t temps_initial ; /* Temps initial en micro-secondes */
	clock_t temps_final ;
	/* Temps final en micro-secondes */
	double temps_cpu ;
	/* Temps total en secondes */


	void temps_rechercheParNum(Biblio *B, int num);
	
	void temps_rechercheParTitre(Biblio *B, char* titre);
	
	void temps_rechercheParArtiste(Biblio *B, char* artiste, char* titre);





#endif

