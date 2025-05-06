/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cb_count_word_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:22:10 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/06 13:57:05 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_op(int *i, const char *input, int *counter)
{
	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
			(*i)++;
		(*counter)++;
	}
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			(*i)++;
		(*counter)++;
	}
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			(*i)++;
		(*counter)++;
	}
	if (input[*i] == '&')
	{
		if (input[*i + 1] == '&')
			(*i)++;
		(*counter)++;
	}
}

int	char_is(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == ')' || c == '(' || c == '|'
		|| c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	set_flag(const char *input, int i, int *flag, int *counter)
{
	if (char_is(input[i]))
		*flag = 0;
	else if ((*flag) == 0)
	{
		(*counter)++;
		(*flag) = 1;
	}
}
