/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ha_set_outfiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/03 10:42:52 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int set_outfiles(t_parsed_command *grouped_array)
{
	int	i;
	int	y;

	i = 0;
	while (grouped_array[i].command)
	{
		while (grouped_array[i].redirection_array[y])
		{
			printf("%s, ", grouped_array[i].redirection_array[y]);
		}
		
	}
}
