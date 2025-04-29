/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:31:22 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/28 12:51:37 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if type is already in the file and returns specific number;
// if it doesn't exist it returns -1
int	find_envtype(t_env *head, char *name)
{
	int		len;
	int		i;
	t_env	*current;

	current = head;
	i = 0;
	while (current != NULL)
	{
		len = ft_strlen(current->type);
		if (ft_strncmp(name, current->type, len + 1) == 0)
			return (i);
		current = current->next;
		i++;
	}
	return (-1);
}

// slightly modified so that there is a difference
// between it exists but has no data and it doent exist at all
int	ft_getenv(t_env *head, char *name, char **result)
{
	int		position;
	t_env	*current;

	current = head;
	position = find_envtype(head, name);
	if (position == -1)
	{
		if (result == NULL)
			return (1);
		*result = NULL;
		return (1);
	}
	while (position > 0)
	{
		current = current->next;
		position--;
	}
	if (current->data == NULL)
		return (2);
	if (result != NULL)
		*result = current->data;
	return (0);
}

// ft_env prints the linked list like the command env would do
void	ft_env(t_env *head, int version)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (version == 2)
			ft_printf("%s=%s\n", current->type, current->data);
		current = current->next;
	}
}

// export needs to be sorted, step by step all nodes get
// copied to the linked list exp
// before inserting it checks, where to put the new node
// this function finds the spot
int	find_exp_spot(t_env *exp, char *name)
{
	t_env	*current;
	int		steps;
	int		compare;

	current = exp;
	steps = 0;
	while (current != NULL)
	{
		compare = ft_strncmp(name, current->type, ft_strlen(name) + 1);
		if (compare == 0)
			return (-1);
		if (compare < 0)
			break ;
		steps++;
		current = current->next;
	}
	return (steps);
}

// this function creates a copy node of a env node and puts it at the right spot
void	ft_insertnode(t_env **exp, int steps, char *type, char *data)
{
	t_env	*new_node;

	if (exp == NULL)
	{
		ft_printf("%s, Error: The list pointer is null.\n", strerror(errno));
		return ;
	}
	new_node = ft_envnew();
	if (new_node == NULL)
	{
		ft_printf("%s, Memory allocation for new node failed\n",
			strerror(errno));
		return ;
	}
	new_node->type = ft_strdup(type);
	new_node->data = ft_strdup(data);
	if (*exp == NULL || steps == 0)
		insert_at_head(exp, new_node);
	else
		insert_at_position(exp, steps, new_node);
}
