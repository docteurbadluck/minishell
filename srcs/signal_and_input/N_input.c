/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/06 14:02:47 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// we assume that everything succeed X) 
void	execute_input(t_free *free_all, char **envp)
{
	free_all->tree = from_group_to_tree(&free_all->new_array);
	set_ignore_signals();
	if (create_ast_helper(&free_all->ast_helper) == 0)
	{
		prepare_execution_ast(free_all->tree,
			free_all->env_exp, free_all->ast_helper, free_all);
	}
	set_menu_signals();
	cleanup(free_all);
}

int	handle_heredocs(int heredoc_counter, t_free *free_all, char *argv0, t_env_exp *env_exp)
{
	set_heredoc_signals();
	if (create_heredoc_files(heredoc_counter, free_all->new_array, argv0, env_exp) == -1)
	{
		set_menu_signals();
		return (-1);
	}
	set_menu_signals();
	if (g_cancel_heredoc)
	{
		g_cancel_heredoc = 0;
		return (-1);
	}
	return (0);
}

int	process_input(char *argv0, char **envp, t_free *free_all, char *input, t_env_exp *env_exp)
{
	int	heredoc_counter;

	add_history(input);
	free_all->new_array = from_input_to_group(input);
	if (!free_all->new_array)
		return (0);
	heredoc_counter = count_heredoc(free_all->new_array);
	if (heredoc_counter != 0)
	{
		if (handle_heredocs(heredoc_counter, free_all, argv0, env_exp))
		{
			cleanup(free_all);
			return (0);
		}
	}
	execute_input(free_all, envp);
	return (0);
}

int	handle_single_input(char *argv0, char **envp, t_free *free_all, t_env_exp *env_exp)
{
	char	*input;

	unlink_tempo_files(argv0);
	input = get_input();
	if (!input)
	{
		printf("exit\n");
		return (-1);
	}
	if (ft_strlen(input))
		process_input(argv0, envp, free_all, input, env_exp);
	free(input);
	return (0);
}

int	read_input(char *argv0, char **envp)
{
	t_free		free_all;
	t_env_exp	*env_exp;

	set_menu_signals();
	if (prepare_env_exp(&env_exp, envp) != 0)
	{
		printf("error\n");
		return (1);
	}
	while (1)
	{
		free_all = init_free_all();
		free_all.env_exp = env_exp;
		if (handle_single_input(argv0, envp, &free_all, env_exp) == -1)
			break ;
	}
	free_env_exp_all(env_exp); 
	rl_clear_history();
	return (0);
}

/*
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	read_input(argv[0], envp);
	return (0);
}
*/