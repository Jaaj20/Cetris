#ifndef DEPLACEMENTS_H
#define DEPLACEMENTS_H

#include "tetris.h"

/* Descente */
int descendre(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino);

/* Décalage a gauche */
void decaler_gauche(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino);

/* Décalage a droite */
void decaler_droite(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino);

/* Rotation à gauche (sens anti horaire) */
void rotation_gauche(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino);

/* Rotation à droite (sens horaire) */
void rotation_droite(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino);

/* Hard Drop */
void hard_drop(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino);

#endif