/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cb_count_word_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:22:10 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/24 16:23:01 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
