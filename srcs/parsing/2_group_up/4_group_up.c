/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   G_group_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/06/02 16:28:05 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "group_up.h"

//void	set_up_arg(t_parsed_command *array);
void	create_new_array(t_parsed_command *array, t_parsed_command *new);
int		set_up_arg(t_parsed_command *array);

t_parsed_command	*group_up(t_parsed_command **array)
{
	t_parsed_command	*new;
	int					count;

	if (set_up_arg(*array))
	{
		return (NULL);
	}
	count = count_new_array(*array);
	new = ft_calloc(count + 1, sizeof(t_parsed_command));
	if (!new)
		return (NULL);
	create_new_array(*array, new);
	return (new);
}

int	set_up_arg(t_parsed_command *array)
{
	int	i;
	int	count_arg;
	int	save_pos;

	i = 0;
	while (array[i].text)
	{
		count_arg = 0;
		if (array[i].group_id > 0)
		{
			save_pos = i;
			count_arg = count_arguments_and_move(array, &i);
			if (!count_arg)
				continue ;
			if (allocate_and_fill_arguments(array, save_pos, count_arg, &i))
				return (1);
		}
		if (array[i].group_id <= 0)
			array[i].command = ft_strdup(array[i].text); 
		if (!array[i].text)
			break ;
		i++;
	}
	return (0);
}

void	create_new_array(t_parsed_command *array, t_parsed_command *new)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (array[i].text)
	{
		if (array[i].command)
		{
			new[y] = array[i];
			y++;
		}
		else
		{
			free(array[i].text);
		}
		i++;
	}
	free(array);
}
