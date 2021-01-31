#include "fonctions.h"
#include <stdlib.h>
#include<stdio.h>


void affiche_matrice(int** M, int dim){
	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			printf("%d\t", M[j][i]);
		}
		printf("\n");
	}
}



/*renvoi vrai si la case ne sort pas de la grilles*/
int dans_grille(int dim, int i, int j){
	if(i < dim && i>=0 && j < dim && j >= 0) return 1;
	return 0;
}



void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, ListeCases *L) {
	//printf("debut trouve_zone_rec\n");
	
	int couleur = M[i][j];
	/*case dans la grille*/
	if(dans_grille(dim, i, j)){
		/*verifie si case non parcourue*/
		if(M[i][j]!=-1){
			ajoute_en_tete(L,i,j);
			(*taille)++;
			M[i][j]=-1;
			if(dans_grille(dim, i, j+1)){
				if(M[i][j+1]==couleur){
						trouve_zone_rec(M,dim,i,j+1,taille,L);
					}
			}
			if(dans_grille(dim, i, j-1)){
				if(M[i][j-1]==couleur){
						trouve_zone_rec(M,dim,i,j-1,taille,L);
				}
			}
			if(dans_grille(dim, i+1, j)){
				if(M[i+1][j]==couleur){
						trouve_zone_rec(M,dim,i+1,j,taille,L);
				}
			}
			if(dans_grille(dim, i-1, j)){
				if(M[i-1][j]==couleur){
						trouve_zone_rec(M,dim,i-1,j,taille,L);
					}
			}
		}
	}
}


int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff) {

	//affiche_matrice(M, dim);
	printf("sequence_aleatoire_rec\n"); ///
	
	int cpt = 0; //nombre de tours (changements de couleurs)
	int taille=0; //taille de la zone
	ListeCases l;
	
	init_liste(&l);
	
	/*tanque on a pas fini la grille*/
	while(taille != dim*dim){
		
		taille = 0;
		detruit_liste(&l);
		
		trouve_zone_rec(M,dim,0,0,&taille,&l); 
		
		int clrand= M[0][0];
		/*tirage d'une couleur aléatoire diff de celle de M[0][0] (de la zone SG)*/
		while(clrand==M[0][0]){
			clrand=rand()%nbcl;
		}
		
		cpt++;//changement de couleur effectué
		
		//changer la couleur de toutes les cases de la zoneSG
		ListeCases tmp=l;
		while(tmp){
			M[tmp->i][tmp->j]=clrand;
		
			if(aff == 1){
				grille_attribue_couleur_case(G,tmp->i,tmp->j,clrand);
			}
			
			tmp=tmp->suiv;
		}
		
		/* affichage */
		if(aff==1){
			grille_attente_touche();
			grille_redessine(G);
			
			/*affichage text*/
			printf("cpt=%d\n", cpt);
		}
	}
	
 	return cpt;
}


/**--------------- exo 2 ---------------------*/

void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, ListeCases *L){
	
	*taille=0;
	int couleur=M[i][j]; //couleur de la case
	ListeCases pile; //pile est une liste, on enleve et on ajoute en tete
	init_liste(&pile);
	
	ajoute_en_tete(L,i,j);//on ajoute la case dans la liste
	M[i][j]=-1;
	ajoute_en_tete(&pile, i, j);//on la met dans la pile
	
	while(pile){ //tant que notre pile n'est pas vide
		
		if(dans_grille(dim, i, j+1)){
			if(M[i][j+1]==couleur){
					ajoute_en_tete(L, i, j+1);
					ajoute_en_tete(&pile, i, j+1);
					M[i][j+1]= -1; //parcourue
				}
		}
		if(dans_grille(dim, i, j-1)){
			if(M[i][j-1]==couleur){
					ajoute_en_tete(L, i, j-1);
					ajoute_en_tete(&pile, i, j-1);
					M[i][j-1]= -1; //parcourue
			}
		}
		if(dans_grille(dim, i+1, j)){
			if(M[i+1][j]==couleur){
					ajoute_en_tete(L, i+1, j);
					ajoute_en_tete(&pile, i+1, j);
					M[i+1][j]= -1; //parcourue
			}
		}
		if(dans_grille(dim, i-1, j)){
			if(M[i-1][j]==couleur){
					ajoute_en_tete(L, i-1, j);
					ajoute_en_tete(&pile, i-1, j);
					M[i-1][j]= -1; //parcourue
				}
		}
		
		enleve_en_tete(&pile, &i, &j); // i,j  seront modifiés !!
		(*taille)++;
	}
	
}



