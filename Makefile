CC = cc

LIBFT = -Llibft -lft

CFLAGS = -Wall -Wextra -Werror

SRC = srcs/variable_manager
HEADERS = includes/minishell.h
BUILD_DIR = build

# Liste des fichiers objets avec le répertoire build
OBJ_FILES = $(SRC:srcs/%.c=$(BUILD_DIR)/%.o)

NAME = $(BUILD_DIR)/minishell

# Règle par défaut pour créer l'exécutable
all: lib create-dir $(NAME) 
	

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)

# Règle pour compiler un fichier .c en .o dans build/
$(BUILD_DIR)/%.o: srcs/%.c $(HEADERS)
	$(CC) -c $< -o $@

# Nettoyage des fichiers objets dans build/
lib:
	@make -C libft > /dev/null 2>&1

create-dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(OBJ_FILES)

# Nettoyage complet (objets + exécutable dans build/)
fclean: clean
	rm -f $(NAME)

# Rebuild complet
re: fclean all

.PHONY: all clean fclean re