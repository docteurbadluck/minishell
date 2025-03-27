/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:41:20 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/27 12:09:46 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
# define RIGHT 2
# define LEFT 1
#include "../libft/libft.h"

# include <dirent.h>
# include <stdlib.h>

typedef struct s_parsed_command {
	char	*text;
	int		group_id;
	int		associativity;
    char	*command;          // The command to be executed (e.g., "ls", "echo").
    char	**arguments;       // Array of arguments for the command (e.g., {"ls" "-l", "/home"}).
    char	*input_file;       // File for input redirection (e.g., "input.txt").
    char	*output_file;      // File for output redirection (e.g., "output.txt").
    int		append_mode;        // Boolean flag for appending output (1 if ">>", 0 if ">").
    int		pipe_in;            // File descriptor for input pipe (used if part of a pipeline).
    int		pipe_out;           // File descriptor for output pipe (used if part of a pipeline).
    char	*heredoc_delimiter;// Delimiter for heredoc input (used with "<<").
    char	**env_vars;        // Array of environment variables to expand (e.g., {"PATH", "HOME"}).
    int		exit_status;        // Exit status of the most recently executed command.
    int		has_wildcards;      // Boolean flag indicating if wildcards are present in arguments.
    int		logical_operator;   // Logical operator for command chaining (0 for none, 1 for "&&", 2 for "||").
}	t_parsed_command;


typedef struct s_ast_node {
    t_parsed_command *command;    // Pointer to a command struct, if this node represents a command
    int logical_operator;         // Logical operator (0 for none, 1 for "&&", 2 for "||")
    struct s_ast_node *left;      // Left child node (used for binary operators)
    struct s_ast_node *right;     // Right child node (used for binary operators)
} t_ast_node;


//***AA


//	***A
//$? est remplacer par STATUS_LAST_PROCESS
// TO MAKE IT WORK I ADD IN THE ENVIRONEMENT $status_process	
// so it's important to verify at the beggining that it is		/TODO
// present in the environnement. 
char	*variable_manager(char *input);

//	***B

char	*wildcard_manager(char *input);
//	***Ba
int		compte_name(void);
char	**name_array_generator(void);
int		check_current_dir_input(char *input);
int		matching_name(char *pattern, char *name);
char	*assembling_wild(char *variable, char **array_of_str);

//	***C
int	count_word_valid_quote(const char *input);
//  ***Cb
void	count_op(int *i, const char *input, int *counter);
void set_flag(const char *input, int i, int *flag, int *counter);

//	***D
t_parsed_command	*tokenise(char *input);
//  ***Da
void	split_special_char(char *input, int *i, int *y, t_parsed_command *a);
void	split_double_quote(char *input, int *i, int *y, t_parsed_command *array);

//  ***E
int	set_logic_op(t_parsed_command *array);

//  ***F
int	set_groupid_control_logic(t_parsed_command *array);

//  ***Fa
int 	control_border_logic(t_parsed_command *array);
void	give_value(t_parsed_command *array, int i);
void    free_array(t_parsed_command **array);
void    free_new_array(t_parsed_command **new_array);


//  G
t_parsed_command	*group_up(t_parsed_command **array);

//  Ga***
int	count_new_array(t_parsed_command *array);
int	count_arguments_and_move(t_parsed_command *array, int *i);
void	allocate_and_fill_arguments(t_parsed_command *array
	, int save_pos, int count_arg, int *i);

//  H
t_parsed_command	*from_input_to_group(char *input);

//  Ia***
void	set_associativity(t_parsed_command	*new_array);
int	    check_priority(t_parsed_command *new_array, int i, t_list *operator_stack);
void	send_element(t_list **operator_stack, t_list **output_list);
void    print_list(t_list *output_list);
void    free_list(t_list *output_list);


//  I***
t_list *from_group_to_polish_reverse(t_parsed_command *new_array);
//  J***
t_ast_node	*from_polish_to_tree(t_list *output_list);



#endif