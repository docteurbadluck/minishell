/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_ft_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:29:04 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/15 15:59:43 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_cd_home(t_env_exp *env_exp, int version)
{
	char	*home;

	ft_getenv(env_exp->env, "HOME", &home);
	if (home == NULL)
	{
		if (version == 0)
			write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	if (chdir(home) == -1)
	{
		if (version == 0)
			write(2, " No such file or directory\n", 26);
		return (1);
	}
	return (0);
}

static int	handle_cd_path(char **str, int version)
{
	if (chdir(str[1]) == -1)
	{
		if (version == 0)
			write(2, " No such file or directory\n", 26);
		return (1);
	}
	return (0);
}

int	ft_cd(t_env_exp *env_exp, char **str, int version)
{
	if (str[1] == NULL)
		return (handle_cd_home(env_exp, version));
	if (str[2] != NULL)
	{
		if (version == 0)
			write(2, " too many arguments\n", 19);
		return (1);
	}
	return (handle_cd_path(str, version));
}
