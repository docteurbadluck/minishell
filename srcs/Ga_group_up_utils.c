/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ga_group_up_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/02 15:44:41 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//modify this function to put into a new array the 
//redirection.

void	allocate_argument_arrays(t_parsed_command *array,
			int save_pos, int count_arg)
{
	array[save_pos].redirection_array
		= ft_calloc(count_arg + 1, sizeof(char *));
	if (!array[save_pos].redirection_array)
		return ;
	array[save_pos].arguments = ft_calloc(count_arg + 1, sizeof(char *));
	if (!array[save_pos].arguments)
		return ;
}

void	fill_redirections(t_parsed_command *array, int save_pos, int *i, int *z)
{
	array[save_pos].redirection_array[*z] = ft_strdup(array[*i].text);
	(*i)++;
	(*z)++;
	if (array[*i].text && array[save_pos].group_id == array[*i].group_id)
	{
		array[save_pos].redirection_array[*z] = ft_strdup(array[*i].text);
		(*i)++;
		(*z)++;
	}
}

void	fill_arguments(t_parsed_command *array, int save_pos, int *i, int *y)
{
	array[save_pos].arguments[*y] = ft_strdup(array[*i].text);
	(*i)++;
	(*y)++;
}

void	fill_arguments_and_redirections(t_parsed_command *array,
			int save_pos, int *i)
{
	int	y;
	int	z;

	y = 0;
	z = 0;
	while (array[*i].text && array[save_pos].group_id == array[*i].group_id)
	{
		if (array[*i].logical_operator == 4)
			fill_redirections(array, save_pos, i, &z);
		else
			fill_arguments(array, save_pos, i, &y);
	}
	(*i)--;
	array[save_pos].command = ft_strdup(array[save_pos].arguments[0]);
}

void	allocate_and_fill_arguments(t_parsed_command *array,
			int save_pos, int count_arg, int *i)
{
	allocate_argument_arrays(array, save_pos, count_arg);
	fill_arguments_and_redirections(array, save_pos, i);
}
