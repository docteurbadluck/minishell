/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   H_from_input_to_group.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/02 11:17:48 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//modifying for wildcards
char	*developpe_input(char *input)
{
	char	*new;

	new = variable_manager(input);
	if (!new)
	{
		printf("error variable manager");
		return (NULL);
	}
	return (new);
}

t_parsed_command	*from_new_to_group_up(char *developped_input)
{
	t_parsed_command	*array;
	t_parsed_command	*new_array;

	array = tokenise(developped_input);
	free(developped_input);
	if (!array)
		return (NULL);
	set_logic_op(array);
	if (set_groupid_control_logic(array) == -1)
	{
		free_array(&array);
		return (NULL);
	}
	new_array = group_up(&array);
	if (new_array == NULL)
	{
		if (array)
			free_array(&array);
		return (NULL);
	}
	return (new_array);
}

t_parsed_command	*from_input_to_group(char *input)
{
	char				*developped_input;
	t_parsed_command	*grouped_array;

	if (!input || !ft_strlen(input))
		return (NULL);
	developped_input = developpe_input(input);
	if (!developped_input)
		return (NULL);
	grouped_array = from_new_to_group_up(developped_input);
	if (!grouped_array)
		return (NULL);
	set_associativity(grouped_array);
	return (grouped_array);
}
