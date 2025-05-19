/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_variable_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:16:54 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/19 09:28:59 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_space_or_doll(char c);
int		lenght_variable(char *str);
char	**cut_input(char *input, int i);
char	*assembling(char *variable, char **array_of_str);
char	*handle_variable_expansion(char *input, int i, t_env_exp *env_exp);
char	*assembling(char *variable, char **array_of_str);

char	*variable_manager(char *input, t_env_exp *env_exp)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'')
		{
			flag++;
			flag %= 2;
		}
		if (input[i] == '$' && input[i + 1] != ' ' && input[i + 1] != '"'
			&& input[i + 1] != '\0' && !flag)
			return (handle_variable_expansion(input, i, env_exp));
		i++;
	}
	return (ft_strdup(input));
}

int	lenght_variable(char *str)
{
	int	i;

	str++;
	i = 0;
	while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\t'
		&& str[i] != '"' && str[i] != '\n')
	{
		i++;
	}
	i++;
	return (i);
}

static char	*allocate_and_copy(char *src, int len)
{
	char	*result;

	result = ft_calloc(sizeof(char), len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, src, len + 1);
	return (result);
}

char	**cut_input(char *input, int i)
{
	char	**array_of_str;
	int		compteur;

	array_of_str = ft_calloc(sizeof(char *), 4);
	if (!array_of_str)
		return (NULL);
	array_of_str[0] = allocate_and_copy(input, i);
	if (!array_of_str[0])
		return (NULL);
	if (input[i + 1] == '?')
		compteur = 2;
	else
		compteur = lenght_variable(&input[i]);
	array_of_str[1] = allocate_and_copy(&input[i], compteur);
	if (!array_of_str[1])
		return (NULL);
	i += compteur;
	if (!input[i])
		return (array_of_str);
	array_of_str[2] = allocate_and_copy(&input[i], ft_strlen(&input[i]));
	if (!array_of_str[2])
		return (NULL);
	return (array_of_str);
}

char	*assembling(char *variable, char **array_of_str)
{
	char	*result;
	char	*temp;

	result = NULL;
	if (array_of_str[0])
	{
		if (variable)
			result = ft_strjoin(array_of_str[0], variable);
		else
			result = ft_strdup(array_of_str[0]);
		free(array_of_str[0]);
	}
	if (array_of_str[2])
	{
		temp = result;
		result = ft_strjoin(result, array_of_str[2]);
		free(temp);
		free(array_of_str[2]);
	}
	free(array_of_str[1]);
	free(array_of_str);
	return (result);
}
