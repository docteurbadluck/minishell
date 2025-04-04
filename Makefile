CC = cc

LIBFT = -Llibft -lft

READLINE = -lreadline

CFLAGS = -Wall -Wextra -Werror

SRC = srcs/A_variable_manager.c  srcs/A_Amain.c srcs/B_wildcard_manager.c srcs/Ba_wildcard_util.c \
	srcs/Bc_set_wildcard.c srcs/Bd_set_wildcard_utils.c srcs/Be_free.c srcs/Ca_count_word_valid_quote.c \
	srcs/Cb_count_word_utils.c srcs/D_tokenise.c srcs/Da_tokenise_utils.c srcs/E_set_logic_op.c \
	srcs/F_set_groupid_control_logic.c srcs/Fa_set_groupid_control_logic.c srcs/G_group_up.c srcs/Ga_group_up_utils.c \
	srcs/Gb_group_up_count.c srcs/H_from_input_to_group.c srcs/Ha_set_outfiles.c \
	srcs/I_from_group_to_polish_reverse.c srcs/Ia_to_polish_reverse_utils.c \
	srcs/J_from_polish_to_tree.c srcs/K_from_text_to_tree.c srcs/L_print_tree.c srcs/X_free_new_array.c

HEADERS = includes/minishell.h
BUILD_DIR = build

# Liste des fichiers objets avec le répertoire build
OBJ_FILES = $(SRC:srcs/%.c=$(BUILD_DIR)/%.o)

NAME = $(BUILD_DIR)/minishell

# Règle par défaut pour créer l'exécutable
all: lib create-dir $(NAME) 
	

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(READLINE) -o $(NAME)

# Règle pour compiler un fichier .c en .o dans build/
$(BUILD_DIR)/%.o: srcs/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

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