/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Be_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:40:57 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/02 10:44:30 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
