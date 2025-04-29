/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_1_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:07:36 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/28 12:52:04 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_build_in(char **command, t_env_exp *env_exp)
{
	if (!ft_strncmp(command[0], "echo", 5))
		return (0);
	if (!ft_strncmp(command[0], "cd", 3))
		return (1);
	if (!ft_strncmp(command[0], "pwd", 4))
		return (2);
	if (!ft_strncmp(command[0], "export", 7))
		return (3);
	if (!ft_strncmp(command[0], "unset", 6))
		return (4);
	if (!ft_strncmp(command[0], "env", 4))
		return (5);
	if (!ft_strncmp(command[0], "exit", 5))
	{
		printf("exiting\n");
		// maybe should free here
		exit(0);
	}
	return (-1);
}

int	build_in_addition(char **command, t_env_exp *env_exp, int return_value)
{
	if (return_value == 3)
	{
		if (ft_export(env_exp, command[1], 1) != 0)
			return (1);
		return (0);
	}
	if (return_value == 4)
	{
		if (ft_unset(env_exp, command[1]) != 0)
			return (1);
		return (0);
	}
	if (return_value == 5)
	{
		ft_env(env_exp->env, 2);
		return (0);
	}
	return (-1);
}

int	execute_build_in(char **command, t_env_exp *env_exp, int return_value)
{
	if (return_value == 0)
	{
		ft_echo(command);
		return (0);
	}
	if (return_value == 1)
	{
		if (ft_cd(env_exp, command[1], 1) == 1)
			return (1);
		return (0);
	}
	if (return_value == 2)
	{
		if (ft_pwd() != 0)
			return (1);
		return (0);
	}
	return (build_in_addition(command, env_exp, return_value));
}
