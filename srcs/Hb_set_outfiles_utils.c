/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hb_set_outfiles_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 11:00:17 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//function with all sign with mutlipe of them
int	control_operator(char *redirection)
{
	int	y;

	y = 0;
	if (redirection && (!ft_strncmp(redirection, ">", 1)
			|| !ft_strncmp(redirection, "<", 1)))
		return (0);
	return (1);
}

int	is_redirection_invalid(char **redirection_array)
{
	int	y;

	y = 0;
	while (redirection_array[y])
	{
		if (!ft_strncmp("\'\'", redirection_array[y], 2)
			|| (!ft_strncmp("\"\"", redirection_array[y], 2)))
			return (1);
		if (!control_operator(redirection_array[y])
			&& !control_operator(redirection_array[y + 1]))
			return (1);
		y++;
	}
	y--;
	if (!control_operator(redirection_array[y]))
		return (1);
	return (0);
}

int	control_redirection_logique(t_parsed_command *grouped_array)
{
	int	i;

	i = -1;
	while (grouped_array[++i].command)
	{
		if (grouped_array[i].logical_operator != 0)
			continue ;
		if (grouped_array[i].redirection_array[0])
		{
			if (is_redirection_invalid(grouped_array[i].redirection_array))
				return (1);
		}
	}
	return (0);
}

int	which_symbole(char *redirection)
{
	if (!ft_strncmp(">>", redirection, 2))
	{
		return (3);
	}
	if (!ft_strncmp("<<", redirection, 2))
	{
		return (4);
	}
	if (!ft_strncmp(">", redirection, 1))
	{
		return (1);
	}
	if (!ft_strncmp("<", redirection, 1))
	{
		return (2);
	}
	return (0);
}

int	count_files_names(char	**redirection_array)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (redirection_array[i])
	{
		if (which_symbole(redirection_array[i]))
			count++;
		i++;
	}
	return (count);
}
