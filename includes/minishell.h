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

struct s_env;
typedef struct s_env	t_env;

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

extern volatile sig_atomic_t	g_cancel_heredoc;


#endif