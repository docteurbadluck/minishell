/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_4_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:06:45 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/25 13:25:51 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_for_pipes_and_process(t_ast_helper *ast_helper, int *status)
{
	pid_t	pid;

	while (ast_helper->active_pipes > 0)
	{
		pid = waitpid(-1, status, 0);
		if (pid > 0)
			ast_helper->active_pipes--;
	}
	if (waitpid(ast_helper->pids[ast_helper->counter], status, 0) == -1)
	{
		perror("waitpid");
		return (-3);
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
		if (wait_for_pipes_and_process(ast_helper, &status) == -3)
			return (0);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
