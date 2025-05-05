/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_ft_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:50:54 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/16 18:21:13 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>

void	ft_exit(char **args)
{
	int	number;
	int	i;

	if (args == NULL || args[0] == NULL || args[1] == NULL)
		exit(0);
	i = 0;
	if (args[1][i] == '-' || args[1][i] == '+')
		i++;
	if (args[1][i] == '\0')
	{
		write(2, "exit: numeric argument required\n", 32);
		exit(255);
	}
	while (args[1][i])
	{
		if (!isdigit(args[1][i]))
		{
			write(2, "exit: numeric argument required\n", 32);
			exit(255);
		}
		i++;
	}
	if (args[2] != NULL)
	{
		write(2, "exit: too many arguments\n", 25);
		exit(1);
	}
	number = ft_atoi(args[1]);
	number = (number % 256 + 256) % 256;
	exit(number);
}









