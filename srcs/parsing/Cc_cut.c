/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cc_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:22:10 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/06 14:22:47 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_quoted_section(const char *input, int i, char quote)
{
	i++;
	while (input[i])
	{
		if (input[i] == '\\' && input[i + 1] == quote)
			i += 2;
		else if (input[i] == quote)
			break ;
		else
			i++;
	}
	if (input[i] == '\0')
		return (-1);
	return (i + 1);
}

static int	handle_escaped_char(const char *input, int *i)
{
	if (input[*i] == '\\' && (input[*i + 1] == '"' || input[*i + 1] == '\''))
	{
		*i += 2;
		return (1);
	}
	return (0);
}

static int	skip_and_update_quote(const char *input,
		int *i, int *counter, int *flag)
{
	int		new_pos;
	int		has_quote;

	has_quote = 0;
	while (input[*i] == '"' || input[*i] == '\'')
	{
		new_pos = skip_quoted_section(input, *i, input[*i]);
		if (new_pos == -1)
			return (-1);
		*i = new_pos;
		has_quote = 1;
	}
	if (!has_quote)
		return (0);
	if (*flag == 0)
		(*counter)++;
	if (input[*i] == '(' || input[*i] == ')')
		(*counter)++;
	while (input[*i] && !char_is(input[*i]))
		(*i)++;
	*flag = 0;
	return (1);
}

int	skip_escaped_or_quoted(const char *input, int *i, int *counter, int *flag)
{
	if (handle_escaped_char(input, i))
		return (1);
	return (skip_and_update_quote(input, i, counter, flag));
}
