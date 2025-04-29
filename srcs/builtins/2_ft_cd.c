/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_ft_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:29:04 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/24 16:32:45 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_env_exp *env_exp, char *str, int version)
{
	char	*home;

	if (str == NULL)
	{
		ft_getenv(env_exp->env, "HOME", &home);
		if (home == NULL)
		{
			if (version == 0)
				ft_printf("cd: HOME not set\n");
			return (1);
		}
		if (chdir(home) == -1)
			return (ft_printf("cd: %s\n", strerror(errno)), 1);
	}
	else if (chdir(str) == -1)
		return (ft_printf("cd: %s: %s\n", strerror(errno), str), 1);
	return (0);
}
