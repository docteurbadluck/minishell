/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Be_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:40:57 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 16:59:01 by jholterh         ###   ########.fr       */
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
