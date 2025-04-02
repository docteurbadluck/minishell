/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bd_set_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:40:57 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/02 17:39:26 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	modify_arg(t_tracker *ptr_tracker)
{
	t_list	*list_of_str;
	t_list	*ptr;
	char	*temp;
	int		i;
	int		z;

	i = 0;
	z = 0;
	list_of_str = NULL;
	while ((*ptr_tracker->groupped_array_argument)[i]
		&& ft_strncmp(ptr_tracker->cp_input
			, (*ptr_tracker->groupped_array_argument)[i]
			, ft_strlen(ptr_tracker->cp_input)))
	{
		temp = ft_strdup((*ptr_tracker->groupped_array_argument)[i]);
		ft_lstadd_back(&list_of_str, ft_lstnew(temp));
		i++;
	}
	while (ptr_tracker->list_of_matched_name[z])
	{
		temp = ft_strdup(ptr_tracker->list_of_matched_name[z]);
		ft_lstadd_back(&list_of_str, ft_lstnew(temp));
		z++;
	}
	i++;
	while ((*ptr_tracker->groupped_array_argument)[i])
	{
		temp = ft_strdup((*ptr_tracker->groupped_array_argument)[i]);
		ft_lstadd_back(&list_of_str, ft_lstnew(temp));
		i++;
	}
	ptr = list_of_str;
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
	while (ptr)
	{
		(*ptr_tracker->groupped_array_argument)[i] 
			= ft_strdup((char *)ptr->content);
		i++;
		ptr = ptr->next;
	}
	ft_lstclear(&list_of_str, &free_str_list);
}
