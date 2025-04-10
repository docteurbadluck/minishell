/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Xa_free_new_array_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/09 14:05:42 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_iofiles(t_parsed_command *command)
{
	int	i;

	if (command->input_file)
	{
		i = 0;
		while (command->input_file[i].filename)
		{
			free(command->input_file[i].filename);
			i++;
		}
		free(command->input_file);
		command->input_file = NULL;
	}
	if (command->output_file)
	{
		i = 0;
		while (command->output_file[i].filename)
		{
			free(command->output_file[i].filename);
			i++;
		}
		free(command->output_file);
		command->output_file = NULL;
	}
}
