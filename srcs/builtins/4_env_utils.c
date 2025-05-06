/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:31:03 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/24 16:33:29 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

// Creates a new t_env node and initializes its type and data
t_env	*initialize_node(char *env_var, int j, int k)
{
	t_env	*node;

	node = ft_envnew();
	if (!node)
	{
		ft_printf("ERROR: while allocating node\n");
		return (NULL);
	}
	node->type = allocate_memory(env_var, 0, j);
	if (!node->type)
	{
		free(node);
		return (NULL);
	}
	if (k == -1)
		node->data = ft_strdup("\0");
	else
		node->data = allocate_memory(env_var, j + 1, k);

	if (!node->data)
	{
		free(node->type);
		free(node);
		return (NULL);
	}

	return (node);
}

// Parses env_var and separates it into type (key) and data (value)
t_env	*create_node(char *env_var)
{
	int	j;
	int	k;
	int	str_len;

	if (!env_var)
	{
		ft_printf("ERROR: env_var is NULL\n");
		return (NULL);
	}
	if (env_var[0] == '=')
		exit(1);

	str_len = ft_strlen(env_var);
	j = 0;
	while (env_var[j] && env_var[j] != '=')
	{
		if (j == 0 && (ft_isdigit(env_var[j]) || env_var[j] == '='))
		{
			write(2, "not a valid identifier\n", 23);
			exit(1);
		}
		if (!(ft_isalnum(env_var[j]) || env_var[j] == '_'))
		{
			write(2, "not a valid identifier\n", 23);
			exit(1);
		}
		j++;
	}
	if (str_len == j)
		return (initialize_node(env_var, str_len, -1));
	k = j;
	while (env_var[k])
		k++;
	return (initialize_node(env_var, j, k));
}


// this function gets the envp over main and saves everything
// in a linked list called env
// LOGNAME=jholterh becomes type: LOGNAME and data: jholterh
// _= needs to be the last one
t_env	*safe_env(char **envp)
{
	t_env	*head;
	t_env	*node;
	t_env	*hold;
	int		i;

	head = NULL;
	hold = NULL;
	i = -1;
	while (envp[++i] != NULL)
	{
		node = create_node(envp[i]);
		if (!node)
			return (NULL);
		if (ft_strncmp(node->type, "_\0", 2) == 0)
			hold = node;
		else
			ft_envadd_back(&head, node);
	}
	if (hold)
		ft_envadd_back(&head, hold);
	return (head);
}
