/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Amain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:42:07 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/03 09:47:51 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_parsed_command	*new_array;
	t_ast_node			*tree;

	new_array = NULL;
	tree = from_text_to_tree("ls  *out *out || cat > *.out", &new_array);
	if (!tree)
		return (1);
	print_tree(tree, 0);
	free_tree(tree);
	free_new_array(&new_array);
	return (0);
}
