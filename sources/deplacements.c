#include "../headers/tetris.h"

int descendre(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino)
{
    int i;
    /* Verification des cases libres en dessous de la pièce */
    for (i = 0; i < 4; i++)
    {
        int col = (*p_tetromino).la_piece[i].colonne;
        int lig = (*p_tetromino).la_piece[i].ligne;
        if (plateau_jeu[p_tetromino->pos_ligne + lig + 1][p_tetromino->pos_colonne + col].carre != VIDE || lig == (HAUTEUR - 1))
        {
            return 0;
        }
    }
    for (i = 0; i < 4; i++)
    {
        /* Descente de la pièce */
        (*p_tetromino).la_piece[i].ligne += 1;
    }
    return 1;
}

void decaler_gauche(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino)
{
    int i;
    int libre = 1;
    /* Verification des cases libres autour de la pièce */
    for (i = 0; i < 4; i++)
    {
        int col = (*p_tetromino).la_piece[i].colonne;
        int lig = (*p_tetromino).la_piece[i].ligne;
        if ((col == -4) || (plateau_jeu[p_tetromino->pos_ligne + lig][p_tetromino->pos_colonne + col - 1].carre != VIDE))
        {
            libre = 0;
        }
    }
    /* Déplacement de la pièce */
    if (libre)
    {
        for (i = 0; i < 4; i++)
        {
            (*p_tetromino).la_piece[i].colonne -= 1;
        }
    }
}

void decaler_droite(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino)
{
    int i;
    int libre = 1;
    /* Verification des cases libres autour de la pièce*/
    for (i = 0; i < 4; i++)
    {
        int col = (*p_tetromino).la_piece[i].colonne;
        int lig = (*p_tetromino).la_piece[i].ligne;
        if ((col == 5) || (plateau_jeu[p_tetromino->pos_ligne + lig][p_tetromino->pos_colonne + col + 1].carre != VIDE))
        {
            libre = 0;
        }
    }
    /* Déplacement de la pièce */
    if (libre)
    {
        for (i = 0; i < 4; i++)
        {
            (*p_tetromino).la_piece[i].colonne += 1;
        }
    }
}

void rotation_gauche(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino)
{
    int i = 0;
    int libre = 0;
    struct une_case pos_tab[4];

    for (i = 0; i < 4; i++)
    {
        /* Obtention des coordonnées du centre la pièce */
        int cc = p_tetromino->la_piece[1].colonne;
        int cl = p_tetromino->la_piece[1].ligne;

        /* Différence entre les coordonnées du bloc de la piece et son centre
         pour obtenir les coordonnées relatives de chaque bloc */
        int col = (*p_tetromino).la_piece[i].colonne - cc;
        int lig = (*p_tetromino).la_piece[i].ligne - cl;

        /* Calcul des coordonnées post rotation */
        int abs_lig = p_tetromino->pos_ligne - col;
        int abs_col = p_tetromino->pos_colonne + lig;
        abs_col += cc;
        abs_lig += cl;

        /* Vérification que les cases occupées par la pièce post rotation soient libres */
        if (abs_lig >= 0 && abs_lig < HAUTEUR && abs_col >= 0 && abs_col < LARGEUR / 2 && plateau_jeu[abs_lig][abs_col].carre == VIDE)
        {
            libre++;
            pos_tab[i].colonne = lig + cc;
            pos_tab[i].ligne = -col + cl;
        }
    }
    /* Application de la rotation */
    for (i = 0; i < 4; i++)
    {
        if (libre == 4 && (p_tetromino->type != 0))
        {
            (*p_tetromino).la_piece[i].colonne = pos_tab[i].colonne;
            (*p_tetromino).la_piece[i].ligne = pos_tab[i].ligne;
        }
    }
}

void rotation_droite(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino)
{
    int i = 0;
    int libre = 0;
    struct une_case pos_tab[4];

    for (i = 0; i < 4; i++)
    {
        /* Obtention des coordonnées du centre la pièce */
        int cc = p_tetromino->la_piece[1].colonne;
        int cl = p_tetromino->la_piece[1].ligne;

        /* Différence entre les coordonnées du bloc de la piece et son centre
         pour obtenir les coordonnées relatives de chaque bloc */
        int col = (*p_tetromino).la_piece[i].colonne - cc;
        int lig = (*p_tetromino).la_piece[i].ligne - cl;

        /* Calcul des coordonnées post rotation */
        int abs_col = p_tetromino->pos_colonne - lig;
        int abs_lig = p_tetromino->pos_ligne + col;
        abs_col += cc;
        abs_lig += cl;

        /* Vérification que les cases occupées par la pièce post rotation soient libres */
        if (abs_lig >= 0 && abs_lig < HAUTEUR && abs_col >= 0 && abs_col < LARGEUR / 2 && plateau_jeu[abs_lig][abs_col].carre == VIDE)
        {
            libre++;
            pos_tab[i].colonne = -lig + cc;
            pos_tab[i].ligne = col + cl;
        }
    }
    /* Application de la rotation */
    for (i = 0; i < 4; i++)
    {
        if (libre == 4 && (p_tetromino->type != 0))
        {
            (*p_tetromino).la_piece[i].colonne = pos_tab[i].colonne;
            (*p_tetromino).la_piece[i].ligne = pos_tab[i].ligne;
        }
    }
}

void hard_drop(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], struct piece *p_tetromino)
{
    /* Pretty much straightforward */
    int descente;
    do
    {
        descente = descendre(plateau_jeu, p_tetromino);
    } while (descente == 1);
}