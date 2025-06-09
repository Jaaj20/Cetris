#include "../headers/tetris.h"
#include "../headers/deplacements.h"

/* Affiche une piece */
void afficher_piece(struct piece tetromino, struct color color_tab, SDL_Renderer *renderer)
{
    int i;
    int ligne_deb, colonne_deb;

    for (i = 0; i < 4; i++)
    {
        ligne_deb = (tetromino.pos_ligne + tetromino.la_piece[i].ligne) * TAILLE_CASE;
        colonne_deb = (tetromino.pos_colonne + tetromino.la_piece[i].colonne) * TAILLE_CASE;
        SDL_Rect rect = {colonne_deb, ligne_deb, TAILLE_CASE, TAILLE_CASE};
        SDL_SetRenderDrawColor(renderer, color_tab.r, color_tab.g, color_tab.b, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void afficher_preview(struct piece tetromino, struct color color_tab, SDL_Renderer *renderer)
{
    int i;
    int ligne_deb, colonne_deb;
    tetromino.pos_ligne = 2;
    tetromino.pos_colonne = 14;

    for (i = 0; i < 4; i++)
    {
        ligne_deb = (tetromino.pos_ligne + tetromino.la_piece[i].ligne) * TAILLE_CASE;
        colonne_deb = 10 + (tetromino.pos_colonne + tetromino.la_piece[i].colonne) * TAILLE_CASE;
        SDL_Rect rect = {colonne_deb, ligne_deb, TAILLE_CASE, TAILLE_CASE};
        SDL_SetRenderDrawColor(renderer, color_tab.r, color_tab.g, color_tab.b, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void afficher_plateau(struct color color_tab[], struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], SDL_Renderer *renderer)
{
    int col;
    int lig;
    SDL_Rect rect;

    for (lig = 0; lig < HAUTEUR; lig++)
    {
        /* Plateau de Jeu */
        for (col = 0; col < LARGEUR / 2; col++)
        {
            rect = (SDL_Rect){col * TAILLE_CASE, lig * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE};
            SDL_SetRenderDrawColor(renderer, color_tab[plateau_jeu[lig][col].carre].r, color_tab[plateau_jeu[lig][col].carre].g, color_tab[plateau_jeu[lig][col].carre].b, 255);
            SDL_RenderFillRect(renderer, &rect);
            }
        
        /* Ligne de séparation entre plateau de jeu et l'affiche de la preview/score */
        rect = (SDL_Rect){(LARGEUR / 2) * TAILLE_CASE, lig * TAILLE_CASE, TAILLE_CASE / 2, TAILLE_CASE};
        SDL_SetRenderDrawColor(renderer, color_tab[8].r, color_tab[8].g, color_tab[8].b, 255);
        SDL_RenderFillRect(renderer, &rect);

        /* Encadré de la preview */
        if (lig == 1)
        {
            rect = (SDL_Rect){265, lig * TAILLE_CASE, 90, TAILLE_CASE / 4};
            SDL_RenderFillRect(renderer, &rect);

            rect = (SDL_Rect){265, lig * TAILLE_CASE, TAILLE_CASE / 4, TAILLE_CASE};
            SDL_RenderFillRect(renderer, &rect);
            rect = (SDL_Rect){350, lig * TAILLE_CASE, TAILLE_CASE / 4, TAILLE_CASE};
            SDL_RenderFillRect(renderer, &rect);
        }
        if (lig > 1 && lig < 6)
        {
            rect = (SDL_Rect){265, lig * TAILLE_CASE, TAILLE_CASE / 4, TAILLE_CASE};
            SDL_RenderFillRect(renderer, &rect);

            rect = (SDL_Rect){350, lig * TAILLE_CASE, TAILLE_CASE / 4, TAILLE_CASE};
            SDL_RenderFillRect(renderer, &rect);
        }
        if (lig == 6)
        {
            rect = (SDL_Rect){265, lig * TAILLE_CASE, 90, TAILLE_CASE / 4};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void afficher_texte(char Text[64], int SZofText, TTF_Font *police, SDL_Color color, float posX, float posY, SDL_Renderer *renderer)
{
    snprintf(Text, SZofText, Text);
    SDL_Surface *surfaceTexte = TTF_RenderText_Blended(police, Text, color);
    if (surfaceTexte == NULL)
    {
        fprintf(stderr, "Erreur création surface texte: %s\n", TTF_GetError());
    }
    else
    {
        SDL_Texture *textureTexte = SDL_CreateTextureFromSurface(renderer, surfaceTexte);
        if (textureTexte == NULL)
        {
            fprintf(stderr, "Erreur création texture texte: %s\n", SDL_GetError());
        }
        else
        {

            SDL_Rect destRect;
            destRect.x = posX; /* Position X (à partir du coin supérieur gauche) */
            destRect.y = posY; /* Position Y (à partir du coin supérieur gauche) */
            /* Prend la largeur et hauteur depuis la texture créée */

            SDL_QueryTexture(textureTexte, NULL, NULL, &destRect.w, &destRect.h);

            SDL_RenderCopy(renderer, textureTexte, NULL, &destRect);
            SDL_DestroyTexture(textureTexte);
        }
        SDL_FreeSurface(surfaceTexte);
    }
}

void afficher_nbr(int nbr, char Text[64], int SZofText, TTF_Font *police, SDL_Color color, float posX, float posY, SDL_Renderer *renderer)
{
    snprintf(Text, SZofText, "%d", nbr);
    SDL_Surface *surfaceTexte = TTF_RenderText_Blended(police, Text, color);
    if (surfaceTexte == NULL)
    {
        fprintf(stderr, "Erreur création surface texte: %s\n", TTF_GetError());
    }
    else
    {
        SDL_Texture *textureTexte = SDL_CreateTextureFromSurface(renderer, surfaceTexte);
        if (textureTexte == NULL)
        {
            fprintf(stderr, "Erreur création texture texte: %s\n", SDL_GetError());
        }
        else
        {

            SDL_Rect destRect;
            destRect.x = posX; /* Position X (à partir du coin supérieur gauche) */
            destRect.y = posY; /* Position Y (à partir du coin supérieur gauche) */
            /* Prend la largeur et hauteur depuis la texture créée */
            SDL_QueryTexture(textureTexte, NULL, NULL, &destRect.w, &destRect.h);

            SDL_RenderCopy(renderer, textureTexte, NULL, &destRect);
            SDL_DestroyTexture(textureTexte);
        }
        SDL_FreeSurface(surfaceTexte);
    }
}

void startscreen(int *start_game, int *end_game, SDL_Event event, char Text[64], int SZofText, TTF_Font *police, SDL_Color color, SDL_Renderer *renderer)
{
    while(!(*end_game) && !(*start_game))
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT: /* Appui sur la croix de la fenêtre */
                *end_game = TRUE;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE: /* Descente forcée */
                    *start_game = TRUE;
                    break;
                case SDLK_ESCAPE: /* Fermeture forcée du jeu */
                    *end_game = TRUE;
                    break;
                default:
                    break;
                }
            }
        }
    }

    SDL_RenderClear(renderer);

    strcpy(Text, "CETRIS");
    afficher_texte(Text, SZofText, police, color, (LARGEUR/2)-25, (HAUTEUR/2)-50, renderer);
    
    strcpy(Text, "Appuyez sur ESPACE");
    afficher_texte(Text, SZofText, police, color, (LARGEUR/2)-25, (HAUTEUR/2), renderer);

    strcpy(Text, "ESC pour quitter");
    afficher_texte(Text, SZofText, police, color, 0, HAUTEUR-50, renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fond noir
    SDL_RenderPresent(renderer);
}

void afficher_viseur(struct piece *p_tetromino, struct color color_tab[], struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], SDL_Renderer *renderer)
{
    struct piece viseur = *p_tetromino;
    hard_drop(plateau_jeu, &viseur);
    afficher_piece(viseur, color_tab[8], renderer);
}
