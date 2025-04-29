/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:53:23 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/26 12:15:36 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*find_next_command_left(t_ast_node *node, t_ast_helper *ast_helper)
{
	t_ast_node	*current;

	if (!node || !node->left)
	{
		ft_printf("Error: %s\n", strerror(EINVAL));
		return (NULL);
	}
	current = node;
	while (current->left && current->left->logical_operator != 0)
		current = current->left;
	if (!current->left || !current->left->command
		|| !current->left->command->command)
	{
		printf("Error: %s\n", strerror(EINVAL));
		return (NULL);
	}
	return (current->left);
}

t_ast_node	*find_next_command_right(t_ast_node *node, t_ast_helper *ast_helper)
{
	t_ast_node	*current;

	if (!node || !node->right)
	{
		ft_printf("Error: %s\n", strerror(EINVAL));
		return (NULL);
	}
	current = node;
	if (current->right->logical_operator == 0)
		return (current->right);
	return (find_next_command_left(current->right, ast_helper));
}

int	execute_ast_pipe(t_ast_node *node, t_ast_helper *ast_helper,
	t_env_exp *env_exp, t_free *free_all)
{
	t_ast_node	*left_command;
	t_ast_node	*right_command;

	left_command = find_next_command_left(node, ast_helper);
	right_command = find_next_command_right(node, ast_helper);
	if (!left_command || !right_command)
	{
		printf("Error: %s\n", strerror(EINVAL));
		return (-1);
	}
	left_command->command->pipe_out = 1;
	right_command->command->pipe_in = 1;
	if (execute_ast(node->left, ast_helper, env_exp, free_all) == -1)
		return (-1);
	ast_helper->counter++;
	ast_helper->pipe_counter++;
	return (execute_ast(node->right, ast_helper, env_exp, free_all));
}

int	handle_and_or(t_ast_node *node, t_ast_helper *ast_helper,
	t_env_exp *env_exp, t_free *free_all)
{
	int	exit_code;

	if (node->logical_operator == 2)
	{
		exit_code = execute_ast(node->left, ast_helper, env_exp, free_all);
		if (exit_code == 0)
		{
			ast_helper->counter++;
			return (execute_ast(node->right, ast_helper, env_exp, free_all));
		}
		return (exit_code);
	}
	if (node->logical_operator == 1)
	{
		exit_code = execute_ast(node->left, ast_helper, env_exp, free_all);
		/////// modif theo The goals is to handle : sleep 10 || ls (if i send a signal during the sleep, it should quit direclty)
		///////	i don't know if it's enough cause maybe some function have -1 as a fail code. modify this value by -255? 
		if (exit_code == -1)
			return(exit_code);
		//////
		if (exit_code != 0)
		{
			ast_helper->counter++;
			return (execute_ast(node->right, ast_helper, env_exp, free_all));
		}
		return (exit_code);
	}
	return (-1);
}

int	execute_ast(t_ast_node *node, t_ast_helper *ast_helper,
	t_env_exp *env_exp, t_free *free_all)
{
	if (!node)
		return (-1);
	if (node->logical_operator == 0)
		return (execute_command(node->command, ast_helper, env_exp, free_all));
	if (node->logical_operator == 1 || node->logical_operator == 2)
		return (handle_and_or(node, ast_helper, env_exp, free_all));
	if (node->logical_operator == 3)
	{
		if (execute_ast_pipe(node, ast_helper, env_exp, free_all) == -1)
			return (-1);
		return (0);
	}
	return (-1);
}
