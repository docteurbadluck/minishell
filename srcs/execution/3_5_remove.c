/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_5_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:06:45 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/13 17:14:53 by jholterh         ###   ########.fr       */
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

void	remove_quotation(t_parsed_command **command)
{
	int		i;
	char	*result;

	i = -1;
	while ((*command)->arguments[++i])
	{
		if ((*command)->input_file && (*command)->input_file->filename)
		{
			result = remove_quotes((*command)->input_file->filename);
			free((*command)->input_file->filename);
			(*command)->input_file->filename = result;
		}
		if ((*command)->output_file && (*command)->output_file->filename)
		{
			result = remove_quotes((*command)->output_file->filename);
			free((*command)->output_file->filename);
			(*command)->output_file->filename = result;
		}
		result = remove_quotes((*command)->arguments[i]);
		free((*command)->arguments[i]);
		(*command)->arguments[i] = result;
	}
}
