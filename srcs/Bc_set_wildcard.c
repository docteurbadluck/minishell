/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bc_set_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:40:57 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/02 11:29:08 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_wildcard_in_redirection(t_parsed_command *grouped_array,
			int i, t_list **list_of_tracker);
void	find_wildcard_in_arg(t_parsed_command *grouped_array, int i,
			t_list **list_of_tracker);

t_list	*find_wildcars(t_parsed_command	*grouped_array)
{
	t_list		*list_of_tracker;
	int			i;

	if (grouped_array == NULL)
		return (NULL);
	list_of_tracker = NULL;
	i = 0;
	while (grouped_array[i].command)
	{
		find_wildcard_in_arg(grouped_array, i, &list_of_tracker);
		find_wildcard_in_redirection(grouped_array, i, &list_of_tracker);
		i++;
	}
	return (list_of_tracker);
}

void	find_wildcard_in_arg(t_parsed_command *grouped_array,
			int i, t_list **list_of_tracker)
{
	int			y;
	t_tracker	*tracker;

	y = -1;
	if (grouped_array[i].arguments)
	{
		while (grouped_array[i].arguments[++y])
		{
			if (ft_strchr(grouped_array[i].arguments[y], '*')
				&& grouped_array[i].arguments[y][0] != '"'
				&& grouped_array[i].arguments[y][0] != '\'' )
			{
				tracker = ft_calloc(1, sizeof(t_tracker));
				if (!tracker)
					return ;
				(*tracker).groupped_array_argument
					= &grouped_array[i].arguments;
				(*tracker).input = &grouped_array[i].arguments[y];
				(*tracker).cp_input = ft_strdup(*(*tracker).input);
				(*tracker).y = y;
				(*tracker).i = i;
				ft_lstadd_back(list_of_tracker, ft_lstnew(tracker));
			}
		}
	}
}

void	find_wildcard_in_redirection(t_parsed_command *grouped_array,
		int i, t_list **list_of_tracker)
{
	int			y;
	t_tracker	*tracker;

	y = 0;
	if (grouped_array[i].redirection_array)
	{
		while (grouped_array[i].redirection_array[y])
		{
			if (ft_strchr(grouped_array[i].redirection_array[y], '*')
				&& grouped_array[i].arguments[y][0] != '"'
				&& grouped_array[i].arguments[y][0] != '\'')
			{
				tracker = ft_calloc(1, sizeof(t_tracker));
				if (!tracker)
					return ;
				(*tracker).input = &grouped_array[i].redirection_array[y];
				(*tracker).cp_input = ft_strdup(*(*tracker).input);
				(*tracker).redirection = 1;
				ft_lstadd_back(list_of_tracker, ft_lstnew(tracker));
			}
			y++;
		}
	}
}

// without wildcard no problem 
// if * has no return let it the same, good for arg and for redirection.
// redirection : if too much answer perfect. 
// redirection with 1 is correct. " ls > *.out > *2.* " wore also
// redirection with several wildcards work.
int	process_wildcard(t_tracker *ptr_tracker, int *flag)
{
	char	*temp;
	int		i;

	i = 0;
	temp = wildcard_manager(ptr_tracker->cp_input);
	if (!temp)
		return (0);
	ptr_tracker->list_of_matched_name = ft_split(temp, ' ');
	while (ptr_tracker->list_of_matched_name[i])
		i++;
	if (ptr_tracker->redirection)
	{
		if (i > 1)
			*flag = 1;
		else
		{
			free(*ptr_tracker->input);
			*ptr_tracker->input
				= ft_strdup(ptr_tracker->list_of_matched_name[0]);
		}
	}
	else
		modify_arg(ptr_tracker);
	free(temp);
	return (0);
}

int	set_wildcard(t_parsed_command *grouped_array)
{
	t_list		*list_of_wildcards;
	t_list		*ptr;
	t_tracker	*ptr_tracker;
	int			flag;

	flag = 0;
	list_of_wildcards = find_wildcars(grouped_array);
	if (!list_of_wildcards)
		return (-1);
	ptr = list_of_wildcards;
	while (ptr && !flag)
	{
		ptr_tracker = ptr->content;
		process_wildcard(ptr_tracker, &flag);
		ptr = ptr->next;
	}
	ft_lstclear(&list_of_wildcards, &free_wildcard_list);
	return (flag);
}

/*
int main()
{
	char *str = " ls  a.* a.*  > a.* || ls " ;
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
	
	int i = 0;
	int y;
	int z;
	while (new_array[i].text)
	{	
		z = 0;
		 y = 0;
		if (new_array[i].command)
		{
			printf(" command : %s\n", new_array[i].command);
			if (new_array[i].arguments)
			{				
				printf("arg : ");

				while (new_array[i].arguments[y])
				{
					printf("'%s' ", new_array[i].arguments[y]);
					y++;
				}
			}
			printf("\n");
			if (new_array[i].redirection_array)
			{
				printf (" redirection array : ");
				while (new_array[i].redirection_array[z])
				{
					printf("'%s' ", new_array[i].redirection_array[z]);
					z++;
				}
				printf("\n");
			}
		}
		i++;
	}
	
	free_new_array(&new_array);
	return 0;
}
*/