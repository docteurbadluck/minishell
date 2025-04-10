/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:41:20 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/10 09:57:40 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RIGHT 2
# define LEFT 1
# define _XOPEN_SOURCE 700

# include "../libft/libft.h"

# include <dirent.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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
	int			logical_operator;	// Logical operator for command chaining (0 for none, 1 for "&&", 2 for "||").
}	t_parsed_command;

typedef struct s_ast_node {
	t_parsed_command	*command;		// Pointer to a command struct, if this node represents a command
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
char				*variable_manager(char *input);

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

//	***K
t_ast_node			*from_text_to_tree(char *str, t_parsed_command **new_array);
t_ast_node			*from_group_to_tree(t_parsed_command **new_array);

void				free_tree(t_ast_node *node);

//	***L
void				print_tree(t_ast_node *node, int depth);

//	***O
int					create_heredoc_files(int nbr_of_heredoc, t_parsed_command *array_of_cmd);
//	***Oa
int					init_eof_and_to_modif(int nbr_heredoc,
						t_parsed_command *array_of_cmd, t_heredoc_manip *heredoc);
void				names_tempo_files(t_heredoc_manip *heredoc);
void				write_into_temp(t_heredoc_manip *heredoc, int y);



//	***X
void				free_array(t_parsed_command **array);
void				free_new_array(t_parsed_command **new_array);

//	***Xa
void				free_iofiles(t_parsed_command *command);

void				print_ast_balanced(t_ast_node *root);

#endif