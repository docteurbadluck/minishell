/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   J_from_polish_to_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/27 12:11:23 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//< > << >> = 4 | = 3 && = 2 || = 1  < = 4 > = 5 << = 6 >> = 7 
void	init_logical_operator(t_list *input_of_s_ast_node)
{
	t_list				*ptr;
	t_parsed_command	*ptr_command;

	ptr = input_of_s_ast_node;
	while (ptr)
	{
		ptr_command = ((t_ast_node *)ptr->content)->command;
		if (ptr_command->logical_operator != 4)
			((t_ast_node *)ptr->content)->logical_operator
				= ptr_command->logical_operator;
		else
		{
			if (!ft_strncmp(ptr_command->command, "<<", 2))
				((t_ast_node *)ptr->content)->logical_operator = 6;
			else if (!ft_strncmp(ptr_command->command, ">>", 2))
				((t_ast_node *)ptr->content)->logical_operator = 7;
			else if (!ft_strncmp(ptr_command->command, "<", 1))
				((t_ast_node *)ptr->content)->logical_operator = 4;
			else if (!ft_strncmp(ptr_command->command, ">", 1))
				((t_ast_node *)ptr->content)->logical_operator = 5;
		}
		ptr = ptr->next;
	}
}

t_list	*transform_parsed_in_ast(t_list *output_list)
{
	t_list		*input_of_s_ast_node;
	t_ast_node	*new;
	t_list		*ptr;

	ptr = output_list;
	input_of_s_ast_node = NULL;
	while (ptr)
	{
		new = ft_calloc(1, sizeof(t_ast_node));
		new->command = ((t_parsed_command *)ptr->content);
		ft_lstadd_back(&input_of_s_ast_node, ft_lstnew(new));
		ptr = ptr->next;
	}
	init_logical_operator(input_of_s_ast_node);
	return (input_of_s_ast_node);
}

void	pop_last(t_list **output_list)
{
	t_list	*prev;
	t_list	*current;

	prev = NULL;
	current = *output_list;
	if (!*output_list || !output_list)
		return ;
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	if (prev)
		prev->next = NULL;
	else 
		*output_list = NULL;
	free(current);
}

void	process_operator_tree(t_ast_node *ptr_ast, t_list **output_stack)
{
	ptr_ast->right = (t_ast_node *)ft_lstlast(*output_stack)->content;
	pop_last(output_stack);
	ptr_ast->left = (t_ast_node *)ft_lstlast(*output_stack)->content;
	pop_last(output_stack);
	ft_lstadd_back(output_stack, ft_lstnew(ptr_ast));
}

t_ast_node	*from_polish_to_tree(t_list *output_list)
{
	t_list		*input_of_s_ast_node;
	t_list		*output_stack;
	t_list		*ptr;
	t_ast_node	*ptr_ast;

	output_stack = NULL;
	input_of_s_ast_node = transform_parsed_in_ast(output_list);
	ptr = input_of_s_ast_node;
	while (ptr)
	{
		ptr_ast = (t_ast_node *)ptr->content;
		if (ptr_ast->logical_operator == 0)
			ft_lstadd_back(&output_stack, ft_lstnew(ptr_ast));
		else 
			process_operator_tree(ptr_ast, &output_stack);
		ptr = ptr->next;
	}
	ptr_ast = (t_ast_node *)output_stack->content;
	free_list(output_stack);
	free_list(input_of_s_ast_node);
	return (ptr_ast);
}

/*
int	main(void)
{
	char				*str;
	t_parsed_command	*new_array;
	t_list				*output_list;
	t_ast_node			*tree;

	str = ft_strdup("(A && B)");
	new_array = from_input_to_group(str);
	if (!new_array)
		return (1);
	output_list = from_group_to_polish_reverse(new_array);
	tree = from_polish_to_tree(output_list);
	free_list(output_list);
	
	printf("\n%s\n", tree->command->command);
	printf("\n%s\n", tree->left->command->command);
	printf("\n%s\n", tree->right->command->command);

	free(tree->left);
	free(tree->right);
	free(tree);
	free_new_array(&new_array);
	free(str);
	return (0);
}*/