/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gb_group_up_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 17:00:32 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (array[*i].text && array[save_pos].group_id
		== array[*i].group_id)
	{
		count_arg++;
		(*i)++;
	}
	*i = save_pos;
	return (count_arg);
}
