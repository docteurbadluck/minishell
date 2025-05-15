CC = cc
CFLAGS = -g -Iincludes -I/usr/local/opt/readline/include -Wall -Wextra -Werror
LIBFT = -Llibft- -lft
READLINE = -L/usr/local/opt/readline/lib -lreadline

HEADERS = includes/minishell.h
BUILD_DIR = build

# Source files with updated structure
SRC = srcs/builtins/1_ft_echo.c srcs/builtins/2_ft_cd.c srcs/builtins/3_ft_pwd.c \
	srcs/builtins/4_env_insert.c srcs/builtins/4_env_operations.c srcs/builtins/4_env_utils.c \
	srcs/builtins/4_linked_list_utils.c srcs/builtins/4_memory_management.c srcs/builtins/5_exp_operations_helper.c \
	srcs/builtins/5_exp_operations.c srcs/builtins/6_ft_unset.c srcs/builtins/7_ft_exit.c \
	srcs/execution/paths.c srcs/execution/3_1_builtins.c srcs/execution/3_2_input.c \
	srcs/execution/3_3_output.c srcs/execution/3_4_parent.c srcs/execution/3_5_remove.c srcs/execution/3_0_execution.c \
	srcs/execution/0_preparation.c srcs/execution/1_setup.c srcs/execution/2_ast.c \
	srcs/parsing/A_variable_manager_helper.c \
	srcs/parsing/A_Amain.c srcs/parsing/A_variable_manager.c srcs/parsing/Cc_cut.c\
	srcs/parsing/B_wildcard_manager.c srcs/parsing/Ba_wildcard_util.c srcs/parsing/Bc_set_wildcard.c \
	srcs/parsing/Bd_set_wildcard_utils.c srcs/parsing/Be_free.c srcs/parsing/Ca_count_word_valid_quote.c \
	srcs/parsing/Cb_count_word_utils.c srcs/parsing/D_tokenise.c srcs/parsing/Da_tokenise_utils.c \
	srcs/parsing/Dc_split_op_utils.c \
	srcs/parsing/E_set_logic_op.c srcs/parsing/F_set_groupid_control_logic.c \
	srcs/parsing/Fa_set_groupid_control_logic.c srcs/parsing/G_group_up.c \
	srcs/parsing/Ga_group_up_utils.c srcs/parsing/Gb_group_up_count.c \
	srcs/parsing/H_from_input_to_group.c srcs/parsing/Ha_set_outfiles.c \
	srcs/parsing/Hb_set_outfiles_utils.c srcs/parsing/Hc_process_filename.c \
	srcs/parsing/I_from_group_to_polish_reverse.c srcs/parsing/Ia_to_polish_reverse_utils.c \
	srcs/parsing/J_from_polish_to_tree.c srcs/parsing/K_from_text_to_tree.c \
	srcs/parsing/L_print_tree.c srcs/execution/3_6_validate_permission_direc.c \
	srcs/X_free_new_array.c srcs/Xa_free_new_array_utils.c \
	  srcs/parsing/Db_split_word.c\
	srcs/signal_and_input/Na_input_count_heredoc.c srcs/signal_and_input/Nb_input_util.c srcs/signal_and_input/N_input.c \
	srcs/signal_and_input/Ma_signal_handler.c srcs/signal_and_input/M_signal.c \
	srcs/signal_and_input/Oa_heredoc_utils.c srcs/signal_and_input/O_heredoc.c \
	srcs/signal_and_input/P_name_generator.c

# Object files in the build directory
OBJ_FILES = $(SRC:srcs/%.c=$(BUILD_DIR)/%.o)

# Output executable
NAME = minishell

# Default rule
all: lib create-dir $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(READLINE) -o $(NAME)

# Rule to compile .c files into .o files in the build directory
$(BUILD_DIR)/%.o: srcs/%.c $(HEADERS)
	@mkdir -p $(@D) # Ensure subdirectories in build/ exist
	$(CC) $(CFLAGS) -c $< -o $@

# Build the libft library
lib:
	@make -C libft- > /dev/null 2>&1

# Create the build directory
create-dir:
	mkdir -p $(BUILD_DIR)
	mkdir -p tmp

# Clean object files
clean:
	rm -f $(OBJ_FILES)

# Full cleanup
fclean: clean
	rm -f $(NAME)

# Full rebuild
re: fclean all

.PHONY: all clean fclean re
