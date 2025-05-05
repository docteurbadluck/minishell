/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:41:20 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/28 12:33:25 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RIGHT 2
# define LEFT 1
# define _XOPEN_SOURCE 700
# define _POSIX_C_SOURCE 200809L


# include "../libft/libft.h"

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
	char		*text;				// flexible text for helping me to create the tree 
	int			group_id;			// group the argument together 
	int			associativity;		// define the associativity
	char		*command;			// The command to be executed (e.g., "ls", "echo").
	char		**arguments;		// Array of arguments for the command (e.g., {"ls" "-l", "/home"}).
	char		**redirection_array;// array with all redirection in order ( ">" "text.txt" ">" "text2.txt" )
	t_iofile	*input_file;		// array with the names of the input file in order
	t_iofile	*output_file;		// File for output redirection (e.g., "output.txt").
	int			append_mode;		// Boolean flag for appending output (1 if ">>", 0 if ">").
	int			pipe_in;			// File descriptor for input pipe (used if part of a pipeline).
	int			pipe_out;			// File descriptor for output pipe (used if part of a pipeline).
	char		*heredoc_delimiter;	// Delimiter for heredoc input (used with "<<").
	char		**env_vars;			// Array of environment variables to expand (e.g., {"PATH", "HOME"}).
	int			exit_status;		// Exit status of the most recently executed command.
	int			has_wildcards;		// Boolean flag indicating if wildcards are present in arguments.
	char		**list_of_files;	// list of files referenced by the wildcard.
	int			logical_operator;	// Logical operator for command chaining (0 for none, 1 for "&&", 2 for "||", 3 for "|").
}	t_parsed_command;

typedef struct s_ast_node {
	t_parsed_command	*command;		// Pointer to a command struct, if this node represents a command
	int					logical_operator; // Logical operator for command chaining (0 for none, 1 for "&&", 2 for "||", 3 for "|").
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
    char *type;
    char *data;
    struct s_env *next;
}   t_env;

typedef struct s_env_exp
{
    t_env *env;
    t_env *exp;
	char **paths;
	char **execute_env;
	int dollar_question;
}   t_env_exp;

typedef struct s_ast_helper
{
	int pipes_num;
	int commands_num;
	pid_t *pids;
	int **pipe_fds;
	int active_pipes;
	int counter;
	int pipe_counter;
}	t_ast_helper;

typedef struct s_free
{
	t_parsed_command	*new_array;
	t_ast_node			*tree;
	t_env_exp 			*env_exp;
	t_ast_helper        *ast_helper;
}	t_free;

typedef struct s_heredoc_manip
{
	int			i;
	int			y;
	char		**EOFtext;
	char		**tempfiles_names;
	t_iofile	**to_modif;
	int			z;
	int			*fd;
}	t_heredoc_manip;


//	***A
char				*variable_manager(char *input, t_env *head);
 
//	***B
char				*wildcard_manager(char *input);

//	***Ba
int					compte_name(void);
char				**name_array_generator(void);
int					check_current_dir_input(char *input);
int					matching_name(char *pattern, char *name, int first_call);
char				*assembling_wild(char *variable, char **array_of_str);

//	***Bc
void				find_wildcard_in_arg(t_parsed_command *grouped_array,
						int i, t_list **list_of_tracker);
int					set_wildcard(t_parsed_command *grouped_array);

//	***Bd
void				modify_arg(t_tracker *ptr_tracker);

//	***Be
void				free_wildcard_list(void *content);
void				free_str_list(void *content);
void				copy_before_wildcard(t_tracker *ptr_tracker,
						t_list **list_of_str, int *i);

//	***C
int					count_word_valid_quote(const char *input);

//	***Cb
void				count_op(int *i, const char *input, int *counter);
void				set_flag(const char *input, int i, int *flag, int *counter);

//	***D
t_parsed_command	*tokenise(char *input);

//	***Da
void				split_special_char(char *input, int *i,
						int *y, t_parsed_command *a);
void				split_double_quote(char *input, int *i,
						int *y, t_parsed_command *array);

//	***E
int					set_logic_op(t_parsed_command *array);

//	***F
int					set_groupid_control_logic(t_parsed_command *array);

//	***Fa
int					control_border_logic(t_parsed_command *array);
void				give_value(t_parsed_command *array, int i);

//	***G
t_parsed_command	*group_up(t_parsed_command **array);

//	***Ga
int					allocate_and_fill_arguments(
						t_parsed_command *array, int save_pos,
						int count_arg, int *i);

//	***Gb
int					count_new_array(t_parsed_command *array);
int					count_arguments_and_move(t_parsed_command *array, int *i);

//	***H
t_parsed_command	*from_input_to_group(char *input);

//	***Ha
int					set_outfiles(t_parsed_command *grouped_array);

//	***Hb
int					control_operator(char *redirection);
int					control_redirection_logique(
						t_parsed_command *grouped_array);
int					count_files_names(char **redirection_array);
int					which_symbole(char *redirection);

//	***Hc
char				*process_redirection_filename(const char *input);

//	***I
t_list				*from_group_to_polish_reverse(t_parsed_command *new_array);

//	***Ia
void				set_associativity(t_parsed_command *new_array);
int					check_priority(t_parsed_command *new_array, int i,
						t_list *operator_stack);
void				send_element(t_list **operator_stack, t_list **output_list);
void				print_list(t_list *output_list);
void				free_list(t_list *output_list);

//	***L
t_ast_node			*from_polish_to_tree(t_list *output_list);
t_ast_node	*from_group_to_tree(t_parsed_command **new_array);

//	***K
t_ast_node			*from_text_to_tree(char *str, t_parsed_command **new_array);
void				free_tree(t_ast_node *node);

