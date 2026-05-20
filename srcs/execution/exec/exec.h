#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "../execution.h"

/* ===== PUBLIC API ===== */

int		execute_command(t_parsed_command *command, t_ast_helper *ast_helper,
			t_env_exp *env_exp, t_free *free_all);

/* ===== INTERNAL HELPERS ===== */

/* 2_builtins.c */
int		check_build_in(char **command);
int		build_in_addition(char **command, t_env_exp *env_exp, int return_value);
int		execute_build_in(char **command, t_env_exp *env_exp, int return_value);

/* 3_input.c */
int		count_files(t_iofile *file);
void	handle_before_input_files(int num_files, t_iofile *file);
int		execute_command_input(t_parsed_command *command,
			t_ast_helper *ast_helper);

/* 4_output.c */
void	handle_before_output_files(int num_files, t_iofile *file);
void	handle_output_file(t_parsed_command *command);
int		execute_command_output(t_parsed_command *command,
			t_ast_helper *ast_helper);

/* 5_parent.c */
int		handle_parent_process(t_parsed_command *command,
			t_ast_helper *ast_helper, t_env_exp *env_exp, int return_value);
int		execute_command_parent(t_parsed_command *command,
			t_ast_helper *ast_helper);

/* 6_remove.c */
char	*remove_quotes(char *input);
void	remove_quotation(t_parsed_command **command);

/* 7_validate_permission_direc.c */
void	handle_path_error(int error_code);
void	check_executable(const char *path);
void	check_directory(const char *path);
void	check_path(const char *path);
void	validate_permissions_and_directory(const char *path);

#endif
