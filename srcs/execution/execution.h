#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "../parsing/3_build_tree/build_tree.h"

typedef struct s_free
{
	t_parsed_command	*new_array;
	t_ast_node			*tree;
	t_env_exp			*env_exp;
	t_ast_helper		*ast_helper;
}	t_free;

/* ===== PUBLIC API ===== */

/* 0_preparation.c */
int			prepare_env_exp(t_env_exp **env_exp, char **envp);
int			create_ast_helper(t_ast_helper **ast_helper);
void		cleanup(t_free *free_all);

/* 1_setup.c */
int			prepare_execution_ast(t_ast_node *tree, t_env_exp *env_exp,
				t_ast_helper *ast_helper, t_free *free_all);

/* 3_paths.c */
char		**create_env_from_linked_list(t_env *env);

/* ===== INTERNAL HELPERS ===== */

/* 0_preparation.c */
void		free_paths(char **paths);

/* 1_setup.c */
int			pipes_commands_counter(t_ast_node *node, t_ast_helper *ast_helper);
void		cleanup_ast_helper(t_ast_helper *ast_helper);
int			handle_pipe_failure(t_ast_helper *ast_helper, int i);
int			ast_handle_pipes_setup(t_ast_helper *ast_helper);

/* 2_ast.c */
t_ast_node	*find_next_command_left(t_ast_node *node);
t_ast_node	*find_next_command_right(t_ast_node *node);
int			execute_ast_pipe(t_ast_node *node, t_ast_helper *ast_helper,
				t_env_exp *env_exp, t_free *free_all);
int			handle_and_or(t_ast_node *node, t_ast_helper *ast_helper,
				t_env_exp *env_exp, t_free *free_all);
int			execute_ast(t_ast_node *node, t_ast_helper *ast_helper,
				t_env_exp *env_exp, t_free *free_all);

/* 3_paths.c */
char		**get_paths(t_env_exp *env_exp);
char		*find_path(char **paths, char *command);
char		**get_environ(t_env *env);

#endif
