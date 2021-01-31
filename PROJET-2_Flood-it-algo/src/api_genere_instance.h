#ifndef API_GENERE_INSTANCE_H
#define API_GENERE_INSTANCE_H

/* Fonction de generation d'une instance*/
/* Entree:
   dim   : dimension de la grille carree 
   nbcl  : nombre de couleurs demandees
   nivdif: niveau de difficulte entre 0 et 100
           (taille moyenne d une zone mesuree 
            en pourcentage de dim*dim)
   graine: graine de la generation aleatoire
   M     : matrice entiere carree dim * dim DEJA ALLOUEE
           
   Sortie: Affectation de M telle que M[i][j] possede un numero
           de couleur choisi aleatoirement entre 0 et nbcl-1.
           La generation depend du niveau de difficulte choisi*/

void gi_genere_matrice(int dim, int nbcl, int nivdif, int graine, int **M);

#endif /* API_GENERE_INSTANCE_H */
