/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Na_input_count_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/26 10:55:17 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_heredoc(t_parsed_command *ptr)
{
	int	i;
	int	y;
	int	heredoc_counter;

	heredoc_counter = 0;
	y = 0;
	i = 0;
	while (ptr[i].command)
	{
		y = 0;
		while (ptr[i].input_file && ptr[i].input_file[y].filename)
		{
			if (ptr[i].input_file[y].mode == 4)
				heredoc_counter++;
			y++;
		}
		i++; 
	}
	return (heredoc_counter);
}
