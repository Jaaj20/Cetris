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

void start_screen(int *start_game, int *end_game, char Text[64], int SZofText, TTF_Font *police, SDL_Color color, SDL_Renderer *renderer)
{
    int posX, posY, w, h;
    while (!(*end_game) && !(*start_game))
    {
        SDL_Event event;
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
                case SDLK_SPACE: /* Démarrer */
                    *start_game = TRUE;
                    break;
                case SDLK_ESCAPE: /* Fermeture forcée du jeu */
                    *end_game = TRUE;
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fond noir
        SDL_RenderClear(renderer);

        TTF_SizeText(police, "CETRIS", &w, &h);
        posX = (LARGEUR * TAILLE_CASE - w) / 2;
        posY = (HAUTEUR * TAILLE_CASE / 2) - 50;
        strcpy(Text, "CETRIS");
        afficher_texte(Text, SZofText, police, color, posX, posY, renderer);

        TTF_SizeText(police, "Appuyez sur ESCAPE", &w, &h);
        posX = (LARGEUR * TAILLE_CASE - w) / 2;
        posY = (HAUTEUR * TAILLE_CASE / 2);
        strcpy(Text, "Appuyez sur ESPACE");
        afficher_texte(Text, SZofText, police, color, posX, posY, renderer);

        strcpy(Text, "ESC pour quitter");
        afficher_texte(Text, SZofText, police, color, 0, HAUTEUR * TAILLE_CASE - 25, renderer);

        SDL_RenderPresent(renderer);
    }
}

void afficher_viseur(struct piece *p_tetromino, struct color color_tab[], struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2], SDL_Renderer *renderer)
{
    struct piece viseur = *p_tetromino;
    hard_drop(plateau_jeu, &viseur);
    afficher_piece(viseur, color_tab[8], renderer);
}

void menu_pause(int *pause, int *end_game, int *retour_accueil, char Text[64], int SZofText, TTF_Font *police, SDL_Color color, SDL_Renderer *renderer)
{
    int choix = 0, selection = 0; // choix == 0 Reprendre, == 1 Retourner à l'écran d'accueil, ==2 Quitter le jeu
    SDL_Event event;
    int posX, posY, w, h;
    while (*pause && !(*end_game) && !(*retour_accueil))
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
                case SDLK_RETURN:
                    selection = TRUE;
                    break;
                case SDLK_ESCAPE:
                    *pause = FALSE;
                    break;
                case SDLK_DOWN:
                    if (choix < 2)
                        choix++;
                    else
                        choix = 0;
                    break;
                case SDLK_UP:
                    if (choix > 0)
                        choix--;
                    else
                        choix = 2;
                    break;
                default:
                    break;
                }
            }
        }

        posX = (LARGEUR * TAILLE_CASE / 2) - 40;
        posY = (HAUTEUR * TAILLE_CASE / 4);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fond noir
        SDL_RenderClear(renderer);
        
        TTF_SizeText(police, "> Reprendre", &w, &h);
        strcpy(Text, "Pause");
        afficher_texte(Text, SZofText, police, color, posX, posY, renderer);

        if (selection)
        {
            if (choix == 0)
            {
                *pause = FALSE;
            }
            if (choix == 1)
            {
                *retour_accueil = TRUE;
            }
            if (choix == 2)
            {
                *end_game = TRUE;
            }
        }

        if (choix == 0)
        {
            TTF_SizeText(police, "> Reprendre", &w, &h);
            posX = (LARGEUR * TAILLE_CASE - w) / 2;
            posY = (HAUTEUR * TAILLE_CASE / 2) - 20;
            strcpy(Text, "> Reprendre");
            afficher_texte(Text, SZofText, police, color, posX, posY, renderer);

            TTF_SizeText(police, "Ecran d'accueil", &w, &h);
            posX = (LARGEUR * TAILLE_CASE - w) / 2;
            posY = (HAUTEUR * TAILLE_CASE / 2);
            strcpy(Text, "Ecran d'accueil");
            afficher_texte(Text, SZofText, police, color, posX, posY, renderer);

            TTF_SizeText(police, "Quitter", &w, &h);
            posX = (LARGEUR * TAILLE_CASE - w) / 2;
            posY = (HAUTEUR * TAILLE_CASE / 2) + 20;
            strcpy(Text, "Quitter");
            afficher_texte(Text, SZofText, police, color, posX, posY, renderer);
        }
        if (choix == 1)
        {
            TTF_SizeText(police, "Reprendre", &w, &h);
            posX = (LARGEUR * TAILLE_CASE - w) / 2;
            posY = (HAUTEUR * TAILLE_CASE / 2) - 20;
            strcpy(Text, "Reprendre");
            afficher_texte(Text, SZofText, police, color, posX, posY, renderer);

            TTF_SizeText(police, "> Ecran d'accueil", &w, &h);
            posX = (LARGEUR * TAILLE_CASE - w) / 2;
            posY = (HAUTEUR * TAILLE_CASE / 2);
            strcpy(Text, "> Ecran d'accueil");
            afficher_texte(Text, SZofText, police, color, posX, posY, renderer);

            TTF_SizeText(police, "Quitter", &w, &h);
            posX = (LARGEUR * TAILLE_CASE - w) / 2;
            posY = (HAUTEUR * TAILLE_CASE / 2) + 20;
            strcpy(Text, "Quitter");
            afficher_texte(Text, SZofText, police, color, posX, posY, renderer);
        }
        if (choix == 2)
        {
            TTF_SizeText(police, "Reprendre", &w, &h);
            posX = (LARGEUR * TAILLE_CASE - w) / 2;
            posY = (HAUTEUR * TAILLE_CASE / 2) - 20;
            strcpy(Text, "Reprendre");
            afficher_texte(Text, SZofText, police, color, posX, posY, renderer);

            TTF_SizeText(police, "Ecran d'accueil", &w, &h);
            posX = (LARGEUR * TAILLE_CASE - w) / 2;
            posY = (HAUTEUR * TAILLE_CASE / 2);
            strcpy(Text, "Ecran d'accueil");
            afficher_texte(Text, SZofText, police, color, posX, posY, renderer);

            TTF_SizeText(police, "> Quitter", &w, &h);
            posX = (LARGEUR * TAILLE_CASE - w) / 2;
            posY = (HAUTEUR * TAILLE_CASE / 2) + 20;
            strcpy(Text, "> Quitter");
            afficher_texte(Text, SZofText, police, color, posX, posY, renderer);
        }

        SDL_RenderPresent(renderer);
    }
}