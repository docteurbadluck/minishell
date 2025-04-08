/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   K_from_text_to_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 10:22:02 by tdeliot          ###   ########.fr       */
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
