/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_ft_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:46:02 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/24 16:33:53 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_unset deletes a variable from env and exp
int	ft_unset(t_env_exp *env_exp, char *content)
{
	int	spot;
	int	i;

	if (content == NULL)
	{
		ft_printf("unset: not enough arguments\n");
		return (1);
	}
	spot = find_envtype(env_exp->exp, content);
	if (spot == -1)
		return (0);
	delete_node(&env_exp->exp, spot);
	spot = find_envtype(env_exp->env, content);
	delete_node(&env_exp->env, spot);
	i = -1;
	while (env_exp->execute_env[++i])
		free(env_exp->execute_env[i]);
	free (env_exp->execute_env);
	env_exp->execute_env = create_env_from_linked_list(env_exp->env);
	return (0);
}
