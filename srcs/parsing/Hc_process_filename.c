/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hc_process_filename.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 17:00:44 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quote_and_space(char *result,
	const char *input, char other_quote, size_t len)
{
	char	*modified;

	if (ft_strchr(result, other_quote))
	{
		free(result);
		return (ft_strdup(input));
	}
	if (ft_strchr(result, ' '))
	{
		modified = malloc(len + 1);
		if (!modified)
		{
			free(result);
			return (NULL);
		}
		modified[0] = '\'';
		ft_memcpy(modified + 1, result, ft_strlen(result));
		modified[ft_strlen(result) + 1] = '\'';
		modified[ft_strlen(result) + 2] = '\0';
		free(result);
		return (modified);
	}
	return (result);
}

char	*extract_valid_filename(const char *input, char quote_type)
{
	size_t	len;
	char	*result;
	char	other_quote;

	len = ft_strlen(input);
	result = ft_substr(input, 1, len - 2);
	if (!result)
		return (NULL);
	if (quote_type == '"')
		other_quote = '\'';
	else
		other_quote = '"';
	return (handle_quote_and_space(result, input, other_quote, len));
}

char	*process_redirection_filename(const char *input)
{
	size_t	len;
	char	quote_type;

	if (!input || !*input)
		return (NULL);
	len = ft_strlen(input);
	if (len < 2 || (input[0] != '\'' && input[0] != '"'))
		return (ft_strdup(input));
	quote_type = input[0];
	return (extract_valid_filename(input, quote_type));
}
