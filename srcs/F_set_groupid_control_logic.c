/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   F_set_groupid_control_logic.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/25 16:37:25 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	attribute_groupid(t_parsed_command *array);
int		control_logic(t_parsed_command *array);
int		control_parentheses(t_parsed_command *array);

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
		if (array[i].logical_operator != 0)
		{
			give_value(array, i);
			i++;
		}
		else
		{
			while (array[i].logical_operator == 0 && array[i].text)
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
	char *str = " ( ( abc || def)";
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
	if (set_groupid_control_logic(array)) //echec
	{
		free_array(&array);
		return -1;
	}
	i = 0;
	while (array[i].text)
	{
		printf("text : %s, groupid : %d\n",array[i].text, array[i].group_id);
		i++;
	}
	free_array(&array);
	return 0;
}
*/