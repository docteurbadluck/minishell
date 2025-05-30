/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   E_set_logic_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 16:59:16 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		arrow_check(t_parsed_command *array, int y);
int		operator_check(t_parsed_command *array, int y);
void	word_value(t_parsed_command *array, int y);
int		parenthese_check(t_parsed_command *array, int y);

//  declare logic_operator,
//which would be usefull late to create the tree.
int	set_logic_op(t_parsed_command *array)
{
	int	y;

	y = 0;
	while (array[y].text)
	{
		arrow_check(array, y);
		operator_check(array, y);
		parenthese_check(array, y);
		word_value(array, y);
		y++;
	}
	return (0);
}

int	arrow_check(t_parsed_command *array, int y)
{
	if (ft_strchr(array[y].text, '<'))
	{
		if (ft_strncmp(array[y].text, "<", 2) == 0
			|| ft_strncmp(array[y].text, "<<", 3) == 0)
			array[y].logical_operator = 4;
		else 
		{
			return (0);
		}
	}
	if (ft_strchr(array[y].text, '>'))
	{
		if (ft_strncmp(array[y].text, ">", 2) == 0
			|| ft_strncmp(array[y].text, ">>", 3) == 0)
			array[y].logical_operator = 4;
		else 
		{
			return (0);
		}
	}
	return (0);
}

int	parenthese_check(t_parsed_command *array, int y)
{
	if (ft_strchr(array[y].text, '('))
	{
		if (ft_strncmp(array[y].text, "(", 2) == 0)
			array[y].logical_operator = -1;
		else 
		{
			return (0);
		}
	}
	if (ft_strchr(array[y].text, ')'))
	{
		if (ft_strncmp(array[y].text, ")", 2) == 0)
			array[y].logical_operator = -2;
		else 
		{
			return (0);
		}
	}
	return (0);
}

int	operator_check(t_parsed_command *array, int y)
{
	if (ft_strchr(array[y].text, '|'))
	{
		if (ft_strncmp(array[y].text, "|", 2) == 0)
			array[y].logical_operator = 3;
		else if (ft_strncmp(array[y].text, "||", 3) == 0)
			array[y].logical_operator = 1;
		else 
		{
			return (0);
		}
	}
	if (ft_strchr(array[y].text, '&'))
	{
		if (ft_strncmp(array[y].text, "&&", 3) == 0)
			array[y].logical_operator = 2;
		else 
		{
			return (0);
		}
	}
	return (0);
}

void	word_value(t_parsed_command *array, int y)
{
	if ((!ft_strchr(array[y].text, '>'))
		&& (!ft_strchr(array[y].text, '<'))
		&& (!ft_strchr(array[y].text, '|')))
	{
		if ((!ft_strchr(array[y].text, '&'))
			&& (!ft_strchr(array[y].text, ')'))
			&& (!ft_strchr(array[y].text, '(')))
			array[y].logical_operator = 0;
	}
}

/*
int main()
{
	t_parsed_command *ptr;
	int i = 0;
	ptr = tokenise("  && abcd|asd  sdf||sdf > < >> ( )");

	printf("logic control : %d\n\n", typo_control_set_logic_op(ptr));
	i = 0;
	while (ptr[i].text)
	{
		printf("text : %s \nlo :%d\n\n",ptr[i].text, ptr[i].logical_operator);
		i++;
	}
	while (i > 0)
	{
		i--;
		free(ptr[i].text);
	}
	free(ptr);
}
*/