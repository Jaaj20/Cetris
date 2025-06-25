# Nom de l'exécutable
EXEC = Cetris.exe

# Répertoire des sources
SRC_DIR = sources

# Fichiers source et objets
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Commande et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -I./SDL2/include/SDL2 -I./SDL2ttf/include
LDFLAGS = -L./SDL2/lib -L./SDL2ttf/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mconsole
# Cible par défaut
all: $(EXEC)

# Compilation de l'exécutable à partir des .o
$(EXEC): $(OBJ)
	@echo "Fichiers objets : $(OBJ)"
	@echo "Création de l'exécutable $(EXEC)..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des .c en .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer pour PowerShell / cmd
clean:
	@rm -f $(SRC_DIR)/*.o

rebuild: clean all
