/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ia_to_polish_reverse_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/06/02 16:30:26 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_associativity(t_parsed_command	*new_array)
{
	int	i;

	i = 0;
	while (new_array[i].command)
	{
		new_array[i].associativity = 0;
		if (new_array[i].logical_operator)
			new_array[i].associativity = LEFT;
		if (new_array[i].logical_operator == 4)
			new_array[i].associativity = RIGHT;
		i++;
	}
}

int	check_priority(t_parsed_command *new_array, int i, t_list *operator_stack)
{
	t_parsed_command	*stack_content;

	if (operator_stack)
		stack_content = operator_stack->content;
	else 
		return (0);
	if (new_array[i].associativity == LEFT)
	{
		if ((new_array[i].logical_operator < stack_content->logical_operator)
			&& stack_content->logical_operator != -1)
			return (1);
		return (0);
	}
	if (new_array[i].associativity == RIGHT)
	{
		if (new_array[i].logical_operator <= stack_content->logical_operator
			&& stack_content->logical_operator != -1)
			return (1);
		return (0);
	}
	return (0);
}

void	send_element(t_list **operator_stack, t_list **output_list)
{
	t_list	*ptr;
	t_list	*temp;

	if (*operator_stack)
	{
		ptr = (*operator_stack)->content;
		ft_lstadd_back(output_list, ft_lstnew(ptr));
		temp = *operator_stack;
		*operator_stack = (*operator_stack)->next;
		free(temp);
	}
}

void	print_list(t_list *output_list)
{
	t_list	*ptr;

	ptr = output_list;
	while (ptr)
	{
		printf("%s, ", ((t_parsed_command *)ptr->content)->command);
		ptr = ptr->next;
	}
}

void	free_list(t_list *output_list)
{
	t_list	*ptr;
	t_list	*temp;

	ptr = output_list;
	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
}

/*
void	print_shunting_yard(t_list *output_list, t_list *operator_stack)
{
	t_parsed_command	*ptr;

	printf(" output list : \n");
	while (output_list)
	{
		ptr = output_list->content;
		printf("%s\n", ptr->command);
		output_list = output_list->next;
	}
	printf(" operator stack : \n");
	while (operator_stack)
	{
		ptr = operator_stack->content;
		printf("%s\n", ptr->command);
		operator_stack = operator_stack->next;
	}
}*/