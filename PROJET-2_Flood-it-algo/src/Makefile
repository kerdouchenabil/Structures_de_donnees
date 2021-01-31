CC = gcc
CFLAGS = -W -Wall -Os `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`
EXEC = floodit floodit_partie1 jeux_essais

all: $(EXEC)

api_genere_instance.o: api_genere_instance.c api_genere_instance.h
	$(CC) $(CFLAGS) -c api_genere_instance.c

api_grille.o: api_grille.c api_grille.h
	$(CC) $(CFLAGS) -c api_grille.c

liste_cases.o: liste_cases.c liste_cases.h
	$(CC) $(CFLAGS) -c liste_cases.c

graphe.o: graphe.c graphe.h liste_cases.h fonctions.h
	$(CC) $(CFLAGS) -c graphe.c

fonctions.o: fonctions.c fonctions.h liste_cases.h
	$(CC) $(CFLAGS) -c fonctions.c

fonctions2.o: fonctions2.c fonctions2.h graphe.h liste_cases.h
	$(CC) $(CFLAGS) -c fonctions2.c


floodit.o: floodit.c
	$(CC) $(CFLAGS) -c floodit.c

floodit: floodit.o liste_cases.o graphe.o api_grille.o api_genere_instance.o fonctions.o fonctions2.o
	$(CC) -o floodit floodit.o liste_cases.o graphe.o api_grille.o api_genere_instance.o fonctions.o fonctions2.o $(LDFLAGS)


floodit_partie1.o: floodit_partie1.c
	$(CC) $(CFLAGS) -c floodit_partie1.c

floodit_partie1: floodit_partie1.o liste_cases.o  api_grille.o api_genere_instance.o fonctions.o
	$(CC) -o floodit_partie1 floodit_partie1.o liste_cases.o api_grille.o api_genere_instance.o fonctions.o $(LDFLAGS)
jeux_essais.o: jeux_essais.c
	$(CC) $(CFLAGS) -c jeux_essais.c

jeux_essais: jeux_essais.o liste_cases.o graphe.o api_grille.o api_genere_instance.o fonctions.o fonctions2.o
	$(CC) -o jeux_essais jeux_essais.o liste_cases.o graphe.o api_grille.o api_genere_instance.o fonctions.o fonctions2.o $(LDFLAGS)
clean:
	rm -f *.o $(EXEC)
