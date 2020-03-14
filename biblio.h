/* biblio.h */

#ifndef biblio_h
#define biblio_h

typedef struct Biblio Biblio;
typedef struct CellMorceau CellMorceau;


void affiche_morceau(CellMorceau* cm);

Biblio *nouvelle_biblio(void);
Biblio *charge_n_entrees(const char *nom_fichier, int n);
void libere_biblio(Biblio *B);

void insere(Biblio *B, int num, char *titre, char *artiste);
void affiche(Biblio *B);
Biblio *uniques(Biblio *B);

CellMorceau* chercher_num(Biblio* B, int n);
CellMorceau* chercher_titre(Biblio* B, char* titre);
Biblio* chercher_artiste(Biblio* B, char* artiste);
Biblio* supprimer_morceau(Biblio* B, CellMorceau* morceau);



#endif /* biblio_h */
