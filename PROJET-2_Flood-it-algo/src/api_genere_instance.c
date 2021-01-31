#include "api_genere_instance.h"

#include <stdlib.h>

void gi_genere_matrice(int dim, int nbcl, int nivdif, int graine, int **M) {
  int diam = nivdif * dim / 100;
  if(diam == 0) {
    diam = 1;
  }
  srand(graine);

  int j;
  for(j = 0; j < dim; j++) {
    int i;
    for(i = 0; i < dim; i++) {
      M[i][j] = -1;
    }
  }

  for(j = 0; j < dim; j++) {
    int i;
    for(i = 0; i < dim; i++) {

      if(M[i][j] == -1) {
        int c = rand() % (nbcl);

        int prof = 1 + rand() % (diam);
        int larg = 1 + rand() % (diam);

        int k = 0;
        while(k < prof && j + k < dim) {
          M[i][j] = c;
          int di = rand() % larg / 4.0;
          int si = 1 - 2 * rand() % 2;
          int m = 0;
          while(m < larg) {
            if(i + si * di + m >= 0
               && i + si * di + m < dim
               && M[i + si * di + m][j+k] == -1) {
              M[i + si * di + m][j + k] = c;
            }
            m++;
          }
          k++;
        }
      }
    }
  }
}
