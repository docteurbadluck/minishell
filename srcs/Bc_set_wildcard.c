/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bc_set_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:40:57 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/01 15:04:35 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


  // TODO GERER LES " "
t_list		*find_wildcars(t_parsed_command	*grouped_array)
{
	t_tracker	*tracker;
	t_list		*list_of_tracker;

	if (grouped_array == NULL)
		return NULL;
	list_of_tracker = NULL;	
	int i = 0;
	int y;
	while (grouped_array[i].command)
	{
		y = 0;

		if (grouped_array[i].arguments)
		{
			while (grouped_array[i].arguments[y])
		{
			if (ft_strchr(grouped_array[i].arguments[y], '*'))
			{
				//printf("%s", grouped_array[i].arguments[y]);
				tracker = ft_calloc(1, sizeof(t_tracker));
				if (!tracker)
					return NULL;
				(*tracker).groupped_array_argument = &grouped_array[i].arguments;
				(*tracker).input = grouped_array[i].arguments[y];
				(*tracker).cp_input = ft_strdup((*tracker).input);
				(*tracker).y = y;
				ft_lstadd_back(&list_of_tracker, ft_lstnew(tracker));
			}
			y++;
		}
	}
		y = 0; 
		if (grouped_array[i].redirection_array)
		{
			while (grouped_array[i].redirection_array[y])
			{
				if (ft_strchr(grouped_array[i].redirection_array[y], '*'))
				{
					tracker = ft_calloc(1, sizeof(t_tracker));
					if (!tracker)
						return NULL;
					(*tracker).input = grouped_array[i].redirection_array[y];
					(*tracker).cp_input = ft_strdup((*tracker).input);
					(*tracker).redirection = 1;
					ft_lstadd_back(&list_of_tracker, ft_lstnew(tracker));
				}
				y++;
			}
		}
		i++;
	}
	return(list_of_tracker);
}

int	set_wildcard(t_parsed_command	*grouped_array)
{
	t_list		*list_of_wildcards;
	t_list		*ptr;
	t_tracker	*ptr_tracker; 
	int 	i = 0;
	char *temp ;
	int flag = 0;

	ptr = NULL;
	list_of_wildcards =  find_wildcars(grouped_array);
	
	if (!list_of_wildcards)
		return (-1);

	ptr = list_of_wildcards;
	while(ptr && !flag)
	{
		ptr_tracker = ptr->content;
		temp = wildcard_manager(ptr_tracker->cp_input);
		if (temp)
		{
			ptr_tracker->list_of_matched_name = ft_split(temp, ' ');
			while (ptr_tracker->list_of_matched_name[i])
				i++;
			if (ptr_tracker->redirection)
			{
				if (i > 1)
				{
					flag = 1;
				}
				else
				{
					free(ptr_tracker->input);
					ptr_tracker->input = ft_strdup(ptr_tracker->list_of_matched_name[0]);
				}
			}
			else 
			{
				modify_arg(ptr_tracker);
			}
		}
		free(temp);
		ptr = ptr->next;
	}
	ft_lstclear(&list_of_wildcards, &free_wildcard_list);
	return flag;
}

/*
int main()
{
	char *str = " cat *.abc && echo * abc def *.out ghi ";
	t_parsed_command	*new_array;
	
	new_array =  from_input_to_group(str);
	if (!new_array)
		return (1);
	if (set_wildcard(new_array))
	{
		printf("error wildcards");
		free_new_array(&new_array);
		return -1;
	}
	free_new_array(&new_array);
	return 0;
}
*/