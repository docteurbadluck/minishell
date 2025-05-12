/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_5_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docteurbadluck <docteurbadluck@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:06:45 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/12 18:05:52 by docteurbadl      ###   ########.fr       */
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

void	handle_quoted_segment(char *input, int *i, int *start, char **parts)
{
	char	quote;
	char	*quoted;

	if (*i > *start)
		*parts = ft_strjoin_free(*parts, ft_substr(input, *start, *i - *start));
	quote = input[*i];
	*start = ++(*i);
	while (input[*i] && (input[*i] != quote 
			|| (quote == '"' && input[*i - 1] == '\\')))
		(*i)++;
	quoted = ft_substr(input, *start, *i - *start);
	*parts = ft_strjoin_free(*parts, quoted);
	if (input[*i])
		(*i)++;
	*start = *i;
}

char	*remove_quotes(char *input)
{
	char	*parts;
	int		i;
	int		start;

	parts = ft_strdup("");
	start = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			handle_quoted_segment(input, &i, &start, &parts);
		else
			i++;
	}
	if (start < i)
		parts = ft_strjoin_free(parts, ft_substr(input, start, i - start));
	if (!parts)
		parts = ft_strdup(input);
	return (parts);
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
