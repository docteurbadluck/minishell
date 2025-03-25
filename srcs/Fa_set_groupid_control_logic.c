/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fa_set_groupid_control_logic.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/25 16:25:57 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	give_value(t_parsed_command *array, int i)
{
	array[i].group_id = 0;
	if (array[i].logical_operator == -1)
		array[i].group_id = -1;
	if (array[i].logical_operator == -2)
		array[i].group_id = -2;
}

int	control_border_logic(t_parsed_command *array)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (array[i + 1].text)
		i++;
	while (array[i].group_id == -1 || array[i].group_id == -2)
		i--;
	while (array[y].group_id == -1 || array[y].group_id == -2)
		y++;
	if (array[y].group_id == 0 || array[i].group_id == 0)
	{
		printf("error control logic\n");
		return (-1);
	}
	return (0);
}

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

void	free_new_array(t_parsed_command **new_array)
{
	int	i;
	int	y;

	i = 0;
	while ((*new_array)[i].text)
	{
		y = 0;
		free((*new_array)[i].text);
		free((*new_array)[i].command);
		if ((*new_array)[i].arguments)
		{
			while ((*new_array)[i].arguments[y])
			{
				free((*new_array)[i].arguments[y]);
				y++;
			}
			free((*new_array)[i].arguments);
		}
		i++;
	}
	free(*new_array);
}
