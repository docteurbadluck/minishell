CC = cc
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    CFLAGS = -g -Iincludes -I/usr/local/opt/readline/include -Wall -Wextra -Werror
    READLINE = -L/usr/local/opt/readline/lib -lreadline
    READLINE_HEADER = /usr/local/opt/readline/include/readline/readline.h
else
    CFLAGS = -g -Iincludes -Wall -Wextra -Werror
    READLINE = -lreadline
    READLINE_HEADER = /usr/include/readline/readline.h
endif
LIBFT = -Llibft- -lft

HEADERS = includes/minishell.h
BUILD_DIR = build

# Source files with updated structure
SRC = srcs/builtins/1_ft_echo.c srcs/builtins/2_ft_cd.c srcs/builtins/3_ft_pwd.c \
	srcs/builtins/4_env/1_env_insert.c srcs/builtins/4_env/2_env_operations.c srcs/builtins/4_env/3_env_utils.c \
	srcs/builtins/4_env/4_linked_list_utils.c srcs/builtins/4_env/5_memory_management.c srcs/builtins/5_export/2_exp_operations_helper.c \
	srcs/builtins/5_export/1_exp_operations.c srcs/builtins/6_ft_unset.c srcs/builtins/7_ft_exit.c \
	srcs/execution/3_paths.c srcs/execution/exec/1_execution.c srcs/execution/exec/2_builtins.c \
	srcs/execution/exec/3_input.c srcs/execution/exec/4_output.c srcs/execution/exec/5_parent.c \
	srcs/execution/exec/6_remove.c srcs/execution/exec/7_validate_permission_direc.c \
	srcs/execution/0_preparation.c srcs/execution/1_setup.c srcs/execution/2_ast.c \
	srcs/parsing/variable/1_variable_manager.c srcs/parsing/variable/2_variable_manager_helper.c \
	srcs/parsing/A_Amain.c \
	srcs/parsing/wildcard/1_wildcard_manager.c srcs/parsing/wildcard/2_wildcard_util.c \
	srcs/parsing/wildcard/3_set_wildcard.c srcs/parsing/wildcard/4_set_wildcard_utils.c \
	srcs/parsing/wildcard/5_free.c \
	srcs/parsing/1_tokenise/1_count_word_valid_quote.c srcs/parsing/1_tokenise/2_count_word_utils.c \
	srcs/parsing/1_tokenise/3_cut.c srcs/parsing/1_tokenise/4_tokenise.c \
	srcs/parsing/1_tokenise/5_tokenise_utils.c srcs/parsing/1_tokenise/6_split_word.c \
	srcs/parsing/1_tokenise/7_split_op_utils.c \
	srcs/parsing/2_group_up/1_set_logic_op.c srcs/parsing/2_group_up/2_set_groupid_control_logic.c \
	srcs/parsing/2_group_up/3_set_groupid_control_logic_utils.c srcs/parsing/2_group_up/4_group_up.c \
	srcs/parsing/2_group_up/5_group_up_utils.c srcs/parsing/2_group_up/6_group_up_count.c \
	srcs/parsing/2_group_up/7_from_input_to_group.c srcs/parsing/2_group_up/8_set_outfiles.c \
	srcs/parsing/2_group_up/9_set_outfiles_utils.c srcs/parsing/2_group_up/10_process_filename.c \
	srcs/parsing/3_build_tree/1_from_group_to_polish_reverse.c srcs/parsing/3_build_tree/2_to_polish_reverse_utils.c \
	srcs/parsing/3_build_tree/3_from_polish_to_tree.c srcs/parsing/3_build_tree/4_from_text_to_tree.c \
	srcs/parsing/3_build_tree/5_print_tree.c \
	srcs/free/1_free_new_array.c srcs/free/2_free_new_array_utils.c \
	srcs/signal_and_input/input/1_input.c srcs/signal_and_input/input/2_input_count_heredoc.c \
	srcs/signal_and_input/input/3_input_util.c \
	srcs/signal_and_input/signal/1_signal.c srcs/signal_and_input/signal/2_signal_handler.c \
	srcs/signal_and_input/heredoc/1_heredoc.c srcs/signal_and_input/heredoc/2_heredoc_utils.c \
	srcs/signal_and_input/heredoc/3_name_generator.c

# Object files in the build directory
OBJ_FILES = $(SRC:srcs/%.c=$(BUILD_DIR)/%.o)

# Output executable
NAME = minishell

# Default rule
all: check-readline lib create-dir $(NAME)

check-readline:
	@if [ ! -f "$(READLINE_HEADER)" ]; then \
		echo "readline not found, installing..."; \
		sudo apt-get install -y libreadline-dev; \
	fi

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(READLINE) -o $(NAME)

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

install-deps:
	sudo apt-get install -y libreadline-dev

test:
	@make -C test test

tester:
	@make -C test tester

signals:
	@make -C test signals

signals-view:
	@make -C test signals-view

check:
	@bash check.sh

.PHONY: all check-readline clean fclean re install-deps test tester signals signals-view check
