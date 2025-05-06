/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   H_from_input_to_group.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/06 14:03:00 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	developped_input = ft_strdup(input);
	grouped_array = from_new_to_group_up(developped_input);
	if (!grouped_array)
		return (NULL);
	set_associativity(grouped_array);
	if (set_wildcard(grouped_array))
	{
		printf("error wildcards");
		free_new_array(&grouped_array);
		return (NULL);
	}
	if (set_outfiles(grouped_array))
	{
		printf("error redirection");
		free_new_array(&grouped_array);
		return (NULL);
	}
	return (grouped_array);
}
