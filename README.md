# Cetris

Tetris codé en C en tant que projet perso pour apprendre le langage

## Prérequis
- SDL2 (https://github.com/libsdl-org/SDL/releases/tag/release-2.32.8)
- SDL2_ttf (https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.24.0)

## Installation et compilation
1. Télécharger les préréquis (liens fournis).

2. Créer le répertoire d'installation du jeu.
  
3. A l'intérieur de celui-ci, placer les dossier "include" et "lib" de chaque bibliothèque dans un autre dossier portant leur nom correspondant (ex: pour SDL2 avoir SDL2/include). Sinon vous pouvez adapter les paramètres de compilation dans le makefile pour correspondre a vos préférences.

4. Placer maintenant les fichiers .dll trouvables dans les dossiers "bin" de leur bibliothèque correspondante dans le répertoire du jeu.

5. Compiler avec make.

## Contrôles
Quitter: **ESC**

Recommencer une partie (a la fin de celle-ci): **R**

Descendre: **FLECHE BAS**

Droite: **FLECHE DROITE**

Gauche: **FLECHE GAUCHE**

Hard Drop: **ESPACE**

