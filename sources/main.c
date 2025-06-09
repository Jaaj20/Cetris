#include "../headers/tetris.h"
#include "../headers/evenements.h"
#include "../headers/affichage.h"
#include "../headers/deplacements.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);

    if (TTF_Init() == -1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    /* DECLARATIONS */

    int indice; /* l'indice (type) de la piece jouee */

    /* Actions du Joueur */
    int GotoLeft = FALSE;
    int GotoRight = FALSE;
    int RotateLeft = FALSE;
    int RotateRight = FALSE;
    int GoDown = FALSE;
    int HardDrop = FALSE;
    int NewGame = FALSE;

    /* Fonctionnement de la boucle */
    int descente_OK = 1; /* determine si la piece peut encore descendre */
    int start_game = 0; /* passe a 1 lorsque l'utilisateur appuie sur ESPACE dans l'écran d'accueil */
    int end_game = 0;     /* passe a 1 si l'utilsateur utilise la touche ESCAPE permet un arret premature de la partie  */
    int cpt = 0, niveau = 0, score = 0;
    SDL_TimerID horloge;     /* l'identifiant de l'horloge qui cadence la chute des pieces */
    Uint32 intervalle = 500; /* la periode de l'horloge (en ms) */

    /* Besoins de SDL */
    SDL_Event event; /* l'evenement a traiter */
    SDL_Renderer *renderer = NULL;

    /* Allocation de l'espace du texte */
    char Text[64];
    int SZofText = sizeof(Text);
    float posX, posY;

    struct plateau plateau_jeu[HAUTEUR][LARGEUR / 2];
    struct piece tetromino;
    struct piece preview;

    /* INITIALISATIONS */

    struct une_case tab_pieces[7][4] = {
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, // O
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, // I
        {{0, 0}, {0, 1}, {0, 2}, {1, 2}}, // L
        {{1, 0}, {1, 1}, {1, 2}, {0, 2}}, // J
        {{0, 1}, {1, 1}, {1, 0}, {2, 0}}, // Z
        {{0, 0}, {1, 0}, {1, 1}, {2, 1}}, // S
        {{0, 1}, {1, 0}, {1, 1}, {2, 1}}, // T
    };

    struct color color_tab[] = {
        {"yellow", 255, 233, 38},
        {"cyan", 0, 255, 255},
        {"orange", 255, 140, 0},
        {"blue", 0, 0, 255},
        {"red", 255, 0, 0},
        {"lime green", 50, 205, 50},
        {"fuchsia", 255, 0, 255},
        {"black", 0, 0, 0},
        {"dark grey", 50, 50, 50}};

    for (int i = 0; i < HAUTEUR; i++)
    {
        for (int j = 0; j < LARGEUR / 2; j++)
        {
            plateau_jeu[i][j].carre = VIDE;
        }
    }

    /* OUVERTURE DE LA FENETRE GRAPHIQUE */

    /*Creation de la fenetre */
    SDL_Window *fenetre = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR * TAILLE_CASE, HAUTEUR * TAILLE_CASE, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    /* at_top_horloge est appelee a chaque echeance de intervalle */
    horloge = SDL_AddTimer(intervalle, at_top_horloge, NULL);

    TTF_Font *police = TTF_OpenFont("SDL2ttf/Minecraft.ttf", 24);
    if (police == NULL)
    {
        fprintf(stderr, "ERREUR FATALE : Impossible de charger la police. TTF_OpenFont: %s\n", TTF_GetError());
    }

    /* BOUCLE DE JEU */

    /* Choix et creation de la piece */
    indice = rand() % 7;
    initialiser(&tetromino, tab_pieces[indice], indice);
    indice = rand() % 7;
    initialiser(&preview, tab_pieces[indice], indice);

    /* Lecture des actions */
    do
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT: /* Appui sur la croix de la fenêtre */
                end_game = 1;
                break;
            case SDL_USEREVENT: /* Aucune action du Joueur */
                GoDown = TRUE;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_DOWN: /* Descente forcée */
                    GoDown = TRUE;
                    break;
                case SDLK_LEFT: /* Aller a gauche */
                    GotoLeft = TRUE;
                    break;
                case SDLK_RIGHT: /* Aller a droite */
                    GotoRight = TRUE;
                    break;
                case SDLK_d: /* Rotation sens anti-horaire */
                    RotateLeft = TRUE;
                    break;
                case SDLK_g: /* Rotation sens horaire */
                    RotateRight = TRUE;
                    break;
                case SDLK_SPACE: /* Hard Drop */
                    HardDrop = TRUE;
                    break;
                case SDLK_ESCAPE: /* Fermeture forcée du jeu */
                    end_game = 1;
                    break;
                default:
                    break;
                }
            }
        }

        /* Gestion des actions */
        if (GoDown)
        {
            descente_OK = descendre(plateau_jeu, &tetromino);
            if (!descente_OK)
            {
                /* Sauvegarde de la pièce dans le plateau */
                for (int i = 0; i < 4; i++)
                {
                    int lig = tetromino.pos_ligne + tetromino.la_piece[i].ligne;
                    int col = tetromino.pos_colonne + tetromino.la_piece[i].colonne;
                    if (lig >= 0 && lig < HAUTEUR && col >= 0 && col < LARGEUR / 2)
                    {
                        plateau_jeu[lig][col].carre = tetromino.type;
                    }
                }

                /* Suppression des lignes et maj du score */
                cpt += supprimer_lignes(plateau_jeu, &score);

                /* on verifie si la partie est perdue */
                if (partie_perdue(plateau_jeu) != 0)
                {
                    while (!NewGame && !end_game)
                    {
                        SDL_WaitEvent(&event);
                        switch (event.type)
                        {
                        case SDL_QUIT:
                            end_game = 1;
                            break;
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym)
                            {
                            case SDLK_ESCAPE:
                                end_game = 1;
                                break;
                            case SDLK_r:
                                NewGame = TRUE;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }

                /* on genère une nouvelle pièce */
                tetromino = preview;
                indice = rand() % 7;
                initialiser(&preview, tab_pieces[indice], indice);
            }
            GoDown = FALSE;
        }

        if (GotoLeft)
        {
            decaler_gauche(plateau_jeu, &tetromino);
            GotoLeft = FALSE;
        }

        if (GotoRight)
        {
            decaler_droite(plateau_jeu, &tetromino);
            GotoRight = FALSE;
        }
        if (RotateLeft)
        {
            rotation_gauche(plateau_jeu, &tetromino);
            RotateLeft = FALSE;
        }

        if (RotateRight)
        {
            rotation_droite(plateau_jeu, &tetromino);
            RotateRight = FALSE;
        }

        if (HardDrop)
        {
            hard_drop(plateau_jeu, &tetromino);

            /* Sauvegarde de la pièce dans le plateau */
            for (int i = 0; i < 4; i++)
            {
                int lig = tetromino.pos_ligne + tetromino.la_piece[i].ligne;
                int col = tetromino.pos_colonne + tetromino.la_piece[i].colonne;
                if (lig >= 0 && lig < HAUTEUR && col >= 0 && col < LARGEUR / 2)
                {
                    plateau_jeu[lig][col].carre = tetromino.type;
                }
            }

            /* Suppression des lignes et maj du score */
            cpt += supprimer_lignes(plateau_jeu, &score);

            /* on verifie si la partie est perdue */
            if (partie_perdue(plateau_jeu) != 0)
            {
                while (!NewGame && !end_game)
                {
                    SDL_WaitEvent(&event);
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        end_game = 1;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            end_game = 0;
                            break;
                        case SDLK_r:
                            NewGame = TRUE;
                            break;
                        default:
                            break;
                        }
                    }
                }
            }

            /* on genère une nouvelle pièce */
            tetromino = preview;
            indice = rand() % 7;
            initialiser(&preview, tab_pieces[indice], indice);
            HardDrop = FALSE;
        }

        if (NewGame)
        {
            for (int i = 0; i < HAUTEUR; i++)
            {
                for (int j = 0; j < LARGEUR / 2; j++)
                {
                    plateau_jeu[i][j].carre = VIDE;
                }
            }
            indice = rand() % 7;
            initialiser(&tetromino, tab_pieces[indice], indice);
            indice = rand() % 7;
            initialiser(&preview, tab_pieces[indice], indice);
            cpt = 0, niveau = 0, score = 0;

            NewGame = FALSE;
        }

        /* Gestion des niveaux */
        if (cpt >= CHANGEMENT_NIVEAU)
        {
            SDL_RemoveTimer(horloge);
            intervalle = intervalle - DIMINUTION_PERIODE;
            if (intervalle < 50)
                intervalle = 50; // Ajout d'une limite minimale
            horloge = SDL_AddTimer(intervalle, at_top_horloge, NULL);
            niveau++;
            cpt = cpt - CHANGEMENT_NIVEAU;
        }

        /* Gestion du rendu graphique*/
        if (!end_game)
        {
            SDL_RenderClear(renderer);
            afficher_plateau(color_tab, plateau_jeu, renderer);

            SDL_Color white = {255, 255, 255, 255};

            strcpy(Text, "Score:");
            posX = 2.6 * (LARGEUR * TAILLE_CASE) / 4, posY = (HAUTEUR * TAILLE_CASE) / 2;
            afficher_texte(Text, SZofText, police, white, posX, posY, renderer);

            posY += 25;
            afficher_nbr(score, Text, SZofText, police, white, posX, posY, renderer);

            strcpy(Text, "Niveau:");
            posY += 25;
            afficher_texte(Text, SZofText, police, white, posX, posY, renderer);

            posY += 25;
            afficher_nbr(niveau, Text, SZofText, police, white, posX, posY, renderer);

            afficher_preview(preview, color_tab[preview.type], renderer);
            afficher_viseur(&tetromino, color_tab, plateau_jeu, renderer);
            afficher_piece(tetromino, color_tab[tetromino.type], renderer);

            SDL_SetRenderDrawColor(renderer, color_tab[7].r, color_tab[7].g, color_tab[7].b, 255);
            SDL_RenderPresent(renderer);
        }

    } while (!end_game);

    TTF_CloseFont(police);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    TTF_Quit();
    SDL_Quit();
    return 0;
}