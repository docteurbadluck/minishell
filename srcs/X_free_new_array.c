/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   X_free_new_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/03 16:27:10 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(t_parsed_command **array)
{
	int	i;

	i = 0;
	while ((*array)[i].text)
	{
		free((*array)[i].text);
		i++;
	}
	free(*array);
}

void	free_arguments(char **arguments)
{
	int	y;

	y = 0;
	if (!arguments)
		return ;
	while (arguments[y])
	{
		free(arguments[y]);
		y++;
	}
	free(arguments);
}

void	free_redirections(char **redirection_array)
{
	int	z;

	z = 0;
	if (!redirection_array)
		return ;
	while (redirection_array[z])
	{
		free(redirection_array[z]);
		z++;
	}
	free(redirection_array);
}

void	free_iofiles(t_parsed_command *command)
{
	int	i;

	if (!command)
		return;

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


void	free_parsed_command(t_parsed_command *command)
{
	if (!command)
		return ;
	free(command->text);
	free(command->command);
	free_arguments(command->arguments);
	free_redirections(command->redirection_array);
	free_iofiles(command);
}

void	free_new_array(t_parsed_command **new_array)
{
	int	i;

	i = 0;
	if (!new_array || !*new_array)
		return ;
	while ((*new_array)[i].text) 
	{
		free_parsed_command(&(*new_array)[i]);
		i++;
	}
	free(*new_array);
}
