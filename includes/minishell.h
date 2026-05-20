/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:41:20 by tdeliot           #+#    #+#             */
/*   Updated: 2025/06/04 08:04:00 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RIGHT 2
# define LEFT 1
# define _XOPEN_SOURCE 700
# define _POSIX_C_SOURCE 200809L

# include "../libft-/libft.h"
# include <dirent.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_infile
{
	char	*filename;
	int		mode;
	int		quote_heredoc;
}	t_iofile;

typedef struct s_parsed_command {
	char		*text;
	int			group_id;
	int			associativity;
	char		*command;
	char		**arguments;
	char		**redirection_array;
	t_iofile	*input_file;
	t_iofile	*output_file;
	int			append_mode;
	int			pipe_in;
	int			pipe_out;
	char		*heredoc_delimiter;
	char		**env_vars;
	int			exit_status;
	int			has_wildcards;
	char		**list_of_files;
	int			logical_operator;
	int			what_first;
}	t_parsed_command;

typedef struct s_ast_node {
	t_parsed_command	*command;
	int					logical_operator;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_tracker
{
	char	**groupped_array_list_of_files;
	char	***groupped_array_argument;
	char	**temporaire_array;
	char	**input;
	char	*cp_input;
	char	**list_of_matched_name;
	int		redirection;
	int		y;
	int		i;
}	t_tracker;

typedef struct s_redir_state
{
	t_iofile	*infiles;
	t_iofile	*outfiles;
	int			x;
	int			z;
}	t_redir_state;

typedef struct s_env
{
	char			*type;
	char			*data;
	struct s_env	*next;
}	t_env;

typedef struct s_env_exp
{
	t_env	*env;
	t_env	*exp;
	char	**paths;
	char	**execute_env;
	int		dollar_question;
}	t_env_exp;

typedef struct s_ast_helper
{
	int		pipes_num;
	int		commands_num;
	pid_t	*pids;
	int		**pipe_fds;
	int		active_pipes;
	int		counter;
	int		pipe_counter;
}	t_ast_helper;

typedef struct s_free
{
	t_parsed_command	*new_array;
	t_ast_node			*tree;
	t_env_exp			*env_exp;
	t_ast_helper		*ast_helper;
}	t_free;

typedef struct s_heredoc_manip
{
	int			i;
	int			y;
	char		**eoftext;
	char		**tempfiles_names;
	t_iofile	**to_modif;
	int			z;
	int			*fd;
}	t_heredoc_manip;

extern volatile sig_atomic_t	g_cancel_heredoc;

//	***X
void				free_array(t_parsed_command **array);
void				free_new_array(t_parsed_command **new_array);

//	***Xa
void				free_iofiles(t_parsed_command *command);

void				print_ast_balanced(t_ast_node *root);

// built in
int					ft_echo(char **str);
int					ft_cd(t_env_exp *env_exp, char **str, int version);
int					ft_pwd(void);
void				ft_exit(char **args, int version);

char				*allocate_memory(char *env_var, int start, int end);
t_env				*initialize_node(char *env_var, int j, int k);
t_env				*create_node(char *env_var, int version);
t_env				*safe_env(char **envp, int version);
int					find_envtype(t_env *head, char *name);
int					ft_getenv(t_env *head, char *name, char **result);
void				ft_env(t_env *head, int version);
t_env				*ft_envnew(void);
void				free_env_exp_all(t_env_exp *env_exp);
void				free_ast_helper(t_ast_helper *ast_helper);
void				free_env_exp(t_env *head);
void				free_node(t_env *node);
int					ft_unset(t_env_exp *env_exp, char *content);
void				ft_envadd_back(t_env **lst, t_env *new);
void				ft_insertnode(t_env **exp,
						int steps, char *type, char *data);
int					create_exp(t_env_exp *env_exp);
int					ft_export(t_env_exp *env_exp,
						char **arguments, int version);
void				insert_at_head(t_env **exp, t_env *new_node);
void				insert_at_position(t_env **exp, int steps, t_env *new_node);
t_env				*ft_envlast(t_env *lst);
int					find_exp_spot(t_env *exp, char *name);
t_env				*ft_envlast_minus_one(t_env *lst);
void				ft_envadd_back_minus_one(t_env **lst, t_env *new);
void				delete_node(t_env **head, int steps);
char				**get_paths(t_env_exp *env_exp);
char				*find_path(char **paths, char *command);
char				**create_env_from_linked_list(t_env *env);
void				handle_existing_node(t_env_exp *env_exp, t_env *new_node);
void				handle_new_node(t_env_exp *env_exp, t_env *new_node);

// preparation
int					prepare_env_exp(t_env_exp **env_exp, char **envp);
int					create_ast_helper(t_ast_helper **ast_helper);
void				cleanup(t_free *free_all);

// setup
int					pipes_commands_counter(t_ast_node *node,
						t_ast_helper *ast_helper);
void				cleanup_ast_helper(t_ast_helper *ast_helper);
int					handle_pipe_failure(t_ast_helper *ast_helper, int i);
int					ast_handle_pipes_setup(t_ast_helper *ast_helper);
int					prepare_execution_ast(t_ast_node *tree, t_env_exp *env_exp,
						t_ast_helper *ast_helper, t_free *free_all);

// ast
t_ast_node			*find_next_command_left(t_ast_node *node);
t_ast_node			*find_next_command_right(t_ast_node *node);
int					execute_ast_pipe(t_ast_node *node, t_ast_helper *ast_helper,
						t_env_exp *env_exp, t_free *free_all);
int					handle_and_or(t_ast_node *node, t_ast_helper *ast_helper,
						t_env_exp *env_exp, t_free *free_all);
int					execute_ast(t_ast_node *node, t_ast_helper *ast_helper,
						t_env_exp *env_exp, t_free *free_all);

// builtins
int					check_build_in(char **command);
int					build_in_addition(char **command,
						t_env_exp *env_exp, int return_value);
int					execute_build_in(char **command,
						t_env_exp *env_exp, int return_value);

// input
int					count_files(t_iofile *file);
void				handle_before_input_files(int num_files, t_iofile *file);
int					execute_command_input(t_parsed_command *command,
						t_ast_helper *ast_helper);

// output
void				handle_before_output_files(int num_files, t_iofile *file);
void				handle_output_file(t_parsed_command *command);
int					execute_command_output(t_parsed_command *command,
						t_ast_helper *ast_helper);

// parent
int					handle_parent_process(t_parsed_command *command,
						t_ast_helper *ast_helper,
						t_env_exp *env_exp, int return_value);
int					execute_command_parent(t_parsed_command *command,
						t_ast_helper *ast_helper);

// execution
int					execute_command(t_parsed_command *command,
						t_ast_helper *ast_helper,
						t_env_exp *env_exp, t_free *free_all);

char				*remove_quotes(char *input);
void				remove_quotation(t_parsed_command **command);

// 3_6_validate_permission_direc
void				handle_path_error(int error_code);
void				check_executable(const char *path);
void				check_directory(const char *path);
void				check_path(const char *path);
void				validate_permissions_and_directory(const char *path);

#endif