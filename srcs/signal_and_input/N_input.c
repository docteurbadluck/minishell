/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/06/02 16:31:01 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_input(t_free *free_all)
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

int	handle_heredocs(int heredoc_counter, t_free *free_all
		, char *argv0)
{
	set_heredoc_signals();
	if (create_heredoc_files(heredoc_counter
			, free_all->new_array, argv0) == -1)
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

int	process_input(char *argv0, t_free *free_all)
{
	int	heredoc_counter;

	if (!free_all->new_array)
		return (0);
	heredoc_counter = count_heredoc(free_all->new_array);
	if (heredoc_counter != 0)
	{
		if (handle_heredocs(heredoc_counter, free_all, argv0))
		{
			cleanup(free_all);
			return (0);
		}
	}
	execute_input(free_all);
	return (0);
}

int	handle_single_input(char *way_to_tmp, t_free *free_all)
{
	char	*input;

	unlink_tempo_files(way_to_tmp);
	input = get_input();
	if (!input)
	{
		ft_printf("exit\n");
		return (-1);
	}
	if (ft_strchr(input, '\n'))
	{
		ft_printf("error multiple line\n");
		free(input);
		return (0);
	}
	if (ft_strlen(input))
	{
		add_history(input);
		free_all->new_array = from_input_to_group(input);
		process_input(way_to_tmp, free_all);
	}
	free(input);
	return (0);
}

int	read_input(char *argv0, char **envp)
{
	t_free		free_all;
	t_env_exp	*env_exp;
	char		*way_to_tmp;

	set_menu_signals();
	if (prepare_env_exp(&env_exp, envp) != 0)
	{
		ft_printf("error\n");
		return (1);
	}
	way_to_tmp = path_to_tmp(argv0);
	while (1)
	{
		free_all = init_free_all();
		free_all.env_exp = env_exp;
		if (handle_single_input(way_to_tmp, &free_all) == -1)
			break ;
	}
	free_env_exp_all(env_exp); 
	rl_clear_history();
	return (0);
}
