#include "../headers/tetris.h"

Uint32 at_top_horloge(Uint32 intervalle, void *param)
{
    /* ajoute un evenement SDL_USEREVENT dans la file a l'echeance de l'horloge et reinitialise celle-ci a interval */
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = param;

    event.type = SDL_USEREVENT;
    event.user = userevent;
    SDL_PushEvent(&event);

    return intervalle;
}


void initialiser(struct piece *p_tetromino, struct une_case tab[4], int indice)
{
    int i;

    /* Position de la pièce dans le tableau */
    p_tetromino->pos_colonne = (LARGEUR / 2) - 1;
    p_tetromino->pos_ligne = 0;
    
    /* Construction des pièces */
    for (i = 0; i < 4; i++)
    {
        p_tetromino->la_piece[i] = tab[i];
    }

    /* Association du type de pièce */
    p_tetromino->type = indice;
}

void initialiser_partie(struct piece *tetromino, struct piece *preview, struct plateau plateau_jeu[HAUTEUR][LARGEUR], struct une_case tab_pieces[7][4], int *indice, int *cpt, int *niveau, int *score, Uint32 *intervalle)
{
    /* Remplissage du tableau de cases vides */
    for (int i = 0; i < HAUTEUR; i++)
    {
        for (int j = 0; j < LARGEUR; j++)
        {
            plateau_jeu[i][j].carre = VIDE;
        }
    }

    /* Création de la première pièce */
    *indice = rand() % 7;
    initialiser(tetromino, tab_pieces[*indice], *indice);

    /* Création de la preview */
    *indice = rand() % 7;
    initialiser(preview, tab_pieces[*indice], *indice);

    *cpt = 0, *niveau = 0, *score = 0, *intervalle = 500;
}

void sauvegarder_piece(struct piece tetromino, struct plateau plateau_jeu[HAUTEUR][LARGEUR])
{
    for (int i = 0; i < 4; i++)
    {
        int lig = tetromino.pos_ligne + tetromino.la_piece[i].ligne;
        int col = tetromino.pos_colonne + tetromino.la_piece[i].colonne;
        if (lig >= 0 && lig < HAUTEUR && col >= 0 && col < LARGEUR)
        {
            plateau_jeu[lig][col].carre = tetromino.type;
        }
    }
}

int supprimer_lignes(struct plateau plateau_jeu[HAUTEUR][LARGEUR], int *score)
{
    int lig, col, lig_suppr = 0;

    for (lig = 0; lig < HAUTEUR; lig++)
    {
        int rempli = 0;
        /* Vérification de la dernière ligne du tableau */
        for (col = 0; col < LARGEUR; col++)
        {
            if (plateau_jeu[lig][col].carre != VIDE)
                rempli++;
        }

         
        if (rempli == LARGEUR)
        {
            /* Suppression de la ligne */
            for (col = 0; col < LARGEUR; col++)
            {
                plateau_jeu[lig][col].carre = VIDE;
            }

            /* Décalage du tableau vers le bas */
            int indice = lig;
            for (lig = indice; lig > 0; lig--)
            {
                for (col = LARGEUR - 1; col >= 0; col--)
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

void changement_niveau(int *horloge, Uint32 *intervalle, int *niveau, int *cpt)
{
    SDL_RemoveTimer(*horloge);
    *intervalle -= DIMINUTION_PERIODE;                              // Augmentation de la vitesse
    if (*intervalle < 50)
        *intervalle = 50;                                           // Limite minimale
    *horloge = SDL_AddTimer(*intervalle, at_top_horloge, NULL);     
    *niveau += 1;                                                   // Augmentation de niveau
    *cpt -= CHANGEMENT_NIVEAU;                                      // Remise du compteur de lignes a zéro
}

int partie_perdue(struct plateau plateau_jeu[HAUTEUR][LARGEUR])
{
    for (int i = 0; i < LARGEUR; i++)
    {
        /* On verifie s'il y a des pièces sauvegardées a la première ligne du tableau */
        if (plateau_jeu[0][i].carre != VIDE)                        
            return 1;
    }
    return 0;
}