int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff) {

	//affiche_matrice(M, dim);
	printf("sequence_aleatoire_imp\n"); //
	
	int cpt = 0; //nombre de tours (changements de couleurs)
	int taille=0; //taille de la zone
	ListeCases l;
	
	init_liste(&l);
	
		/*tanque on a pas fini la grille*/
	while(taille != dim*dim){
		
		taille = 0;
		detruit_liste(&l);
		
		trouve_zone_imp(M,dim,0,0,&taille,&l); 
		
		int clrand= M[0][0];
		/*tirage d'une couleur aléa diff de celle de M[0][0]*/
		while(clrand==M[0][0]){
			clrand=rand()%nbcl;
		}
		
		cpt++;//changement de couleur effectué
		
		ListeCases tmp=l;
		while(tmp){
			M[tmp->i][tmp->j]=clrand;
		
			if(aff == 1){
				grille_attribue_couleur_case(G,tmp->i,tmp->j,clrand);
			}
			
			tmp=tmp->suiv;
		}
		
		if(aff==1){
			grille_attente_touche();
			grille_redessine(G);
			printf("cpt=%d\n", cpt);
		}
	}
	
 	return cpt;
}





/**--------------- exo 3 ---------------------*/

S_Zsg* init_zsg(int dim, int nbcl){
	S_Zsg* szsg= malloc (sizeof(S_Zsg));
	szsg->dim=dim;
	szsg->nbcl=nbcl;
	
	init_liste(&szsg->Lzsg);
	szsg->B= malloc(nbcl*sizeof(ListeCases)); //tableau de listes de cases
	if(!szsg->B) {printf("erreur allocation memoire"); exit(1); }
	
	for(int i=0; i<nbcl; i++){
		//szsg->B[i]= malloc(sizeof(ListeCases));
		init_liste(&szsg->B[i]); // fait pour question 3.3
	}
	
	szsg->App= malloc(dim*sizeof(int*));
	for(int i=0; i<dim; i++){
		szsg->App[i]= malloc(dim*sizeof(int));
	}
	
	//initialise la matrice a -2
	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			szsg->App[i][j] = -2;
		}
	}

	return szsg;
}


void ajoute_Zsg (S_Zsg * szsg,int i ,int j){
	ajoute_en_tete(&szsg->Lzsg,i,j);
	szsg->App[i][j]=-1;
}


void ajoute_Bordure(S_Zsg* szsg, int i, int j, int cl){
	ajoute_en_tete(&szsg->B[cl], i, j);	
	szsg->App[i][j]=cl;
	//printf("ajoute_Bordure(%d, %d, %d)\n", i,j,cl);
}


int appartient_Zsg(S_Zsg* szsg, int i, int j){
	return (szsg->App[i][j])==-1;
}


int appartient_Bordure(S_Zsg* szsg, int i, int j, int cl){
	return (szsg->App[i][j])==cl;
}


