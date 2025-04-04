/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:41:20 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/03 15:39:46 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
# define RIGHT 2
# define LEFT 1
#include "../libft/libft.h"

# include <dirent.h>
# include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_infile
{
    char    *filename;
    int     mode;   // 0 -> normal  1 -> << heredoc ( should never hapen but i did'nt coded heredoc yet) 
} t_iofile;


typedef struct s_parsed_command {
	char	*text;              // flexible text for helping me to create the tree 
	int		group_id;           // group the argument together 
	int		associativity;      // define the associativity
    char	*command;          // The command to be executed (e.g., "ls", "echo").
    char	**arguments;       // Array of arguments for the command (e.g., {"ls" "-l", "/home"}).
    char    **redirection_array; //array with all redirection in order ( ">" "text.txt" ">" "text2.txt" )
    t_iofile	*input_file;       // array with the names of the input file in order mode determine if it;s in append mode or not.
    t_iofile	*output_file;      // File for output redirection (e.g., "output.txt").
    int		append_mode;        // Boolean flag for appending output (1 if ">>", 0 if ">").
    int		pipe_in;            // File descriptor for input pipe (used if part of a pipeline).
    int		pipe_out;           // File descriptor for output pipe (used if part of a pipeline).
    char	*heredoc_delimiter;// Delimiter for heredoc input (used with "<<").
    char	**env_vars;        // Array of environment variables to expand (e.g., {"PATH", "HOME"}).
    int		exit_status;        // Exit status of the most recently executed command.
    int		has_wildcards;      // Boolean flag indicating if wildcards are present in arguments. > the function are not applied the same.
    char    **list_of_files;    //list of files referenced by the wildcard.
    int		logical_operator;   // Logical operator for command chaining (0 for none, 1 for "&&", 2 for "||").
}	t_parsed_command;


typedef struct s_ast_node {
    t_parsed_command *command;    // Pointer to a command struct, if this node represents a command
    int logical_operator;         // Logical operator (0 for none, 1 for "&&", 2 for "||")
    struct s_ast_node *left;      // Left child node (used for binary operators)
    struct s_ast_node *right;     // Right child node (used for binary operators)
} t_ast_node;

typedef struct s_tracker
{
    char                **groupped_array_list_of_files;
    char                ***groupped_array_argument;
    char                **temporaire_array;
    char                **input;
    char                *cp_input;
    char                **list_of_matched_name;
    int                 redirection;
    int                 y;
    int                 i;
} t_tracker;

//	***A
//$? est remplacer par STATUS_LAST_PROCESS
// TO MAKE IT WORK I ADD IN THE ENVIRONEMENT $status_process	
// so it's important to verify at the beggining that it is		/TODO
// present in the environnement. 
char	*variable_manager(char *input);

//	***B

// problem echo abc > * write abc in every file 
// so we need to use the has wildcards flag.
char	*wildcard_manager(char *input);
//	***Ba
int		compte_name(void);
char	**name_array_generator(void);
int		check_current_dir_input(char *input);
//int		matching_name(char *pattern, char *name);
int	matching_name(char *pattern, char *name, int first_call);

char	*assembling_wild(char *variable, char **array_of_str);

//  ***Bc
void	find_wildcard_in_arg(t_parsed_command *grouped_array, int i, t_list **list_of_tracker);
int	    set_wildcard(t_parsed_command *grouped_array);

//  ***Bd
void modify_arg(t_tracker *ptr_tracker);
//  ***Be
void free_wildcard_list(void *content);
void	free_str_list(void *content);
void	copy_before_wildcard(t_tracker *ptr_tracker,
	t_list **list_of_str, int *i);



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

//  G
t_parsed_command	*group_up(t_parsed_command **array);

//  Ga***
/*
void	allocate_and_fill_arguments(t_parsed_command *array
	, int save_pos, int count_arg, int *i);*/

int	allocate_and_fill_arguments(t_parsed_command *array
        , int save_pos, int count_arg, int *i);

// ***Gb
int	count_new_array(t_parsed_command *array);
int	count_arguments_and_move(t_parsed_command *array, int *i);

//  H
t_parsed_command	*from_input_to_group(char *input);

int set_outfiles(t_parsed_command *grouped_array);

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
//  K***
t_ast_node  *from_text_to_tree(char *str, t_parsed_command **new_array);
void            free_tree(t_ast_node *node);
void            print_tree(t_ast_node *node, int depth);


//  ***X
void    free_array(t_parsed_command **array);
void    free_new_array(t_parsed_command **new_array);

void print_ast_balanced(t_ast_node *root) ;

#endif