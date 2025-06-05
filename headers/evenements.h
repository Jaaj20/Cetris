#ifndef EVENEMENTS_H
#define EVENEMENTS_H

#include "tetris.h"

/* Gestion du temps */
Uint32 at_top_horloge(Uint32 interval, void *param);

/* Initialisation d'une pièce et la place en haut du plateau */
void initialiser(struct piece *p_tetromino, struct une_case tab[4], int indice);

/* Verification et suppression des lignes remplies + MAJ du score */
int supprimer_lignes(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], int *score);

/* Verification et affichage du statut */
int partie_perdue(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2]);

#endif