int agrandit_Zsg(int **M, S_Zsg *Z, int cl, int k, int l){

	/* on suppose que la case est dans la bordure */
	int couleur=cl, i=k, j=l;//var temp
	
	int dim=Z->dim;
	int taille=0; //nombre de cases ajoutées
	ListeCases pile; //pile est une liste, on enleve et on ajoute en tete
	init_liste(&pile);
	
	/*on peut ajouter plusieur tests tel que dans_grille() , ...*/
	//M[i][j]=-1; // on ne touche pas a la matrice ??
	if(!dans_grille(dim,i,j)){
		printf("case hors de la grille : [%d;%d]\n", i,j);
		return 0;
	}
	
	ajoute_en_tete(&pile, i, j);//on la met dans la pile
	ajoute_Zsg(Z, i, j);
	taille++; //on a ajouté cette premiere case
	
	while(pile){ //tant que notre pile n'est pas vide
		
		if(dans_grille(dim, i, j+1)){
			if(M[i][j+1]==couleur){
					
					//M[i][j+1]= -1; //parcourue
					//on l'ajoute a Lzsg si elle n y est pas deja
					if(!appartient_Zsg(Z, i, j+1)){
						ajoute_Zsg(Z, i, j+1);
						ajoute_en_tete(&pile, i, j+1); // a verif ici ou en haut
						taille++;
						//printf("ajout M[%d][%d] dans Zone, tailleZone=%d\n",i,j+1,taille);
					}
					
			}else{//si couleur differente on l'ajoute dans la bordure
				if(!appartient_Bordure(Z,i,j+1,M[i][j+1])){
					ajoute_Bordure(Z, i, j+1, M[i][j+1]);
					//printf("ajout M[%d][%d] dans Bordure, tailleZone=%d\n",i,j+1,taille);
				}
			}
		}
		
		if(dans_grille(dim, i, j-1)){
			if(M[i][j-1]==couleur){
					
					//M[i][j+1]= -1; //parcourue
					//on l'ajoute a Lzsg si elle n y est pas deja
					if(!appartient_Zsg(Z, i, j-1)){
						ajoute_Zsg(Z, i, j-1);
						ajoute_en_tete(&pile, i, j-1); // a verif ici ou en haut
						taille++;
						//printf("ajout M[%d][%d] dans Zone, tailleZone=%d\n",i,j-1,taille);
					}
					
			}else{//si couleur differente on l'ajoute dans la bordure
				if(!appartient_Bordure(Z,i,j-1,M[i][j-1])){
					ajoute_Bordure(Z, i, j-1, M[i][j-1]);
					//printf("ajout M[%d][%d] dans Bordure, tailleZone=%d\n",i,j-1,taille);
				}
				
			}
		}
		
		if(dans_grille(dim, i+1, j)){
			if(M[i+1][j]==couleur){
					
					//M[i][j+1]= -1; //parcourue
					//on l'ajoute a Lzsg si elle n y est pas deja
					if(!appartient_Zsg(Z, i+1, j)){
						ajoute_Zsg(Z, i+1, j);
						ajoute_en_tete(&pile, i+1, j); // a verif ici ou en haut
						taille++;
						//printf("ajout M[%d][%d] dans Zone, tailleZone=%d\n",i+1,j,taille);
					}
					
			}else{//si couleur differente on l'ajoute dans la bordure
				if(!appartient_Bordure(Z,i+1,j,M[i+1][j])){
					ajoute_Bordure(Z, i+1, j, M[i+1][j]);
					//printf("ajout M[%d][%d] dans Bordure, tailleZone=%d\n",i+1,j,taille);
				}
			}
		}
		
		if(dans_grille(dim, i-1, j)){
			if(M[i-1][j]==couleur){
					
					//M[i][j+1]= -1; //parcourue
					//on l'ajoute a Lzsg si elle n y est pas deja
					if(!appartient_Zsg(Z, i-1, j)){
						ajoute_Zsg(Z, i-1, j);
						ajoute_en_tete(&pile, i-1, j); // a verif ici ou en haut
						taille++;
						//printf("ajout M[%d][%d] dans Zone, tailleZone=%d\n",i-1,j,taille);
					}
					
			}else{//si couleur differente on l'ajoute dans la bordure
				if(!appartient_Bordure(Z,i-1,j,M[i-1][j])){
					ajoute_Bordure(Z, i-1, j, M[i-1][j]);
					//printf("ajout M[%d][%d] dans Bordure, tailleZone=%d\n",i-1,j,taille);
				}
			}
		}
		
		//printf("ajout M[%d][%d] Retiré de la Pile, tailleZone=%d\n",i,j,taille);
		enleve_en_tete(&pile, &i, &j); // i,j  seront modifiés !!
		
	}	
	
	return taille;
}




int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff) {
	
	printf("sequence rapide\n");
	
	S_Zsg* Z = init_zsg(dim, nbcl);
	
	int taille= agrandit_Zsg(M, Z, M[0][0], 0, 0);
	
	int cpt = 0; //nombre de tours (changements de couleurs)
	
	/*tanque on a pas fini la grille*/
	while(taille <= dim*dim){

		int clrand= M[0][0];
		/*tirage d'une couleur aléa diff de celle de M[0][0]*/
		while(clrand==M[0][0]){
			clrand=rand()%nbcl;
		}
		
		cpt++;//changement de couleur effectué
		
		//affecte la nouvelle couleur aux cases de zsg
		ListeCases tmp=Z->Lzsg;
		while(tmp){
			M[tmp->i][tmp->j]=clrand;
		
			//printf("M[%d][%d]\n",tmp->i,tmp->j);
			tmp=tmp->suiv;
		}
		
		tmp=Z->B[clrand]; //pour parcourir la liste des cases de la bordure de la couleur
		while(tmp){
			//printf("parcours_rapide lancé sur la bordure de clrand. M[%d][%d]\n", tmp->i, tmp->j);
			
			taille += agrandit_Zsg(M, Z, clrand, tmp->i, tmp->j); //  +=
			tmp= tmp->suiv;
		}
		
		Z->B[clrand]=NULL;// ou detruit 
		//detruit_liste(&Z->B[clrand]); //on detruit B[clrand] apres les avoir ajoutés
		
		if(aff==1){
			for(int i=0; i<dim; i++)
				for(int j=0; j<dim; j++)
					grille_attribue_couleur_case(G,i,j,M[i][j]);
			
			grille_attente_touche();
			grille_redessine(G);
			
			printf("cpt=%d  ", cpt);
			printf("taille_zone= %d\n",taille);
		}
		
	}
	

	return cpt; //test
}
























