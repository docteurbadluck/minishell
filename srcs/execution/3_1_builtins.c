/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_1_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:53:25 by jholterh          #+#    #+#             */
/*   Updated: 2025/06/02 16:17:31 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_build_in(char **command)
{
	if (!command[0])
		return (0);
	if (!ft_strncmp(command[0], "echo", 5))
		return (1);
	if (!ft_strncmp(command[0], "cd", 3))
		return (2);
	if (!ft_strncmp(command[0], "pwd", 4))
		return (3);
	if (!ft_strncmp(command[0], "export", 7))
		return (4);
	if (!ft_strncmp(command[0], "unset", 6))
		return (5);
	if (!ft_strncmp(command[0], "env", 4))
		return (6);
	if (!ft_strncmp(command[0], "exit", 5))
		return (7);
	if (!ft_strncmp(command[0], "$?", 3))
		return (8);
	return (-1);
}

int	build_in_addition(char **command, t_env_exp *env_exp, int return_value)
{
	if (return_value == 4)
	{
		if (ft_export(env_exp, command, 1) != 0)
			return (1);
		return (0);
	}
	if (return_value == 5)
	{
		if (ft_unset(env_exp, command[1]) != 0)
			return (1);
		return (0);
	}
	if (return_value == 6)
	{
		ft_env(env_exp->env, 2);
		return (0);
	}
	if (return_value == 7)
	{
		ft_exit(command, 1);
	}
	if (return_value == 8)
		ft_printf("%d\n", env_exp->dollar_question);
	return (-1);
}

int	execute_build_in(char **command, t_env_exp *env_exp, int return_value)
{
	if (return_value == 1)
	{
		ft_echo(command);
		return (0);
	}
	if (return_value == 2)
	{
		if (ft_cd(env_exp, command, 1) == 1)
			return (1);
		return (0);
	}
	if (return_value == 3)
	{
		if (ft_pwd() != 0)
			return (1);
		return (0);
	}
	return (build_in_addition(command, env_exp, return_value));
}
