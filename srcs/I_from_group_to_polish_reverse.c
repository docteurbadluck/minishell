/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   I_from_group_to_polish_reverse.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/27 10:16:42 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_open_parenthesis(t_parsed_command *array, int *i, t_list **stack)
{
	if (array[*i].logical_operator == -1)
	{
		ft_lstadd_front(stack, ft_lstnew((void *)&array[*i]));
		(*i)++;
		return (1);
	}
	return (0);
}

int	process_close_parenthesis(t_parsed_command *new_array, int *i
		, t_list **operator_stack, t_list **output_list)
{
	t_list	*temp;

	if (new_array[*i].logical_operator == -2)
	{
		while (*operator_stack && ((t_parsed_command *)
				((*operator_stack)->content))->logical_operator != -1)
			send_element(operator_stack, output_list);
		if (*operator_stack && ((t_parsed_command *)
				((*operator_stack)->content))->logical_operator == -1)
		{
			temp = *operator_stack;
			*operator_stack = (*operator_stack)->next;
			free(temp);
		}
		(*i)++;
		return (1);
	}
	return (0);
}

int	process_operator(t_parsed_command *new_array, int *i
	, t_list **operator_stack, t_list **output_list)
{
	if (new_array[*i].logical_operator != 0)
	{
		while (*operator_stack
			&& check_priority(new_array, *i, *operator_stack))
		{
			send_element(operator_stack, output_list);
		}
		ft_lstadd_front(operator_stack, ft_lstnew((void *)&new_array[*i]));
		(*i)++;
		return (1);
	}
	return (0);
}

t_list	*from_group_to_polish_reverse(t_parsed_command *new_array)
{
	t_list	*output_list;
	t_list	*operator_stack;
	int		i;

	output_list = NULL;
	operator_stack = NULL;
	i = 0;
	while (new_array[i].command)
	{
		if (process_open_parenthesis(new_array, &i, &operator_stack))
			continue ;
		if (process_close_parenthesis(new_array, &i, &operator_stack,
				&output_list))
			continue ;
		if (process_operator(new_array, &i, &operator_stack, &output_list))
			continue ;
		ft_lstadd_back(&output_list, ft_lstnew((void *)&new_array[i]));
		i++;
	}
	while (operator_stack)
		send_element(&operator_stack, &output_list);
	return (output_list);
}

/*
//redirection < > << >> = 4 | = 3 && = 2 || = 1
int main()
{
	char *str = "(A && B) || (C | (D && E) || (F | G)) && H";
	t_parsed_command	*new_array;
	t_list *output_list;
	t_list *ptr;
	t_list	*temp;
	
	new_array =  from_input_to_group(str);
	if (!new_array)
		return (1);
	output_list = from_group_to_polish_reverse(new_array);

	ptr = output_list;
	while (ptr)
	{
		printf("%s, ", ((t_parsed_command *)ptr->content)->command);
		ptr = ptr->next;
	}
	
	ptr = output_list;
	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
	free_new_array(&new_array);
	return (0);
}
*/