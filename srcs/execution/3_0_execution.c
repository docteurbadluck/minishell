/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_0_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:52:05 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/15 14:20:29 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_command_execution(t_parsed_command *command,
		t_ast_helper *ast_helper)
{
	if (command->what_first == 2 || command->what_first == 0)
	{
		execute_command_input(command, ast_helper);
		execute_command_output(command, ast_helper);
	}
	else
	{
		execute_command_output(command, ast_helper);
		execute_command_input(command, ast_helper);
	}
}

static void	validate_and_execute(t_parsed_command *command,
		t_env_exp *env_exp)
{
	int	return_value;

	if (!command->command || !command->arguments)
	{
		ft_printf("Invalid command: %s\n", strerror(errno));
		exit(1);
	}
	return_value = check_build_in(command->arguments);
	if (return_value == 0)
		exit(0);
	if (return_value > 0)
		exit(execute_build_in(command->arguments, env_exp, return_value));
}

static void	execute_child_process(t_parsed_command *command,
		t_ast_helper *ast_helper, t_env_exp *env_exp, t_free *free_all)
{
	char	*path;

	handle_command_execution(command, ast_helper);
	validate_and_execute(command, env_exp);
	path = find_path(env_exp->paths, command->arguments[0]);
	check_path(path);
	set_default_signals();
	execve(path, command->arguments, env_exp->execute_env);
	cleanup(free_all);
	exit(1);
}

void	dollar(t_parsed_command **command, t_env_exp *env_exp)
{
	int		i;
	int		j;
	char	*result;

	i = -1;
	j = 0;
	while ((*command)->arguments[++i])
	{
		result = variable_manager((*command)->arguments[i], env_exp);
		free((*command)->arguments[i]);
		(*command)->arguments[i] = result;
		if ((*command)->arguments[i] && 
			!ft_strncmp((*command)->arguments[i], "", 2))
		{
			free((*command)->arguments[i]);
			(*command)->arguments[i] = NULL;
		}
		if ((*command)->arguments[i])
			(*command)->arguments[j++] = (*command)->arguments[i];
	}
	(*command)->arguments[j] = NULL;
}

int	execute_command(t_parsed_command *command, t_ast_helper *ast_helper,
		t_env_exp *env_exp, t_free *free_all)
{
	int	return_value;

	dollar(&command, env_exp);
	remove_quotation(&command);
	return_value = check_build_in(command->arguments);
	ast_helper->pids[ast_helper->counter] = fork();
	if (ast_helper->pids[ast_helper->counter] == -1)
	{
		perror("fork");
		cleanup_ast_helper(ast_helper);
		return (-2);
	}
	if (ast_helper->pids[ast_helper->counter] == 0)
		execute_child_process(command, ast_helper, env_exp, free_all);
	env_exp->dollar_question = handle_parent_process(command, ast_helper,
			env_exp, return_value);
	return (env_exp->dollar_question);
}
