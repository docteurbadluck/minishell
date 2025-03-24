/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   F_set_groupid_control_logic.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/24 18:10:46 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// attribute group number to each token to create block of command.
                // exemle "(" "ls" "-a" ">" "test.txt" "&&" "cat" "'\pwd'" ")" "||" "echo" "failed"
                //         -1    1    1   0       2      0     3       3   -2    0    4       4
            // check logical operation 
                // check if 0 are at the beginning or at the end.
                //check if two 0s are stuck together.
            // check for () 
                // for the parenthesis, a conter start to 0 and should finish on 0. and if it pass to -1 it break and show an error.
                    // each -1 that it pass -> +1 each -2 -> -1;
                    // if -1 is just before -2 erro
void	attribute_groupid(t_parsed_command *array)
{
	int	i;
	int	compteur;

	i = 0;
	compteur = 1;
	while (array[i].text)
	{
		if (array[i].logical_operator != 0)
		{
			array[i].group_id = 0;
			if (array[i].logical_operator == -1)
				array[i].group_id = -1;
			if (array[i].logical_operator == -2)
				array[i].group_id = -2;
			i++;
		}
		else
		{
			while(array[i].logical_operator == 0 && array[i].text)
			{
				array[i].group_id = compteur;
				i++;
			} 
			compteur++;
		}
	}
}

int	control_logic(t_parsed_command *array)
{
	int	i;
	int y;

	i = 0;
	y = 0;
	while (array[i + 1].text)
		i++;
	while (array[i].group_id == -1 || array[i].group_id == -2)
			i--;
	while (array[y].group_id == -1 || array[y].group_id == -2)
		y++;
	if (array[y].group_id == 0 || array[i].group_id == 0)
	{
		printf("error control logic\n");
		return (-1);
	}
	i = 0;
	while (array[i].text)
	{
		y = i + 1;
		while (array[y].group_id == -1 || array[y].group_id == -2 )
			y++;
		if (array[i].group_id == 0 && array[y].group_id == 0)
		{
			printf("error control logic\n");
			return (-1);
		}
		i++;
	}
	return (0);
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
	}


int main()
{
	char *temp;
	char *str = " ( a > ()() abc def ) ||jhi   )";
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
	attribute_groupid(array);
	printf("control_logic : %d\n", control_logic(array));
	i = 0;

	while (array[i].text)
	{
		printf("text : %s, groupid : %d\n",array[i].text, array[i].group_id);
		i++;
	}
	//free_array(&array);
	return 0;
}