//	***L
void				print_tree(t_ast_node *node, int depth);

//	***M
void				set_default_signals(void);
void				set_ignore_signals(void);
void				set_menu_signals(void);
void				set_heredoc_signals(void);
//	***Ma

extern volatile sig_atomic_t	g_cancel_heredoc;  // Flag to indicate if the heredoc should be canceled
void				handler_menu(int signum);
void				soft_quit_handler(int signum);

//	***N
int	read_input(char *argv0, char **envp);

// ***Na
int					count_heredoc(t_parsed_command *ptr);

//	***Nb
t_free				init_free_all(void);
char				*get_input(void);

//	***O
int					create_heredoc_files(int nbr_of_heredoc, t_parsed_command *array_of_cmd, char *argv0, t_env *head);
//	***Oa
int					init_eof_and_to_modif(int nbr_heredoc,
						t_parsed_command *array_of_cmd, t_heredoc_manip *heredoc);
void				names_tempo_files(t_heredoc_manip *heredoc, char *argv0);
void				write_into_temp(t_heredoc_manip *heredoc, int y);

//	***P 
char	*name_and_path_generator(char* argv0, char* directory, char* file_name);
void	unlink_tempo_files(char *argv0);

//	***X
void				free_array(t_parsed_command **array);
void				free_new_array(t_parsed_command **new_array);

//	***Xa
void				free_iofiles(t_parsed_command *command);

void				print_ast_balanced(t_ast_node *root);

// built in
int ft_echo(char **str);
int ft_cd(t_env_exp *env_exp, char *str, int version);
int ft_pwd();
void ft_exit(char **args);

char	*allocate_memory(char *env_var, int start, int end);
t_env	*initialize_node(char *env_var, int j, int k);
t_env	*create_node(char *env_var);
t_env	*safe_env(char **envp);
int find_envtype(t_env *head, char *name);
int ft_getenv(t_env *head, char *name, char **result);
void ft_env(t_env *head, int version);
t_env	*ft_envnew(void);
void	free_env_exp_all(t_env_exp *env_exp);
void	free_ast_helper(t_ast_helper *ast_helper);
void free_env_exp(t_env *head);
void free_node(t_env *node);
int ft_unset(t_env_exp *env_exp, char *content);
void	ft_envadd_back(t_env **lst, t_env *new);

void ft_insertnode(t_env **exp, int steps, char *type, char *data);
int create_exp(t_env_exp *env_exp);
int ft_export(t_env_exp *env_exp, char *content, int version);
void	insert_at_head(t_env **exp, t_env *new_node);
void	insert_at_position(t_env **exp, int steps, t_env *new_node);
t_env	*ft_envlast(t_env *lst);
int	find_exp_spot(t_env *exp, char *name);
t_env	*ft_envlast_minus_one(t_env *lst);
void	ft_envadd_back_minus_one(t_env **lst, t_env *new);
void	delete_node(t_env **head, int steps);




char	**get_paths(t_env_exp *env_exp);
char	*find_path(char **paths, char *command);
char	**create_env_from_linked_list(t_env *env);



// preparation
int prepare_env_exp(t_env_exp **env_exp, char **envp);
int	create_ast_helper(t_ast_helper **ast_helper);
void	cleanup(t_free *free_all);

// setup
int	pipes_commands_counter(t_ast_node *node, t_ast_helper *ast_helper);
void	cleanup_ast_helper(t_ast_helper *ast_helper);
int	handle_pipe_failure(t_ast_helper *ast_helper, int i);
int	ast_handle_pipes_setup(t_ast_helper *ast_helper);
int	prepare_execution_ast(t_ast_node *tree, t_env_exp *env_exp,
	t_ast_helper *ast_helper, t_free *free_all);

// ast
t_ast_node	*find_next_command_left(t_ast_node *node, t_ast_helper *ast_helper);
t_ast_node	*find_next_command_right(t_ast_node *node, t_ast_helper *ast_helper);
int	execute_ast_pipe(t_ast_node *node, t_ast_helper *ast_helper,
	t_env_exp *env_exp, t_free *free_all);
int	handle_and_or(t_ast_node *node, t_ast_helper *ast_helper,
	t_env_exp *env_exp, t_free *free_all);
int	execute_ast(t_ast_node *node, t_ast_helper *ast_helper,
	t_env_exp *env_exp, t_free *free_all);

// builtins
int	check_build_in(char **command, t_env_exp *env_exp);
int	build_in_addition(char **command, t_env_exp *env_exp, int return_value);
int	execute_build_in(char **command, t_env_exp *env_exp, int return_value);

// input
int	count_files(t_iofile *file);
void	handle_before_input_files(int num_files, t_iofile *file);
int	execute_command_input(t_parsed_command *command, t_ast_helper *ast_helper);
	
// output
void	handle_before_output_files(int num_files, t_iofile *file);
void	handle_output_file(t_parsed_command *command);
int	execute_command_output(t_parsed_command *command, t_ast_helper *ast_helper);

// parent
static int	wait_for_pipes_and_process(t_ast_helper *ast_helper, int *status);
int	execute_command_parent(t_parsed_command *command, t_ast_helper *ast_helper);

// execution
static void	execute_child_process(t_parsed_command *command, t_ast_helper *ast_helper,
	t_env_exp *env_exp, t_free *free_all);
static int	handle_parent_process(t_parsed_command *command, t_ast_helper *ast_helper,
	t_env_exp *env_exp, int return_value);
int	execute_command(t_parsed_command *command, t_ast_helper *ast_helper,
					t_env_exp *env_exp, t_free *free_all);






#endif