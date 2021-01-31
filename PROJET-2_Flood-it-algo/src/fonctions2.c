#include "fonctions2.h"



/*fonctions d'affichage text*/
void affiche_zsg(G_zsg* gz){
	printf("Sommets de Zone_Szsg:\n");
	Cellule_som* cs = gz->Szsg;
	while(cs){
		printf("(%d) ", cs->sommet->num);//(num:marque)
		cs=cs->suiv;
	}
	printf("\n");
}

void affiche_bordure(G_zsg* gz){
	printf("Bordure:\nTaille_bordure[ ");
	for(int i=0; i<gz->nbcl; i++){
		printf("%d ", gz->taille_bordure[i]);
	}
	
	printf("]\n");
	
	for(int i=0; i<gz->nbcl; i++){
		printf("CL %d: ", i);
		Cellule_som* cs = gz->Bordure_g[i];
		
		while(cs){
			printf("(%d) ", cs->sommet->num);//(num:marque)
			cs=cs->suiv;
		}
		printf("\n");
	}
}


/*initialise la struct G_zsg qui gère la strategie*/
G_zsg* init_gzsg(Graphe_zone* G, int dim, int nbcl){
	G_zsg* gz = malloc(sizeof(G_zsg));
	gz->dim=dim;
	gz->nbcl=nbcl;
	gz->G=G;
	gz->Szsg=NULL;
	
	gz->taille_bordure=malloc(nbcl*sizeof(int));
	for(int i=0 ; i<nbcl ; i++){
		gz->taille_bordure[i] = 0;
	}
	
	gz->Bordure_g=malloc(nbcl*sizeof(Cellule_som*));
	for(int i=0 ; i<nbcl ; i++){
		gz->Bordure_g[i] = NULL;
	}
	
	return gz;
}


/* 1=fin    0=pas encore */
int fin_jeu(G_zsg* gz){

	for(int i = 0 ; i< gz -> nbcl;i++){
		if(gz -> Bordure_g[i]){
			return 0;	
		}
	}
	return 1 ; //fin de jeu si bordure vide 

}


void detruit_gzsg(G_zsg* gz,int dim){
	detruit_graphe(gz->G,dim);

	detruit_liste_sommet(gz->Szsg);
	for(int i = 0 ; i < *(gz->taille_bordure) ; i++){

		detruit_liste_sommet(gz->Bordure_g[i]);
	}

	free(gz->Bordure_g);
	free(gz->taille_bordure);
}



/*une etape du jeu, ajoute les sommets bordure de couleur cl dans la zone et met a jour la bordure*/
void maj_bordure_g(G_zsg* gz, int cl){
	if(gz->Bordure_g[cl]==NULL){//ce cas ne doit pas arriver
		printf("Bordure[%d]==NULL\n", cl);
		return;
	}
	
	//insertion des sommets de couleur cl dans la zsg (concatenation des listes)
	Cellule_som* tmp = gz->Bordure_g[cl]; //tete de liste zsg
	Cellule_som* prec = tmp;
	
	while(tmp){
		tmp->sommet->marque = 0; //marque=0 (dans la zsg)
		tmp->sommet->cl = cl;//
		//ajout de la bordure en parcourant les sommets adjacents
		Cellule_som* tmpadj = tmp->sommet->sommet_adj;
		while(tmpadj){//parcours des sommets adjacents
			if(tmpadj->sommet->marque==2){//si n'a pas deja ete visité on lajoute a la bordure
			
				tmpadj -> sommet -> marque = 1 ; //marque bordure
				Cellule_som * c1 = malloc(sizeof(Cellule_som));
				//ajout en tete de liste de sa bordure correspondante
				c1->sommet = tmpadj -> sommet;
				c1->suiv = gz->Bordure_g[tmpadj->sommet->cl];
				gz->Bordure_g[tmpadj->sommet->cl]=c1;
				(gz->taille_bordure[tmpadj->sommet->cl]) += tmpadj->sommet->nbcase_som; //+nbcase_som
			}
			
			tmpadj = tmpadj -> suiv ;
		}
		
		prec=tmp;
		tmp=tmp->suiv;
	}
	
	//concatenation (agrandissement de la zone)
	prec->suiv = gz->Szsg;
	gz->Szsg = gz->Bordure_g[cl];
	gz->Bordure_g[cl] = NULL;
	gz->taille_bordure[cl] = 0;
	
}


/*retourne l'indice du max d'un tableau*/
int cherche_max(int* tab, int taille){
	int max=tab[0];
	int ind=0;
	for(int i=0; i<taille; i++){
		if(tab[i]>max){
			max=tab[i];
			ind=i;
		}
	}
	return ind;
}


