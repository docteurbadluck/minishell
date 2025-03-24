/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AA_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:42:07 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/24 17:47:24 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
int main()
{
	char *temp;
	char *str = " *.out";
	char *new;
	t_parsed_command *array;
	int i;
	
	new = variable_manager(str);
	temp = new;
	new =wildcard_manager(new);
	free(temp);
	if (!new) //only if it's totally empty
	{
		printf("error wildcard_manager");
		exit(1);
	}
	array = tokenise(new);
	free(new);
	if (!array) //echec
		exit(1);
	if (typo_control_set_logic_op(array) == 1) //echec
	{
		free_array(&array);
		return (1);
	}

	
	free_array(&array);
	return 0;
}

void free_array(t_parsed_command **array)
{
	int i = 0;
		while ((*array)[i].text)
		{
			free((*array)[i].text);
			i++;
		}
		free(*array);
		
	}*/