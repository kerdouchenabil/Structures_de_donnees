#ifndef API_GRILLE_H
#define API_GRILLE_H

typedef struct Grille Grille;

/* Fonction d initialisation de la Grille */
/* 
Entree:
   dim : dimension de la grille
   nbcl   : nombre de couleurs
   taille_pixel : taille d affichage de la grille en pixel
            Doit etre inferieur a la resolution de l ecran
   G : adresse d'un pointeur sur l element Grille

Sortie:
   G: allocation et affectation des elements necessaires
      a l affichage d une grille de jeu */
Grille *grille_init(int dim, int nbcl, int taille_pixel);

/* Fonction permettant l'ouverture de la fenetre graphique
   contenant une grille ainsi que l'affichage total de la grille*/
void grille_ouvre_fenetre(Grille *G);

/* Fonction permettant la fermeture de la fenetre graphique
   contenant une grille */
void grille_ferme_fenetre(Grille *G);

/* Fonction permettant l affectation d une case a une nouvelle
   couleur */
void grille_attribue_couleur_case(Grille *G, int i, int j, int c);
 
/* Fonction permettant de redessiner la grille */
void grille_redessine(Grille *G);

/* Fonction permettant de mettre en pause le programme en attente
   de la pression d une touche */
void grille_attente_touche(void);

/* Liberation memoire d une grille */
void grille_free(Grille *G);

#endif /* API_GRILLE_H */
