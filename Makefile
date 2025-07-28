# Nom de l'exécutable
EXEC_WIN = Cetris.exe
EXEC_LINUX = Cetris

# Répertoire des sources
SRC_DIR = sources

# Fichiers source et objets
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Commande et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -g -I./SDL2/include/SDL2 -I./SDL2ttf/include
LDFLAGS_WIN = -L./SDL2/lib -L./SDL2ttf/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mconsole
LDFLAGS_LINUX = -lSDL2 -lSDL2_ttf

# Cible par défaut
all: $(EXEC_WIN)

# Compilation de l'exécutable à partir des .o
$(EXEC_WIN): $(OBJ)
	@echo "Fichiers objets : $(OBJ)"
	@echo "Création de l'exécutable $(EXEC_WIN)..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS_WIN)

linux: 
	$(MAKE) clean
	$(MAKE) $(EXEC_LINUX)

$(EXEC_LINUX): $(OBJ)
	@echo "Fichiers objets : $(OBJ)"
	@echo "Création de l'exécutable : $(EXEC_LINUX)..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS_LINUX)


$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer pour PowerShell / cmd
clean:
	@rm -f $(SRC_DIR)/*.o $(EXEC_LINUX) $(EXEC_WIN)

rebuild: clean all
