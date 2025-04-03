/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ba_wildcard_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:40:57 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/03 09:45:55 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	compte_name(void)
{
	DIR				*one_dir;
	struct dirent	*entry;
	char			*pwd;
	int				nbr_of_name;

	nbr_of_name = 0;
	pwd = getenv("PWD");
	one_dir = opendir(pwd);
	entry = readdir(one_dir);
	while (entry != NULL)
	{
		nbr_of_name++;
		entry = readdir(one_dir);
	}
	closedir(one_dir);
	return (nbr_of_name);
}

char	**name_array_generator(void)
{
	DIR				*my_dir;
	struct dirent	*entry;
	char			**list_of_name;
	int				i;

	i = 0;
	list_of_name = ft_calloc((compte_name() + 1), sizeof(char *));
	my_dir = opendir(getenv("PWD"));
	entry = readdir(my_dir);
	while (entry != NULL)
	{
		list_of_name[i] = ft_strdup(entry->d_name);
		i++;
		entry = readdir(my_dir);
	}
	closedir(my_dir);
	return (list_of_name);
}

int	check_current_dir_input(char *input)
{
	char	*pwd; 
	int		len_pwd;

	pwd = getenv("PWD");
	len_pwd = ft_strlen(pwd);
	if (ft_strchr(input, '/'))
	{
		if (ft_strncmp(input, pwd, len_pwd) == 0
			&& input[len_pwd] == '/')
			return (2);
		return (1);
	}
	else 
		return (0);
}

/*
int	matching_name(char *pattern, char *name)
{
	if (*pattern == '\0' && *name == '\0')
		return (0);
	if (*pattern == '\0')
		return (1); 
	if (*pattern == '*')
	{
		if (matching_name(pattern + 1, name) == 0)
			return (0);
		if (*name != '\0' && matching_name(pattern, name + 1) == 0)
			return (0);
		return (1);
	}
	if (*pattern == *name)
		return (matching_name(pattern + 1, name + 1));
	return (1);
}
*/

int	matching_name(char *pattern, char *name, int first_call)
{
	if (first_call && *name == '.') // Ignore files starting with punctuation
		return (1);
	if (*pattern == '\0' && *name == '\0')
		return (0);
	if (*pattern == '\0')
		return (1);
	if (*pattern == '*')
	{
		if (matching_name(pattern + 1, name, 0) == 0)
			return (0);
		if (*name != '\0' && matching_name(pattern, name + 1, 0) == 0)
			return (0);
		return (1);
	}
	if (*pattern == *name)
		return (matching_name(pattern + 1, name + 1, 0));
	return (1);
}

char	*assembling_wild(char *variable, char **array_of_str)
{
	char	*result;

	result = NULL;
	free(array_of_str[1]);
	if (array_of_str[0])
	{
		if (variable)
		{
			result = ft_strjoin(array_of_str[0], variable);
			free(array_of_str[0]);
			free(variable);
		}
		else
		{
			result = ft_strdup(array_of_str[0]);
			free(array_of_str[0]);
		}
	}
	if (array_of_str[2])
	{
		result = ft_strjoin_2(result, array_of_str[2]);
		free(array_of_str[2]);
	}
	free(array_of_str);
	return (result);
}
