/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_5_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:06:45 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/06 14:55:16 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str1;
	char	*str2;
	char	*result;

	if (s1)
		str1 = s1;
	else
		str1 = "";
	if (s2)
		str2 = s2;
	else
		str2 = "";
	result = ft_strjoin(str1, str2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (result);
}

char	*remove_quotes(char *input)
{
	char	*result;
	char	**parts;
	int		i;
	int		start;
	char	*quoted;
	char	quote;
	int		begin;

	start = 0;
	i = 0;
	parts = ft_calloc(sizeof(char *), 4);
	result = NULL;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (i > start)
				parts[0] = ft_strjoin_free(parts[0],
						ft_substr(input, start, i - start));
			quote = input[i];
			begin = ++i;
			while (input[i] && (input[i] != quote
					|| (quote == '"' && input[i - 1] == '\\')))
				i++;
			quoted = ft_substr(input, begin, i - begin);
			parts[0] = ft_strjoin_free(parts[0], quoted);
			if (input[i])
				i++;
			start = i;
		}
		else
			i++;
	}
	if (start < i)
		parts[0] = ft_strjoin_free(parts[0],
				ft_substr(input, start, i - start));
	result = ft_strdup(parts[0]);
	free(parts[0]);
	free(parts);
	return (result);
}

char	*remove_backslash(char *input)
{
	char	*result;
	int		i;
	int		y;

	result = ft_calloc(1, ft_strlen(input));
	i = 0;
	y = 0;
	while (input[i])
	{
		if (input[i] != '\\')
		{
			result[y] = input[i];
			y++;
		}
		i++;
	}
	return (result);
}
