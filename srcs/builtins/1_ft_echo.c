/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_ft_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:29:00 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/24 16:27:25 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **str)
{
	int	i;
	int	version;
	int	flag;

	flag = 0;
	version = 0;
	i = 0;
	while (str[++i])
	{
		if (ft_strncmp(str[i], "-n\0", 3) == 0)
			version = 1;
		else
		{
			if (flag == 1)
				write(1, " ", 1);
			ft_putstr_fd(str[i], 1);
			flag = 1;
		}
	}
	if (version == 0)
		write(1, "\n", 1);
	return (0);
}
