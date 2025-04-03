/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   G_group_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/03 10:13:49 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//void	set_up_arg(t_parsed_command *array);
void	create_new_array(t_parsed_command *array, t_parsed_command *new);
int	set_up_arg(t_parsed_command *array);

/*
t_parsed_command	*group_up(t_parsed_command **array)
{
	t_parsed_command	*new;
	int					count;

	ifset_up_arg(*array);
	count = count_new_array(*array);
	new = ft_calloc(count + 1, sizeof(t_parsed_command));
	if (!new)
		return (NULL);
	create_new_array(*array, new);
	return (new);
}*/

t_parsed_command	*group_up(t_parsed_command **array)
{
	t_parsed_command	*new;
	int					count;

	if (set_up_arg(*array))
	{
		return NULL;
	}
	count = count_new_array(*array);
	new = ft_calloc(count + 1, sizeof(t_parsed_command));
	if (!new)
		return (NULL);
	create_new_array(*array, new);
	return (new);
}

//fixed we have two array : one for the argument one for the redirection. 
//every redirection are store on the seconde one, the other string are 
//store normally.
// comand is defined at the end, it's a duplication of the first element
// of the arg array.
// free new array has been corrected to free the array also.
/*
void	set_up_arg(t_parsed_command *array)
{
	int	i;
	int	count_arg;
	int	save_pos;

	i = 0;
	while (array[i].text)
	{
		count_arg = 0;
		if (array[i].group_id > 0)
		{
			save_pos = i;
			count_arg = count_arguments_and_move(array, &i);
			if (!count_arg)
				continue ;
			allocate_and_fill_arguments(array, save_pos, count_arg, &i);
		}
		if (array[i].group_id <= 0)
			array[i].command = ft_strdup(array[i].text); 
		if (!array[i].text)
			break ;
		i++;
	}
}*/

int	set_up_arg(t_parsed_command *array)
{
	int	i;
	int	count_arg;
	int	save_pos;

	i = 0;
	while (array[i].text)
	{
		count_arg = 0;
		if (array[i].group_id > 0)
		{
			save_pos = i;
			count_arg = count_arguments_and_move(array, &i);
			if (!count_arg)
				continue ;
			if (allocate_and_fill_arguments(array, save_pos, count_arg, &i))
				return 1;
		}
		if (array[i].group_id <= 0)
			array[i].command = ft_strdup(array[i].text); 
		if (!array[i].text)
			break ;
		i++;
	}
	return 0;
}

void	create_new_array(t_parsed_command *array, t_parsed_command *new)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (array[i].text)
	{
		if (array[i].command)
		{
			new[y] = array[i];
			y++;
		}
		else
		{
			free(array[i].text);
		}
		i++;
	}
	free(array);
}

/*
// then we have (-> command -> null "ls" command ls arg -l -a NULL
int main()
{
	char *temp;
	char *str = " > 123  456  ||  789 >> 111   222  abc ";
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
	
	t_parsed_command *new_array =  group_up(&array); // 

	i = 0;
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
}*/