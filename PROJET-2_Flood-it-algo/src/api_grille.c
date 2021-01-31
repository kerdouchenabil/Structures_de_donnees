#include "api_grille.h"

#include <SDL.h>

/* Structure necessaire aux fonctions d affichage*/
struct Grille {
  int dim;          /* Dimension de la grille */
  int nbcl;         /* Nombre de couleurs */
  int taille_pixel; /* Taille de la grille a l ecran */

  int cas_aff;      /* Dit si une case est limite a un pixel */
                    /* 0 s il y a trop de cases a afficher / 1 sinon */
  int taille_case;  /* Taille d une case a l ecran */
  int modulo;       /* Saut d affichache en cas de nombre de cases important */

  Uint32 *T_coul;   /* Tableau de codage des couleurs */
  SDL_Window *window;
};


Grille* grille_init(int dim, int nbcl, int taille_pixel) {
  int i;
  unsigned int genecl = 10101;
  Grille *G = malloc(sizeof(*G));
  if(G != NULL) {
    G->dim = dim;
    G->nbcl = nbcl;
    G->taille_pixel = taille_pixel;

    G->T_coul = malloc(nbcl * sizeof(*G->T_coul));

    for(i = 0; i < 32; i++) { // pour sauter les 5 premieres couleurs un peu palotes
      genecl = genecl * (i + i + 1);
      genecl = (genecl ^ 0xffffff) >> 2;
    }

    for(i = 0; i < nbcl; i++) {
      genecl = genecl * (i + i + 1);
      genecl = (genecl ^ 0xffffff) >> 2;
      G->T_coul[i] = genecl;
    }

    if((taille_pixel * 1.0) / dim > 1) {
      G->cas_aff = 0;
      G->taille_case = taille_pixel / dim;
    } else {
      G->cas_aff = 1;
      G->modulo = dim / taille_pixel;
    }
  }
  return G;
}

void grille_free(Grille *G) {
  free(G->T_coul);
  free(G);
}

void grille_ouvre_fenetre(Grille *G) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr,
            "Erreur: ne peut pas initialiser le système graphique (\"%s\").\n",
            SDL_GetError());
    return;
  }

  atexit(SDL_Quit);

  G->window = SDL_CreateWindow("Jeu d'inondation",      // window title
                               SDL_WINDOWPOS_CENTERED,  // initial x position
                               SDL_WINDOWPOS_CENTERED,  // initial y position
                               G->taille_pixel,         // width, in pixels
                               G->taille_pixel,         // height, in pixels
                               SDL_WINDOW_OPENGL
                               );
}

void grille_ferme_fenetre(Grille *G) {
  SDL_DestroyWindow(G->window);
}

void grille_attribue_couleur_case(Grille *G, int i, int j, int c) {
  SDL_Surface *screen = SDL_GetWindowSurface(G->window);
  if(G->cas_aff == 0) {
    SDL_Rect rectangle = {
      i * G->taille_case, j * G->taille_case, G->taille_case, G->taille_case
    };
    SDL_FillRect(screen, &rectangle, G->T_coul[c]);
  }
  else {

    if(i % G->modulo == 0 && j % G->modulo == 0) {
      SDL_Rect rectangle = { i / G->modulo, j / G->modulo, 1 , 1 };
      SDL_FillRect(screen, &rectangle, G->T_coul[c]);
    }
  }
}

void grille_redessine(Grille *G) {
  // Redraw backbuffer.
  SDL_UpdateWindowSurface(G->window);
}

void grille_attente_touche() {
  SDL_Event event;

  int stop = 0;
  while(!stop) {
    // Poll system for an event.
    if(SDL_PollEvent(&event)) {
      switch(event.type) {
          // If the window has been closed, then stop the loop.
        case SDL_QUIT:
          stop = 1;

          // A key has been pressed.
        case SDL_KEYDOWN:
          stop = 1;
      }
    }
    // Let the system process other events (avoids 100% CPU).
    SDL_Delay(1);
  }

}
