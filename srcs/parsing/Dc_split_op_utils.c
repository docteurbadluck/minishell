/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dc_split_op_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:08:26 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/14 09:56:30 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_ampersand(char *input, int *i, int *y
		, t_parsed_command *array)
{
	if (input[*i + 1] == '&')
	{
		array[*y].text = ft_substr(input, *i, 2);
		(*i) += 2;
	}
	else
	{
		array[*y].text = ft_substr(input, *i, 1);
		(*i)++;
	}
	(*y)++;
}

static void	handle_pipe(char *input, int *i, int *y, t_parsed_command *array)
{
	if (input[*i + 1] == '|')
	{
		array[*y].text = ft_substr(input, *i, 2);
		(*i) += 2;
	}
	else
	{
		array[*y].text = ft_substr(input, *i, 1);
		(*i)++;
	}
	(*y)++;
}

void	split_operator(char *input, int *i, int *y, t_parsed_command *array)
{
	if (input[*i] == '&')
	{
		handle_ampersand(input, i, y, array);
		return ;
	}
	if (input[*i] == '|')
	{
		handle_pipe(input, i, y, array);
		return ;
	}
}

void	handle_greater(char *input, int *i, int *y, t_parsed_command *array)
{
	if (array->what_first == 0)
		array->what_first = 1;
	if (input[*i + 1] == '>')
	{
		array[*y].text = ft_substr(input, *i, 2);
		(*i) += 2;
	}
	else
	{
		array[*y].text = ft_substr(input, *i, 1);
		(*i)++;
	}
	(*y)++;
}
