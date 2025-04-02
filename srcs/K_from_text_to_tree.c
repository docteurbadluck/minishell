/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   K_from_text_to_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/02 16:14:37 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast_node	*from_text_to_tree(char *str, t_parsed_command **new_array)
{
	t_list		*output_list;
	t_ast_node	*tree;
	
	*new_array = NULL;
	*new_array = from_input_to_group(str);
	
	if (!*new_array)
		return (NULL);
		/*
	if (set_wildcard(*new_array))
	{
		printf("error wildcards");
		free_new_array(new_array);
		return (NULL);
	}

	int i = 0;	
	int y = 0;
	while ((*new_array)[i].command)
	{
		printf("%s", (*new_array)[i].command);
		if ((*new_array)[i].arguments)
		{
			printf(" arg : ");
			while ((*new_array)[i].arguments[y])
			{
				printf("%s ", (*new_array)[i].arguments[y]);
				y++;
			}
		}
		i++;
	}
*/
	
	output_list = from_group_to_polish_reverse(*new_array);
	tree = from_polish_to_tree(output_list);
	free_list(output_list);
	return (tree);
}

void	free_tree(t_ast_node *node)
{
	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	free(node);
}

void	print_tree(t_ast_node *node, int depth)
{
	int	i;
	int	y;
	int z;

	z = 0;
	y = 0;
	i = 0;
	if (!node)
		return ;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	printf("%s", node->command->command);
	if (node->command->arguments)
		{
			printf(" arg : ");

			while (node->command->arguments[y])
			{
				printf(" %s ", node->command->arguments[y]);
				y++;
			}
		}
		if (node->command->redirection_array)
		{
			printf("redir : ");
			while (node->command->redirection_array[z])
			{
				printf(" %s ", node->command->redirection_array[z]);
				z++;
			}
		}
		printf("\n");

		printf("\n");

	print_tree(node->left, depth + 1);
	print_tree(node->right, depth + 1);
}
