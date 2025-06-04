/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_setup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:03:54 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/29 14:05:31 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Count the number of pipes and commands in the AST */
int	pipes_commands_counter(t_ast_node *node, t_ast_helper *ast_helper)
{
	if (!node)
		return (-1);
	if (node->left)
		pipes_commands_counter(node->left, ast_helper);
	if (node->right)
		pipes_commands_counter(node->right, ast_helper);
	if (node->logical_operator == 3)
		ast_helper->pipes_num++;
	if (node->logical_operator == 0)
		ast_helper->commands_num++;
	return (0);
}

/* Free allocated memory in the AST helper */
void	cleanup_ast_helper(t_ast_helper *ast_helper)
{
	int	i;

	if (!ast_helper)
		return ;
	if (ast_helper->pipe_fds)
	{
		i = -1;
		while (++i < ast_helper->pipes_num)
		{
			if (ast_helper->pipe_fds[i])
			{
				close(ast_helper->pipe_fds[i][0]);
				close(ast_helper->pipe_fds[i][1]);
				free(ast_helper->pipe_fds[i]);
			}
		}
		free(ast_helper->pipe_fds);
	}
	if (ast_helper->pids)
		free(ast_helper->pids);
	free(ast_helper);
}

int	handle_pipe_failure(t_ast_helper *ast_helper, int i)
{
	while (--i >= 0)
	{
		close(ast_helper->pipe_fds[i][0]);
		close(ast_helper->pipe_fds[i][1]);
		free(ast_helper->pipe_fds[i]);
	}
	cleanup_ast_helper(ast_helper);
	return (-1);
}

int	ast_handle_pipes_setup(t_ast_helper *ast_helper)
{
	int	i;

	ast_helper->pipe_fds = malloc(sizeof(int *) * ast_helper->pipes_num);
	if (!ast_helper->pipe_fds)
	{
		cleanup_ast_helper(ast_helper);
		return (-1);
	}
	i = 0;
	while (i < ast_helper->pipes_num)
	{
		ast_helper->pipe_fds[i] = (int *)malloc(sizeof(int) * 2);
		if (!ast_helper->pipe_fds[i] || pipe(ast_helper->pipe_fds[i]) == -1)
		{
			perror("pipe");
			return (handle_pipe_failure(ast_helper, i));
		}
		i++;
	}
	return (0);
}

// Prepares ast_helper, which holds information for the pipes
int	prepare_execution_ast(t_ast_node *tree, t_env_exp *env_exp,
	t_ast_helper *ast_helper, t_free *free_all)
{
	int	return_value;

	pipes_commands_counter(tree, ast_helper);
	if (ast_helper->pipes_num > 0)
	{
		if (ast_handle_pipes_setup(ast_helper) == -1)
			return (-1);
	}
	else
		ast_helper->pipe_fds = NULL;
	ast_helper->pids = malloc(sizeof(pid_t) * ast_helper->commands_num);
	if (!ast_helper->pids)
	{
		cleanup_ast_helper(ast_helper);
		return (-1);
	}
	env_exp->paths = get_paths(env_exp);
	return_value = execute_ast(tree, ast_helper, env_exp, free_all);
	return (return_value);
}
