/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   F_set_groupid_control_logic.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 16:59:18 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	attribute_groupid(t_parsed_command *array);
int		control_logic(t_parsed_command *array);
int		control_parentheses(t_parsed_command *array);

//FIXED  now : < are part of the group id : txt > test3.txt ls  || >  text
										//	 1  1   1        1   0  2   2
// also : > || is not a mistake anymore, > text ls is not a mistake anymore
int	set_groupid_control_logic(t_parsed_command *array)
{
	attribute_groupid(array);
	if (control_logic(array) || control_parentheses(array))
		return (-1);
	return (0);
}

void	attribute_groupid(t_parsed_command *array)
{
	int	i;
	int	compteur;

	i = 0;
	compteur = 1;
	while (array[i].text)
	{
		if ((array[i].logical_operator == 0 || array[i].logical_operator == 4))
		{
			while ((array[i].logical_operator == 0
					|| array[i].logical_operator == 4) && array[i].text)
			{
				array[i].group_id = compteur;
				i++;
			}
			compteur++;
		}
		else 
		{
			give_value(array, i);
			i++;
		}
	}
}

int	control_logic(t_parsed_command *array)
{
	int	i;
	int	y;

	if (control_border_logic(array))
		return (-1);
	i = 0;
	while (array[i].text)
	{
		y = i + 1;
		while (array[y].group_id == -1 || array[y].group_id == -2)
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

int	control_parentheses(t_parsed_command *array)
{
	int	compteur;
	int	i;

	i = 0;
	compteur = 0;
	while (array[i].text)
	{
		if (array[i].group_id == -2)
		{
			compteur--;
			if (compteur < 0)
			{
				printf("errror control parentheses");
				return (-1);
			}
		}
		if (array[i].group_id == -1)
			compteur++;
		i++;
	}
	if (compteur == 0)
		return (0);
	printf("errror control parentheses");
	return (-1);
}

/*
int main()
{
	char *temp;
	char *str = "( abc > text.txt > test2. txt > test3.txt l
	s  || && >  text4.txt def) ";
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
	if (set_logic_op(array) == 1) //echec
	{
		free_array(&array);
		return (1);
	}
	if (set_groupid_control_logic(array)) //echec
	{
		free_array(&array);
		return -1;
	}
	i = 0;
	while (array[i].text)
	{
		printf("text : %s, groupid : %d logical : %d\n",array[i].t
		ext, array[i].group_id, array[i].logical_operator);
		i++;
	}
	free_array(&array);
	return 0;
}
*/