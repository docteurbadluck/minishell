/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:31:03 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/13 17:56:35 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*allocate_memory(char *env_var, int start, int end);
t_env	*create_node(char *env_var, int version);
t_env	*ft_envnew(void);

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
static void	validate_identifier(char *env_var, int *j, int version)
{
	if (*j == 0 && (ft_isdigit(env_var[*j]) || env_var[*j] == '='))
	{
		if (version == 2)
		{
			write(2, "not a valid identifier\n", 23);
			exit(1);
		}
	}
	if (!(ft_isalnum(env_var[*j]) || env_var[*j] == '_'))
	{
		if (version == 2)
		{
			write(2, "not a valid identifier\n", 23);
			exit(1);
		}
	}
}

static void	parse_env_var(char *env_var, int *j, int version)
{
	while (env_var[*j] && env_var[*j] != '=')
	{
		validate_identifier(env_var, j, version);
		(*j)++;
	}
}

t_env	*create_node_helper(char *env_var, int *j, int *k, int version)
{
	int	str_len;

	str_len = ft_strlen(env_var);
	*j = 0;
	parse_env_var(env_var, j, version);
	if (str_len == *j)
		return (initialize_node(env_var, str_len, -1));
	*k = *j;
	while (env_var[*k])
		(*k)++;
	return (NULL);
}

// this function gets the envp over main and saves everything
// in a linked list called env
// LOGNAME=jholterh becomes type: LOGNAME and data: jholterh
// _= needs to be the last one
t_env	*safe_env(char **envp, int version)
{
	t_env	*head;
	t_env	*node;
	t_env	*hold;
	int		i;

	head = NULL;
	hold = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		node = create_node(envp[i], version);
		if (!node)
			return (NULL);
		if (ft_strncmp(node->type, "_\0", 2) == 0)
			hold = node;
		else
			ft_envadd_back(&head, node);
		i++;
	}
	if (hold)
		ft_envadd_back(&head, hold);
	return (head);
}
