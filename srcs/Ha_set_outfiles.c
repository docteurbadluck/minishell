/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ha_set_outfiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/03 11:35:36 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//function with all sign with mutlipe of them
int	control_operator(char *redirection)
{
	int y;
	y = 0;
	if (redirection && (!ft_strncmp(redirection, ">", 1) || !ft_strncmp(redirection, "<", 1)))
		return 0;

	return 1;
}

int	control_redirection_logique(t_parsed_command *grouped_array)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (grouped_array[i].command)
	{
		if (grouped_array[i].redirection_array[y])
		{
			while (grouped_array[i].redirection_array[y])
			{
				/*
				if (!ft_strncmp("\'\'", grouped_array[i].redirection_array[y], 2) || (!ft_strncmp("\"\"", grouped_array[i].redirection_array[y], 2)))
					return 1;
					*/
				//printf("%s, ", grouped_array[i].redirection_array[y]);
				if (!control_operator(grouped_array[i].redirection_array[y]) && !control_operator(grouped_array[i].redirection_array[y + 1])) // contro > >  two operator in a row.
				{
					return (1);
				}
				y++;
			}
			y--;
			if (!control_operator(grouped_array[i].redirection_array[y]))		// control last one. 
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}


int set_outfiles(t_parsed_command *grouped_array)
{

	if (control_redirection_logique(grouped_array))
		return (1);
	//attribute
		
	return (0);
}



//count infile and outfile
