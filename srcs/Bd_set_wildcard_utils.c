/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bd_set_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:40:57 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/02 18:04:59 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_matched_names(t_tracker *ptr_tracker, t_list **list_of_str, int *z)
{
	char	*temp;

	while (ptr_tracker->list_of_matched_name[*z])
	{
		temp = ft_strdup(ptr_tracker->list_of_matched_name[*z]);
		ft_lstadd_back(list_of_str, ft_lstnew(temp));
		(*z)++;
	}
}

void	copy_after_wildcard(t_tracker *ptr_tracker,
			t_list **list_of_str, int *i)
{
	char	*temp;

	(*i)++;
	while ((*ptr_tracker->groupped_array_argument)[*i])
	{
		temp = ft_strdup((*ptr_tracker->groupped_array_argument)[*i]);
		ft_lstadd_back(list_of_str, ft_lstnew(temp));
		(*i)++;
	}
}

void	free_old_arguments(t_tracker *ptr_tracker)
{
	int	i;

	i = 0;
	while ((*ptr_tracker->groupped_array_argument)[i])
	{
		free((*ptr_tracker->groupped_array_argument)[i]);
		i++;
	}
	free((*ptr_tracker->groupped_array_argument));
	(*ptr_tracker->groupped_array_argument) = NULL;
}

void	replace_with_new_arguments(t_tracker *ptr_tracker, t_list *list_of_str)
{
	t_list	*ptr;
	int		i;

	ptr = list_of_str;
	i = 0;
	*ptr_tracker->groupped_array_argument
		= ft_calloc(ft_lstsize(list_of_str) + 1, sizeof(char *));
	while (ptr)
	{
		(*ptr_tracker->groupped_array_argument)[i] 
			= ft_strdup((char *)ptr->content);
		i++;
		ptr = ptr->next;
	}
}

void	modify_arg(t_tracker *ptr_tracker)
{
	t_list	*list_of_str;
	int		i;
	int		z;

	i = 0;
	z = 0;
	list_of_str = NULL;
	copy_before_wildcard(ptr_tracker, &list_of_str, &i);
	copy_matched_names(ptr_tracker, &list_of_str, &z);
	copy_after_wildcard(ptr_tracker, &list_of_str, &i);
	free_old_arguments(ptr_tracker);
	replace_with_new_arguments(ptr_tracker, list_of_str);
	ft_lstclear(&list_of_str, &free_str_list);
}
