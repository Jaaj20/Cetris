#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "tetris.h"
#include "deplacements.h"

/* Affiche une piece */
void afficher_piece(struct piece tetromino, struct color color_tab, SDL_Renderer *renderer);

/* Affiche une pièce au fond du tableau */
void afficher_viseur(struct piece *p_tetromino, struct color color_tab[], struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], SDL_Renderer *renderer);

/* Affiche la prochaine pièce */
void afficher_preview(struct piece tetromino, struct color color_tab, SDL_Renderer *renderer);

/* Affiche le plateau */
void afficher_plateau(struct color color_tab[], struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], SDL_Renderer *renderer);

/* Affiche un texte dans la fenêtre */
void afficher_texte(char Text[64], int SZofText, TTF_Font *police, SDL_Color color, float posX, float posY, SDL_Renderer *renderer);

/* Afficher un nombre dans la fenêtre */
void afficher_nbr(int nbr, char Text[64], int SZofText, TTF_Font *police, SDL_Color color, float posX, float posY, SDL_Renderer *renderer);

/* Affiche un écran d'accueil */
void start_screen(int *start_game, int *end_game, char Text[64], int SZofText, TTF_Font *police, SDL_Color color, SDL_Renderer *renderer);

/* Affiche un menu pause */
void menu_pause(int *pause, int *end_game, int *retour_accueil, char Text[64], int SZofText, TTF_Font *police, SDL_Color color, SDL_Renderer *renderer);

#endif