/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ga_group_up_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/25 16:18:55 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_new_array(t_parsed_command *array)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (array[i].text)
	{
		if (array[i].command)
			count++;
		i++;
	}
	return (count);
}

int	count_arguments_and_move(t_parsed_command *array, int *i)
{
	int	count_arg;
	int	save_pos;

	count_arg = 0;
	save_pos = *i;
	while (array[*i + 1].text && array[save_pos].group_id
		== array[*i + 1].group_id)
	{
		count_arg++;
		(*i)++;
	}
	*i = save_pos + 1;
	return (count_arg);
}

void	allocate_and_fill_arguments(t_parsed_command *array
	, int save_pos, int count_arg, int *i)
{
	int	y;

	y = 0;
	array[save_pos].arguments = ft_calloc(count_arg + 1, sizeof(char *));
	if (!array[save_pos].arguments)
		return ;
	while (array[*i].text && array[save_pos].group_id == array[*i].group_id)
	{
		array[save_pos].arguments[y] = ft_strdup(array[*i].text);
		(*i)++;
		y++;
	}
	(*i)--;
}
