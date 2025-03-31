/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Amain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:42:07 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/31 15:26:26 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(void)
{
	t_parsed_command	*new_array;
	t_ast_node			*tree;

	new_array = NULL;
	tree = from_text_to_tree("( >> E A && B) || (C && D)", &new_array);
	if (!tree)
		return (1);
	// Execution or testing
	//printf("\n%s\n", tree->command->command);
	print_tree(tree, 0);
	
	// we have to keep the both function cause some nodes are not in the tree(parentheses)
	free_tree(tree);
	free_new_array(&new_array);
	return (0);
}
