/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_0_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:48:48 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/29 10:49:55 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void determine_error_code(const char *path)
{
    int fd = open(path, O_RDONLY | O_DIRECTORY);

    if (fd != -1)
    {
        // Write "is a directory" to stderr
        write(STDERR_FILENO, "is a directory\n", 15);
        close(fd);
        exit(126);
    }
    else
    {
        // Write the error message to stderr
        if (errno == EACCES)
        {
            write(STDERR_FILENO, "permission denied\n", 19);
            exit(126);
        }
    }
}



static void	execute_child_process(t_parsed_command *command,
	t_ast_helper *ast_helper, t_env_exp *env_exp, t_free *free_all)
{
	char	*path;
	int		return_value;

	execute_command_input(command, ast_helper);
	execute_command_output(command, ast_helper);
	if (!command->command || !command->arguments)
	{
		ft_printf("Invalid command: %s\n", strerror(errno));
		exit(1);
	}
	return_value = check_build_in(command->arguments, env_exp);
	if (return_value > -1)
		exit(execute_build_in(command->arguments, env_exp, return_value));
	path = find_path(env_exp->paths, command->arguments[0]);
	if (path == NULL)
		exit(127);
	determine_error_code(path);
	if (access(path, X_OK) != 0)
	{
		write(STDERR_FILENO, "command not found\n", 18);
		exit(127);
	}
	set_default_signals();
	execve(path, command->arguments, env_exp->execute_env);
	cleanup(free_all);
	exit(1);
}

static int	handle_parent_process(t_parsed_command *command,
	t_ast_helper *ast_helper, t_env_exp *env_exp, int return_value)
{
	int	parent_value;

	parent_value = execute_command_parent(command, ast_helper);
	
	if (return_value == 1 && command->pipe_out != 1)
	{
		if (ft_cd(env_exp, command->arguments[1], 0) == 1)
			return (127);
		return (0);
	}
	if (return_value == 3 && command->pipe_out != 1)
	{
		if (ft_export(env_exp, command->arguments, 2) == 1)
			return (127);
		return (0);
	}
	if (return_value == 4 && command->pipe_out != 1)
	{
		if (ft_unset(env_exp, command->arguments[1]) != 0)
			return (127);
		return (0);
	}
	return (parent_value);
}

void dollar(t_parsed_command **command, t_env_exp *env_exp)
{
	int i = -1;
	char *result;

	while ((*command)->arguments[++i])
	{
		if (ft_strncmp((*command)->arguments[i], "$?", 3) == 0)
		{
			result = ft_itoa(env_exp->dollar_question);
			free((*command)->arguments[i]);
			(*command)->arguments[i] = result;
		}
		else
		{
			result = variable_manager((*command)->arguments[i], env_exp->env);
			free((*command)->arguments[i]);
			(*command)->arguments[i] = result;
		}
	}
}

int	execute_command(t_parsed_command *command, t_ast_helper *ast_helper,
					t_env_exp *env_exp, t_free *free_all)
{
	int	return_value;
	
	dollar(&command, env_exp);
	return_value = check_build_in(command->arguments, env_exp);
	ast_helper->pids[ast_helper->counter] = fork();
	if (ast_helper->pids[ast_helper->counter] == -1)
	{
		perror("fork");
		cleanup_ast_helper(ast_helper);
		return (-2);
	}
	if (ast_helper->pids[ast_helper->counter] == 0)
		execute_child_process(command, ast_helper, env_exp, free_all);
	env_exp->dollar_question = handle_parent_process(command, ast_helper, env_exp, return_value);
	return (env_exp->dollar_question);
}
