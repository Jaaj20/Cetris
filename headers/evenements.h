#ifndef EVENEMENTS_H
#define EVENEMENTS_H

#include "tetris.h"

/* Gestion du temps */
Uint32 at_top_horloge(Uint32 interval, void *param);

/* Initialisation d'une pièce et la place en haut du plateau */
void initialiser(struct piece *p_tetromino, struct une_case tab[4], int indice);

/* Initialiser la partie */
void initialiser_partie(struct piece *tetromino, struct piece *preview, struct plateau plateau_jeu[HAUTEUR][LARGEUR], struct une_case tab_pieces[7][4], int *indice, int *cpt, int *niveau, int *score, Uint32 *intervalle);

/* Sauvegarde des pièces dans le plateau */
void sauvegarder_piece(struct piece tetromino, struct plateau plateau_jeu[HAUTEUR][LARGEUR]);

/* Verification et suppression des lignes remplies + MAJ du score */
int supprimer_lignes(struct plateau plateau_jeu[HAUTEUR][LARGEUR], int *score);

/* Changement de niveau */
void changement_niveau(int *horloge, Uint32 *intervalle, int *niveau, int *cpt);

/* Verification et affichage du statut */
int partie_perdue(struct plateau plateau_jeu[HAUTEUR][LARGEUR]);

#endif