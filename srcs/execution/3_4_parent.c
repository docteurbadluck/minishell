/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_4_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:06:45 by jholterh          #+#    #+#             */
/*   Updated: 2025/06/02 16:20:04 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_for_all_processes(t_ast_helper *ast_helper, int *status)
{
	int	i;

	i = 0;
	while (i <= ast_helper->counter)
	{
		if (ast_helper->pids[i] > 0) 
		{
			if (waitpid(ast_helper->pids[i], status, 0) == -1)
			{
				perror("waitpid");
				return (-1);
			}
			ast_helper->pids[i] = -1;
		}
		i++;
	}
	return (0);
}

int	execute_command_parent(t_parsed_command *command, t_ast_helper *ast_helper)
{
	int		status;

	status = 0;
	if (command->pipe_in == 1)
	{
		close(ast_helper->pipe_fds[ast_helper->pipe_counter - 1][0]);
		close(ast_helper->pipe_fds[ast_helper->pipe_counter - 1][1]);
	}
	if (command->pipe_out == 1)
		ast_helper->active_pipes++;
	if (command->pipe_out != 1)
	{
		if (wait_for_all_processes(ast_helper, &status) == -3)
			return (0);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

static int	handle_builtins_no_pipe(t_parsed_command *command,
		t_env_exp *env_exp, int return_value)
{
	if (return_value == 2 && command->pipe_out != 1)
	{
		if (ft_cd(env_exp, command->arguments, 0) == 1)
			return (1);
		return (0);
	}
	if (return_value == 4 && command->pipe_out != 1)
	{
		if (ft_export(env_exp, command->arguments, 2) == 1)
			return (1);
		return (0);
	}
	if (return_value == 5 && command->pipe_out != 1)
	{
		if (ft_unset(env_exp, command->arguments[1]) != 0)
			return (1);
		return (0);
	}
	if (return_value == 7 && command->pipe_out != 1)
	{
		ft_exit(command->arguments, 0);
		return (1);
	}
	return (-1);
}

int	handle_parent_process(t_parsed_command *command,
		t_ast_helper *ast_helper, t_env_exp *env_exp, int return_value)
{
	int	parent_value;
	int	builtin_result;

	parent_value = execute_command_parent(command, ast_helper);
	builtin_result = handle_builtins_no_pipe(command, env_exp, return_value);
	if (builtin_result != -1)
		return (builtin_result);
	return (parent_value);
}
