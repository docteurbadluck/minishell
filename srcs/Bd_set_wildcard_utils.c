/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bd_set_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:40:57 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/02 10:44:46 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_until_wildcard(t_list **list_of_str
		, t_tracker *ptr_tracker, int *i)
{
	char	*temp;

	while ((*ptr_tracker->groupped_array_argument)[*i] &&
		ft_strncmp(ptr_tracker->cp_input
		, (*ptr_tracker->groupped_array_argument)[*i],
		ft_strlen(ptr_tracker->cp_input)))
	{
		temp = ft_strdup((*ptr_tracker->groupped_array_argument)[*i]);
		ft_lstadd_back(list_of_str, ft_lstnew(temp));
		(*i)++;
	}
}

void	copy_matched_names(t_list **list_of_str, t_tracker *ptr_tracker)
{
	int		z;
	char	*temp;

	z = 0;
	while (ptr_tracker->list_of_matched_name[z])
	{
		temp = ft_strdup(ptr_tracker->list_of_matched_name[z]);
		ft_lstadd_back(list_of_str, ft_lstnew(temp));
		z++;
	}
}

// (*i) ++ skip the wildcard 
void	copy_remaining_args(t_list **list_of_str
	, t_tracker *ptr_tracker, int *i)
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

void	replace_groupped_array(t_list *list_of_str, t_tracker *ptr_tracker)
{
	t_list	*ptr;
	int		i;

	i = 0;
	while ((*ptr_tracker->groupped_array_argument)[i])
	{
		free((*ptr_tracker->groupped_array_argument)[i]);
		i++;
	}
	free((*ptr_tracker->groupped_array_argument));
	(*ptr_tracker->groupped_array_argument) = NULL;
	*ptr_tracker->groupped_array_argument
		= ft_calloc(ft_lstsize(list_of_str) + 1, sizeof(char *));
	i = 0;
	ptr = list_of_str;
	while (ptr)
	{
		(*ptr_tracker->groupped_array_argument)[i]
			= ft_strdup((char *)ptr->content);
		i++;
		ptr = ptr->next;
	}
	ft_lstclear(&list_of_str, &free_str_list);
}

void	modify_arg(t_tracker *ptr_tracker)
{
	t_list	*list_of_str;
	int		i;

	list_of_str = NULL;
	i = 0;
	copy_until_wildcard(&list_of_str, ptr_tracker, &i);
	copy_matched_names(&list_of_str, ptr_tracker);
	copy_remaining_args(&list_of_str, ptr_tracker, &i);
	replace_groupped_array(list_of_str, ptr_tracker);
}
