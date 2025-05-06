/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Db_split_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:08:26 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/06 14:16:20 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quoted_part(char *input, int *i, char **word)
{
	int		start;
	int		len;
	char	quote;
	char	*tmp;

	quote = input[*i];
	start = (*i);
	(*i)++;
	len = 0;
	while (input[*i] && input[*i] != quote)
	{
		(*i)++;
		len++;
	}
	tmp = ft_substr(input, start, len + 2);
	*word = ft_strjoin_2(*word, tmp);
	free(tmp);
	if (input[*i] == quote)
		(*i)++;
}

static void	handle_unquoted_part(char *input, int *i, char **word)
{
	int		start;
	int		len;
	char	*tmp;

	start = *i;
	len = 0;
	while (input[*i] && !char_is(input[*i])
		&& input[*i] != '\'' && input[*i] != '"')
	{
		(*i)++;
		len++;
	}
	tmp = ft_substr(input, start, len);
	*word = ft_strjoin_2(*word, tmp);
	free(tmp);
}

void	split_word_unit(char *input, int *i, int *y, t_parsed_command *array)
{
	char	*word;

	word = NULL;
	while (input[*i])
	{
		if (char_is(input[*i]))
			break ;
		if (input[*i] == '\'' || input[*i] == '"')
			handle_quoted_part(input, i, &word);
		else
			handle_unquoted_part(input, i, &word);
	}
	if (word)
	{
		array[*y].text = word;
		(*y)++;
	}
}