int max_bordure(Graphe_zone* G, int dim, int nbcl, Grille* grille, int aff){
	//printf("debut max_bordure\n");

	G_zsg* gz = init_gzsg( G, dim,nbcl);
	int cpt=0;//nombre d'étapes de jeu
	int couleur; //couleur qui va etre tirée (qui a le + de cases en bordure)
	
	/*cas de base, on ajoute [0][0] a la zone et ses adjacents dans la bordure*/
	Cellule_som * cs = malloc(sizeof(Cellule_som));
	cs -> sommet = gz -> G ->mat[0][0];
	cs -> sommet -> marque = 0;
	cs -> suiv = NULL;
	gz -> Szsg = cs ;
	
	//ajout des adj a la bordure
	Cellule_som * tmp = gz->Szsg->sommet->sommet_adj;
	while(tmp){
		tmp->sommet -> marque = 1 ; 
		Cellule_som * c1 = malloc(sizeof(Cellule_som));
		c1->sommet = tmp ->sommet;
		c1->suiv = gz->Bordure_g[tmp->sommet->cl];
		gz->Bordure_g[tmp->sommet->cl]=c1;
		(gz->taille_bordure[tmp->sommet->cl]) += tmp->sommet->nbcase_som;
		
		tmp = tmp -> suiv ;
	}
	
	/*fin cas de base*/ 
	
	/*strategie*/ 
	while(!fin_jeu(gz)){
		//printf("while fin_jeu()=%d\n", fin_jeu(gz));
		
		couleur = cherche_max(gz->taille_bordure, nbcl);
		maj_bordure_g(gz, couleur);
		cpt++;
		
		/*affichage*/
		if(aff==1){
			printf("\n---ETAPE-%d---\n",cpt);
			
			Cellule_som* lcs = gz->Szsg; //parcours des cellules de la zone
			while(lcs){
				
				//parcours des cases du sommet en cours
				ListeCases lc = lcs->sommet->cases;
				while(lc){
					grille_attribue_couleur_case(grille,lc->i,lc->j,couleur);
					lc=lc->suiv;
				}
				
				lcs=lcs->suiv;
			}
			
			grille_attente_touche();
			grille_redessine(grille);
				
			/*affichage text*/
			affiche_bordure(gz);
			affiche_zsg(gz);
			
		}//fin if	

	}
	
	//printf("fin max_bordure\n");
	return cpt;
}




/*-------------------  exo 6  ---------------------*/


/*affiche un tableau d'entiers*/
void affiche_tab(int* tab, int taille){
	printf("TAB=[ ");
	for(int i=0; i<taille; i++){
		printf("%d ", tab[i]);
	}
	printf("]\n");
}



/*cree une file de sommets*/
File* cree_file(){
	File* file=malloc(sizeof(File));
	file->last=NULL;
	file->sommets=NULL;
	return file;
}



/*enfile un sommet en fin de liste*/
void enfiler(File* f, Sommet* s){
	//creation d'une cellule_som
	Cellule_som* cs = malloc(sizeof(Cellule_som));
	cs->sommet = s;
	cs->suiv=NULL;

	if(f->sommets == NULL){ //file vide (insere le premier element)
		f->last = cs;
		f->sommets = cs;
		
	}else{//file non vide, insere en fin
		f->last->suiv = cs;
		f->last=cs;
	}
}



/*defile le premier sommet et le retourne*/
Sommet* defiler(File* f){
	if(f->sommets==NULL){
		printf("file vide!\n");
		return NULL;
	}
	
	Sommet* s = f->sommets->sommet;
	Cellule_som* adetruire = f->sommets;//////////
	f->sommets=f->sommets->suiv;
	free(adetruire);
	
	return s;
}



/*cherche le plus court chemin de racine vers dest  return tab de couleurs dans l'ordre*/
int* cherche_chemin(Sommet* racine, Sommet* dest){
	
	File* file = cree_file();//creation de la file
	
	racine->distance=0;//ajout de la racine dans la file
	enfiler(file, racine);
	
	while(file->sommets){ //tant que la file n'est pas vide /*on peut verifier aussi tant que dest n'est pas parcouru*/
		Sommet* s = defiler(file);//on defile un sommet
		
		Cellule_som* cs = s->sommet_adj; //parcourir ses sommets adjacents
		while(cs){
			if(cs->sommet->distance == -1){//si non visité par la file
				cs->sommet->pere = s;//maj son pere
				cs->sommet->distance = s->distance+1;;//maj sa distance
				enfiler(file, cs->sommet);
			}
			cs=cs->suiv;
		}
	}
	
	//creation du tableau de couleurs initialisé a -1
	int* tab=malloc( dest->distance *sizeof(int));   /// dest->distance -1 ??? taille du tab ???
	for(int i=dest->distance; i>0; i--){
		tab[i]=-1;
	}
	
	//remonter de la destination vers la racine pour creer le tab chemin de couleurs
	Sommet* tmp = dest;
	int i=dest->distance;   /// dest->distance -1 ???
	while(tmp){
		
		tab[i] = tmp->cl;
		i--;
		tmp=tmp->pere;
	}
	
	return tab;
}




