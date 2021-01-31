#include"graphe.h"


/*renvoi vrai si la case ne sort pas de la grilles*/
int dans_grille2(int dim, int i, int j){
	if(i < dim && i>=0 && j < dim && j >= 0) return 1;
	return 0;
}

Sommet * cree_sommet(int num ,int cl ,ListeCases * l, int nbcase_som, Cellule_som* sommet_adj){
	Sommet* s= malloc(sizeof(Sommet));
	s->num=num;
	s->cl=cl;
	s->cases=*l;
	s->nbcase_som=nbcase_som;
	s->sommet_adj=sommet_adj;
	s->marque=2; // =2 a la creation (non visité)
	s->distance=-1; // non visité
	s->pere=NULL; //non visité
	
	return s;
}


void ajoute_liste_sommet(Cellule_som* csm, Sommet* s){
	Cellule_som * c1=malloc(sizeof(Cellule_som));	
	c1->sommet=s;
	c1->suiv=csm;
	csm=c1;
	printf("sommet ajouté %d \n", c1->sommet->num);
}


void detruit_liste_sommet(Cellule_som * csm){
	while(csm){
		Cellule_som * c1 =csm->suiv;	
		free(csm);
		csm=c1;
	}
}


int adjacent(Sommet *s1,Sommet *s2){
	//printf("dans adjacent__ s1=%d s2=%d ", s1->num,s2->num);
	Cellule_som* tmp = s1->sommet_adj;
	
	while(tmp){
		if(tmp->sommet->num == s2->num){return 1;}
		tmp=tmp->suiv;
	}
	
	tmp=s2->sommet_adj;
	while(tmp){
		
		if(tmp->sommet->num == s1->num){return 1;}
		tmp=tmp->suiv;
	}
	
	return 0;

}



void ajoute_voisin(Sommet *s1,Sommet *s2){
	//printf("adjacent=%d ", adjacent(s1,s2));
	if(!adjacent(s1,s2)){//si elles ne sont pas deja adjacentes
		//ajoute_liste_sommet(s1->sommet_adj,s2);
		Cellule_som* c = malloc(sizeof(Cellule_som)); 
		c->sommet=s1;
		c->suiv = s2->sommet_adj;
		s2->sommet_adj=c;
		//ajoute_liste_sommet(s2->sommet_adj,s1);
		Cellule_som* c2 = malloc(sizeof(Cellule_som)); 
		c2->sommet=s2;
		c2->suiv = s1->sommet_adj;
		s1->sommet_adj=c2;
		
		//printf("voisin ajouté\n");
	}
}


void detruit_sommet(Sommet * s){
	detruit_liste(&s->cases);
	detruit_liste_sommet(s->sommet_adj);
	if(s->pere){detruit_sommet(s->pere);}
	free(s);
}

void detruit_graphe(Graphe_zone * gr,int dim){
	detruit_liste_sommet(gr->som);
	for(int i=0 ; i< dim ; i ++){
		for (int j = 0 ; j < dim ; j++){
			detruit_sommet(gr->mat[i][j]);
		}
		free(gr->mat[i]);
	}
	free(gr->mat);
}



Graphe_zone * cree_graphe_zone(int **M, int dim){
	
	
	Graphe_zone *G = malloc(sizeof(*G));
	G->som=NULL;//tres important
	
	//allocation de la matrice
	Sommet*** m= malloc(dim*sizeof(Sommet**));
	for(int i=0; i<dim; i++){
		m[i]=malloc(dim*sizeof(Sommet*));
	}
	
	//initialisation des cases a NULL
	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			m[i][j]=NULL;
		}
	}
	
	G->mat=m;
	G->nbsom=0;

	Sommet *s;
	int num_sommet=0;
	//creation des sommets
	
	ListeCases L = NULL; //tres important!
	ListeCases tmp = L;
	
	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			//si la case ne pointe pas deja sur un sommet
			if(G->mat[i][j]==NULL){
				int taille=0;				
				int cl = M[i][j];
				num_sommet++;
				//on trouve sa zone
				trouve_zone_imp(M,dim,i,j,&taille,&L);
				//creation du sommet	
				s = cree_sommet(num_sommet,cl,&L,taille,NULL);
				tmp = L;
				
				//ajout du sommet dans le graphe
				//ajoute_liste_sommet(G->som, s);
				Cellule_som* c = malloc(sizeof(Cellule_som));//////
				c->sommet=s;
				c->suiv = G->som;
				G->som=c;
				//printf("sommet ajouté %d \n", s->num);
				
				//faire pointer les cases sur les sommets	
				while(tmp){
					//printf("i=%d; j=%d pointe sur sommet %d\n", tmp->i, tmp->j, s->num);
					G->mat[tmp->i][tmp->j] = s;
					tmp=tmp->suiv;
				}
				
				(G->nbsom)++;
				L=NULL;
				//detruit_liste(&L);
				
			}
		}
	}
	
	//gestion des sommets adjacents, on parcours a nouveau toutes les cases
	
	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
		
			if(G->mat[i][j]==NULL){//pour la securité
				printf("case [%d;%d] n'a pas de sommet ! exit\n", i,j);
				exit(1);
			}
			
			if(dans_grille2(dim, i, j+1)){
				if(G->mat[i][j+1]->num != G->mat[i][j]->num){//si elles ne pointent pas vers le meme sommet
					//ajoute_voisin test a l'interieur si ils ne sont pas deja adjacents(!doublons)
					ajoute_voisin(G->mat[i][j], G->mat[i][j+1]);
				}
			}
			if(dans_grille2(dim, i, j-1)){
				if(G->mat[i][j-1]->num != G->mat[i][j]->num){
					ajoute_voisin(G->mat[i][j], G->mat[i][j-1]);
				}
			}
			if(dans_grille2(dim, i+1, j)){
				if(G->mat[i+1][j]->num != G->mat[i][j]->num){
					ajoute_voisin(G->mat[i][j], G->mat[i+1][j]);
				}
			}
			if(dans_grille2(dim, i-1, j)){
				if(G->mat[i-1][j]->num != G->mat[i][j]->num){
					ajoute_voisin(G->mat[i][j], G->mat[i-1][j]);
				}
			}			
			
		}
	}
	
	return G;
}


/*fonction affichage du graphe*/
void affiche_graphe(Graphe_zone *G) {
	
	if(!G->som){
		printf("graphe vide !\n");
		return;
	}
	
	Cellule_som *cs = G->som;
	
	while (cs) {
		Sommet* s = cs->sommet;
		printf("SOMMET %d: couleur=%d; nbcase=%d; marque=%d\n", s->num, s->cl, s->nbcase_som, s->marque);
		//affichage de ses cases
		printf("cases: ");
		ListeCases l = s->cases;
		while(l){
			printf("[%d;%d] ", l->i, l->j);
			l=l->suiv;
		}
		//affichage des sommets adjacents
		printf("\nAdjacents: ");
		Cellule_som* c = s->sommet_adj;
		while(c){
			printf("(%d) ", c->sommet->num);
			c=c->suiv;
		}
		
		printf("\n");
		cs = cs->suiv;
	}
	printf("\n");
}























