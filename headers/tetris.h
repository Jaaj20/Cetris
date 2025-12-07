#ifndef TETRIS_H
#define TETRIS_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2ttf/include/SDL2/SDL_ttf.h"
#include "../SDL2image/include/SDL2/SDL_image.h"

#define TAILLE_CASE 23
#define H_FENETRE 540
#define L_FENETRE 960
#define HAUTEUR 22
#define LARGEUR 10
#define W_BG  (LARGEUR)*TAILLE_CASE + 17
#define VIDE 8                /* Couleur des cases vides */
#define CHANGEMENT_NIVEAU 8  /* Indique combien de lignes doivent avoir ete supprimees pour changer de niveau */
#define DIMINUTION_PERIODE 75 /* Décrémentation de la periode d'horloge de 50 ms */
#define TRUE 1
#define FALSE 0


struct une_case
{
    int colonne;
    int ligne;
};

struct piece
{
    int pos_ligne, pos_colonne;
    struct une_case la_piece[4];
    int type;
};

struct plateau
{
    int carre; /* VIDE si la case n'est pas occupée */
};

struct color
{
    char *nom;
    Uint8 r, g, b;
};

#endif