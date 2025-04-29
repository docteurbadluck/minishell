/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_preparation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:33:05 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/29 10:05:00 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_env_exp(t_env_exp **env_exp, char **envp)
{
	*env_exp = malloc(sizeof(t_env_exp));
	if (*env_exp == NULL)
	{
		ft_printf("%s, Memory allocation failed\n", strerror(errno));
		return (1);
	}
	(*env_exp)->env = safe_env(envp);
	if ((*env_exp)->env == NULL)
	{
		ft_printf("%s, Failed to initialize environment\n", strerror(errno));
		return (1);
	}
	if (create_exp(*env_exp) != 0)
	{
		ft_printf("Error: Failed to create export\n");
		return (1);
	}
	(*env_exp)->execute_env = create_env_from_linked_list((*env_exp)->env);
	return (0);
}

int	create_ast_helper(t_ast_helper **ast_helper)
{
	*ast_helper = malloc(sizeof(t_ast_helper));
	if (!*ast_helper)
		return (-1);
	ft_memset(*ast_helper, 0, sizeof(t_ast_helper));
	return (0);
}

void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}


void	cleanup(t_free *free_all)
{
	if (free_all)
	{
		if (free_all->tree)
			free_tree(free_all->tree);
		if (free_all->new_array)
			free_new_array(&free_all->new_array);
		if (free_all->ast_helper)
			free_ast_helper(free_all->ast_helper);
		if (free_all->env_exp && free_all->env_exp->paths)
		{
			free_paths(free_all->env_exp->paths);
			free_all->env_exp->paths = NULL;
		}
	}
}


