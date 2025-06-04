/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Be_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:40:57 by tdeliot           #+#    #+#             */
/*   Updated: 2025/06/03 10:39:53 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_wildcard_list(void *content)
{
	t_tracker	*ptr;
	int			i;

	i = 0;
	ptr = content;
	free(ptr->cp_input);
	if (ptr->list_of_matched_name)
	{
		while (ptr->list_of_matched_name[i])
		{
			free(ptr->list_of_matched_name[i]);
			i++;
		}
		free(ptr->list_of_matched_name);
	}
	free(ptr);
}

void	free_str_list(void *content)
{
	free(content);
}

void	copy_before_wildcard(t_tracker *ptr_tracker,
	t_list **list_of_str, int *i)
{
	char	*temp;

	while ((*ptr_tracker->groupped_array_argument)[*i]
	&& ft_strncmp(ptr_tracker->cp_input
		, (*ptr_tracker->groupped_array_argument)[*i]
		, ft_strlen(ptr_tracker->cp_input)))
	{
		temp = ft_strdup((*ptr_tracker->groupped_array_argument)[*i]);
		ft_lstadd_back(list_of_str, ft_lstnew(temp));
		(*i)++;
	}
}

char	*prepare_input_for_wildcard(char *input, char **pwd)
{
	char	*new_input;

	*pwd = getcwd(NULL, 0);
	if (check_current_dir_input(input) == 1)
	{
		free(*pwd);
		printf("incorrect directory wildcard\n");
		return (NULL);
	}
	if (check_current_dir_input(input) == 2)
		new_input = input + ft_strlen(*pwd) + 1;
	else
		new_input = input;
	return (new_input);
}
