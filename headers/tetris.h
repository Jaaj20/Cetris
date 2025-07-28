#ifndef TETRIS_H
#define TETRIS_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2ttf/include/SDL2/SDL_ttf.h"

#define TAILLE_CASE 20
#define HAUTEUR 22
#define LARGEUR 20
#define VIDE 7                /* n'importe quelle valeur qui n'est pas un indice du tableau des couleurs */
#define CHANGEMENT_NIVEAU 8  /* indique combien de lignes doivent avoir ete supprimees pour changer de niveau */
#define DIMINUTION_PERIODE 75 /* décrémentation de la periode d'horloge de 50 ms */
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
    int carre; // VIDE si la case n'est pas occupée
};

struct color
{
    char *nom;
    Uint8 r, g, b;
};

#endif