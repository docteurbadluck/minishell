/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Da_tokenise_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:08:26 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/24 16:19:15 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_arrow(char *input, int *i, int *y, t_parsed_command *array);
void	split_operator(char *input, int *i, int *y, t_parsed_command *array);
void	split_parenthesis(char *input, int *i, int *y, t_parsed_command *array);

void	split_special_char(char *input, int *i, int *y, t_parsed_command *a)
{
	split_operator(input, i, y, a);
	split_arrow(input, i, y, a);
	split_parenthesis(input, i, y, a);
}

void	split_arrow(char *input, int *i, int *y, t_parsed_command *array)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			array[*y].text = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			array[*y].text = ft_substr(input, *i, 1);
		(*y)++;
		return ;
	}
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			array[*y].text = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			array[*y].text = ft_substr(input, *i, 1);
		(*y)++;
		return ;
	}
}

void	split_operator(char *input, int *i, int *y, t_parsed_command *array)
{
	if (input[*i] == '&')
	{
		if (input[*i + 1] == '&')
		{
			array[*y].text = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			array[*y].text = ft_substr(input, *i, 1);
		(*y)++;
		return ;
	}
	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
		{
			array[*y].text = ft_substr(input, *i, 2);
			(*i)++;
		}
		else
			array[*y].text = ft_substr(input, *i, 1);
		(*y)++;
		return ;
	}
}

void	split_parenthesis(char *input, int *i, int *y, t_parsed_command *array)
{
	if (input[*i] == '(')
	{
		array[*y].text = ft_substr(input, *i, 1);
		(*y)++;
		return ;
	}
	if (input[*i] == ')')
	{
		array[*y].text = ft_substr(input, *i, 1);
		(*y)++;
		return ;
	}
}