/* strategie du parcours en largeur */
int parcours_largeur(Graphe_zone* G, int dim, int nbcl, Grille* grille, int aff){
	
	G_zsg* gz = init_gzsg( G, dim,nbcl);
	int cpt=0;//nombre d'étapes de jeu
	
	/*cas de base, on ajoute [0][0] a la zone et ses adjacents dans la bordure*/
	Cellule_som * cs = malloc(sizeof(Cellule_som));
	cs -> sommet = gz -> G ->mat[0][0];
	cs -> sommet -> marque = 0;
	cs -> suiv = NULL;
	gz -> Szsg = cs ;
	
	//ajout des adj a la bordure
	Cellule_som * tmp = gz->Szsg->sommet->sommet_adj;
	while(tmp){
		tmp->sommet -> marque = 1 ; 
		Cellule_som * c1 = malloc(sizeof(Cellule_som));
		c1->sommet = tmp ->sommet;
		c1->suiv = gz->Bordure_g[tmp->sommet->cl];
		gz->Bordure_g[tmp->sommet->cl]=c1;
		(gz->taille_bordure[tmp->sommet->cl]) += tmp->sommet->nbcase_som;
		
		tmp = tmp -> suiv ;
	}
	
	/*fin cas de base*/ 
	
	Sommet* destination = G->mat[dim-1][dim-1]; //zoneBasDroite
	
	int* tab = cherche_chemin(G->mat[0][0], destination); //tab est le chemin
	
	int i=0;
	for(i=1 ; i<=destination->distance ; i++){/*>=1 pour exclure couleur[0][0] et <=...*/
		//printf("ETAPE %d   Couleur=%d\n",cpt, tab[i]);
		
		maj_bordure_g(gz, tab[i]);
		cpt++;
		
		
		/*affichage*/
		if(aff==1){
			if(i==1)printf("distance zoneBasDroite <-> Racine = %d\n", destination->distance);
			affiche_tab(tab, destination->distance);
			
			Cellule_som* lcs = gz->Szsg; //parcours des cellules de la zone
			while(lcs){
				
				//parcours des cases du sommet en cours
				ListeCases lc = lcs->sommet->cases;
				while(lc){
					grille_attribue_couleur_case(grille,lc->i,lc->j,tab[i]); //couleur=tab[i]
					lc=lc->suiv;
				}
				
				lcs=lcs->suiv;
			}
			
			grille_attente_touche();
			grille_redessine(grille);
				
			/* affichage text */
			affiche_zsg(gz);
			affiche_bordure(gz);
		}//fin if
		
	}
	
	if(aff)printf("----- ARRIVE A ZONE BAS DROITE -> Lancement strategie max_bordure -----\n");
	
	/*continue le jeu avec strategie max_bordure*/
	//int cpt2 = max_bordure(G, dim, nbcl, grille, aff); /*rreur cas de base (il faut passer la struct de gestion G_zsg en parametre pour qu'elle continue le travail de cette fonction et ne recommence pas depuis le debut)*/
	int cpt2=0;
	int couleur=tab[i];
	while(!fin_jeu(gz)){
		couleur = cherche_max(gz->taille_bordure, nbcl);
		maj_bordure_g(gz, couleur);
		cpt++;
		
		/*affichage*/
		if(aff==1){
			printf("\n---ETAPE-%d---\n",cpt);
			
			Cellule_som* lcs = gz->Szsg; //parcours des cellules de la zone
			while(lcs){//parcours des cases du sommet en cours
				ListeCases lc = lcs->sommet->cases;
				while(lc){
					grille_attribue_couleur_case(grille,lc->i,lc->j,couleur);
					lc=lc->suiv;
				}
				lcs=lcs->suiv;
			}
			
			grille_attente_touche();
			grille_redessine(grille);
				
			/*affichage text*/
			affiche_bordure(gz);
			affiche_zsg(gz);
		}//fin if	

			
	
	}
	
	
	return cpt+cpt2;
}





















