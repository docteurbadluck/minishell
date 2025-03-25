/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AA_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:42:07 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/25 16:37:34 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
int main()
{
	char *temp;
	char *str = "\"a bcd<  abc > bcd \"";
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
	set_logic_op(array);
	if (set_groupid_control_logic(array) == -1) //echec
	{
		free_array(&array);
		return -1;
	}

	t_parsed_command *new_array =  group_up(&array);
	if (new_array == NULL) // alloc fail .
	{
		if (array)
			free_array(&array);
	}
	i = 0;
	int y;
	while (new_array[i].text)
	{	
		 y = 0;
		if (new_array[i].command)
		{
			printf("command : %s\n", new_array[i].command);
			if (new_array[i].arguments)
			{				
				printf("arg : ");

				while (new_array[i].arguments[y])
				{
					printf("'%s' ", new_array[i].arguments[y]);
					y++;
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