/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_memory_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:32:17 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/29 10:31:11 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// frees a single node
void	free_node(t_env *node)
{
	if (node == NULL)
		return ;
	if (node->data != NULL)
		free(node->data);
	if (node->type != NULL)
		free(node->type);
	free(node);
}

void	free_env_exp_all(t_env_exp *env_exp)
{
	int		i;

	if (env_exp != NULL)
	{
		if (env_exp->paths)
		{
			i = -1;
			while (env_exp->paths[++i])
				free(env_exp->paths[i]);
			free (env_exp->paths);
		}
		if (env_exp->execute_env)
		{
			i = -1;
			while (env_exp->execute_env[++i])
				free(env_exp->execute_env[i]);
			free (env_exp->execute_env);
		}
		free_env_exp(env_exp->env);
		free_env_exp(env_exp->exp);
		free (env_exp);
	}
}

void	free_ast_helper(t_ast_helper *ast_helper)
{
	int		i;

	if (ast_helper != NULL)
	{
		if (ast_helper->pids != NULL)
			free(ast_helper->pids);
		if (ast_helper->pipe_fds != NULL)
		{
			i = -1;
			while (++i < ast_helper->pipes_num)
				free(ast_helper->pipe_fds[i]);
			free(ast_helper->pipe_fds);
		}
		free(ast_helper);
	}
}

// frees one linked list
void	free_env_exp(t_env *head)
{
	t_env	*hold;

	while (head != NULL)
	{
		hold = head;
		head = hold->next;
		free_node(hold);
	}
}

// deletes a node at a specific location
void	delete_node(t_env **head, int steps)
{
	t_env	*current;
	t_env	*hold;

	if (steps == 0)
	{
		hold = *head;
		*head = (*head)->next;
		free_node(hold);
		return ;
	}
	current = *head;
	while (steps > 1)
	{
		current = current->next;
		steps--;
	}
	hold = current->next;
	current->next = hold->next;
	free_node(hold);
}
