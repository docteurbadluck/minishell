/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:41:20 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/24 16:23:47 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include "../libft/libft.h"

# include <dirent.h>
# include <stdlib.h>

typedef struct s_parsed_command {
	char	*text;
	int		group_id;
	int		associativity;
    char	*command;          // The command to be executed (e.g., "ls", "echo").
    char	**arguments;       // Array of arguments for the command (e.g., {"-l", "/home"}).
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
//	***D
	t_parsed_command	*tokenise(char *input);
//  ***Da
void	split_special_char(char *input, int *i, int *y, t_parsed_command *a);

	
#endif