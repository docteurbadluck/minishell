/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:44:45 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/13 17:56:40 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node_helper(char *env_var, int *j, int *k, int version);

// helper function
void	insert_at_head(t_env **exp, t_env *new_node)
{
	new_node->next = *exp;
	*exp = new_node;
}

// helper function
void	insert_at_position(t_env **exp, int steps, t_env *new_node)
{
	t_env	*current_exp;
	t_env	*safe;

	current_exp = *exp;
	while (steps > 1 && current_exp->next->type != NULL)
	{
		current_exp = current_exp->next;
		steps--;
	}
	safe = current_exp->next;
	current_exp->next = new_node;
	new_node->next = safe;
}

t_env	*create_node(char *env_var, int version)
{
	int		j;
	int		k;
	t_env	*node;

	if (!env_var)
	{
		ft_printf("ERROR: env_var is NULL\n");
		return (NULL);
	}
	node = create_node_helper(env_var, &j, &k, version);
	if (node)
		return (node);
	return (initialize_node(env_var, j, k));
}

// Allocates memory for a substring of env_var from start to end indices
char	*allocate_memory(char *env_var, int start, int end)
{
	char	*result;

	result = (char *)malloc(end - start + 1);
	if (!result)
	{
		ft_printf("ERROR: while allocating memory\n");
		return (NULL);
	}
	ft_memcpy(result, env_var + start, end - start);
	result[end - start] = '\0';
	return (result);
}

// there is the stuct env_exp, env stands for environment and exp for export
// this struct holds two linked lists, one called env and one called exp
// this is necessary because the command export prints the env sorted and
// env prints env based on what got added the latest
// creates one new env node
t_env	*ft_envnew(void)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->type = NULL;
	new_node->data = NULL;
	new_node->next = NULL;
	return (new_node);
}
