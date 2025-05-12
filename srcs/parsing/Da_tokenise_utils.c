/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Da_tokenise_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:08:26 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 16:59:12 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (array->what_first == 0)
			array->what_first = 1;
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
		if (array->what_first == 0)
			array->what_first = 2;
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

void	split_double_quote(char *input, int *i, int *y, t_parsed_command *array)
{
	int	save;
	int	count_letter;

	if (input[*i] == '"')
	{
		save = *i;
		count_letter = 1;
		while (input[++(*i)])
		{
			if (input[(*i)] == '"' && input[(*i) - 1] != '\\')
				break ;
			count_letter++;
		}
		array[*y].text = ft_substr(input, save, count_letter + 1);
		(*y)++;
		return ;
	}
}
