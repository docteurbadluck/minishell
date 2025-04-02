/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bd_set_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:40:57 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/02 14:57:31 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
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
*/



/*
void free_wildcard_list(void *content)
{
	t_tracker *ptr;
	int	i = 0;

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

	// copy l'integralite du tableau. 
	// le met dans une list
	// cherche le premier * 
	// met dans la list le tableau de match words.
	//met la find du tableau dans la list. 
	//compte le nombre de node.
	//cree un tableau de la bonne taille et initialise le.
	//free le tableau de basse, et link le nouveau tableau.
	//free (la list)

void free_str_list (void *content)
{
	free(content);
}
*/
/*
void modify_arg(t_tracker *ptr_tracker)
{
	t_list	*list_of_str;
	t_list	*ptr;
	char	*temp;
	int		i = 0;
	int		z = 0;

	list_of_str = NULL;
	
	while ((*ptr_tracker->groupped_array_argument)[i] && i < ptr_tracker->y) // copy everything in the list until the wildcard
	{
		temp = ft_strdup((*ptr_tracker->groupped_array_argument)[i]);
		ft_lstadd_back(&list_of_str, ft_lstnew(temp));
		i++;
	}
	while (ptr_tracker->list_of_matched_name[z]) // copy the array of matching name
	{
		temp = ft_strdup(ptr_tracker->list_of_matched_name[z]);
		ft_lstadd_back(&list_of_str, ft_lstnew(temp));
		z++;
	}
	i++; //pass the * 
	while ((*ptr_tracker->groupped_array_argument)[i]) // copy the rest of the list. 
	{
		temp = ft_strdup((*ptr_tracker->groupped_array_argument)[i]);
		ft_lstadd_back(&list_of_str, ft_lstnew(temp));
		i++;
	}

	ptr = list_of_str;
	while (ptr)
	{
		printf("%s ", (char *)ptr->content);
		ptr = ptr->next;
	}
		ft_lstclear(&list_of_str, &free_str_list);
}
*/
void	modify_arg(t_tracker *ptr_tracker)
{
	t_list	*list_of_str;
	t_list	*ptr;
	char	*temp;
	int		i = 0;
	int		z = 0;

	list_of_str = NULL;
	
	while ((*ptr_tracker->groupped_array_argument)[i] && ft_strncmp(ptr_tracker->cp_input, (*ptr_tracker->groupped_array_argument)[i], ft_strlen(ptr_tracker->cp_input))) // copy everything in the list until the wildcard
	{
		temp = ft_strdup((*ptr_tracker->groupped_array_argument)[i]);
		ft_lstadd_back(&list_of_str, ft_lstnew(temp));
		i++;
	}
	while (ptr_tracker->list_of_matched_name[z]) // copy the array of matching name
	{
		temp = ft_strdup(ptr_tracker->list_of_matched_name[z]);
		ft_lstadd_back(&list_of_str, ft_lstnew(temp));
		z++;
	}
	i++; //pass the * 
	while ((*ptr_tracker->groupped_array_argument)[i]) // copy the rest of the list. 
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
	*ptr_tracker->groupped_array_argument = ft_calloc(ft_lstsize(list_of_str) + 1, sizeof(char *));
	i = 0; 
	while (ptr)
	{
		(*ptr_tracker->groupped_array_argument)[i] = ft_strdup((char *)ptr->content);
		i++;
		ptr = ptr->next;
	}
		ft_lstclear(&list_of_str, &free_str_list);
}