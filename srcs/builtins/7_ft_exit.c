/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_ft_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:13:20 by jholterh          #+#    #+#             */
/*   Updated: 2025/06/02 16:13:17 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_argument(const char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (arg[i] == '\0')
		return (0);
	while (arg[i])
	{
		if (!isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_exit_error(const char *message, int exit_code, int version)
{
	if (version == 0)
		write(2, message, 32);
	exit(exit_code);
}

void	ft_exit(char **args, int version)
{
	int	number;

	if (args == NULL || args[0] == NULL || args[1] == NULL)
		exit(0);
	if (args[2] != NULL)
		handle_exit_error("exit: too many arguments\n", 1, version);
	if (!is_numeric_argument(args[1]))
		handle_exit_error("exit: numeric argument required\n", 2, version);
	number = atoi(args[1]);
	number = (number % 256 + 256) % 256;
	exit(number);
}
