#include "../headers/tetris.h"

Uint32 at_top_horloge(Uint32 interval, void *param)
{
    /* ajoute un evenement SDL_USEREVENT dans la file a l'echeance de l'horloge
        et reinitialise celle-ci a interval */
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = param;

    event.type = SDL_USEREVENT;
    event.user = userevent;
    SDL_PushEvent(&event);

    return interval;
}

void initialiser(struct piece *p_tetromino, struct une_case tab[4], int indice)
{
    int i;
    p_tetromino->pos_colonne = (LARGEUR / 4) - 1;
    p_tetromino->pos_ligne = 0;
    for (i = 0; i < 4; i++)
    {
        p_tetromino->la_piece[i] = tab[i];
    }

    p_tetromino->type = indice;
}

int supprimer_lignes(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], int *score)
{
    int lig, col, lig_suppr = 0;

    for (lig = 0; lig < HAUTEUR; lig++)
    {
        int rempli = 0;
        for (col = 0; col < LARGEUR / 2; col++)
        {
            if (plateau_jeu[lig][col].carre != VIDE)
                rempli++;
        }
        if (rempli == LARGEUR / 2)
        {
            /* suppression de la ligne */
            for (col = 0; col < LARGEUR / 2; col++)
            {
                plateau_jeu[lig][col].carre = VIDE;
            }
            /* décalage du tableau vers le bas */
            int indice = lig;
            for (lig = indice; lig > 0; lig--)
            {
                for (col = LARGEUR / 2 - 1; col >= 0; col--)
                {
                    plateau_jeu[lig][col].carre = plateau_jeu[lig - 1][col].carre;
                }
            }
            lig_suppr++;
        }

        /* Mise à jour du score */
        if (lig_suppr == 1)
            *score += 40;
        if (lig_suppr == 2)
            *score += 100;
        if (lig_suppr == 3)
            *score += 300;
        if (lig_suppr == 4)
            *score += 1200;
    }
    return lig_suppr;
}

int partie_perdue(struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2])
{
    for (int i = 0; i < LARGEUR / 2; i++)
    {
        if (plateau_jeu[0][i].carre != VIDE)
            return 1;
    }
    return 0;
}