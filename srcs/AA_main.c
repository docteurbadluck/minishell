/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AA_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:42:07 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/27 12:11:01 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(void)
{
	char				*str;
	t_parsed_command	*new_array;
	t_list				*output_list;
	t_ast_node			*tree;

	str = ft_strdup("(A && B) || (C | (D && E) || (F | G)) && H");
	new_array = from_input_to_group(str);
	if (!new_array)
		return (1);
	output_list = from_group_to_polish_reverse(new_array);
	tree = from_polish_to_tree(output_list);
	free_list(output_list);

	printf("\n%s\n", tree->command->command);
	printf("\n%s\n", tree->left->command->command);
	printf("\n%s\n", tree->right->command->command);
	
	//todo free_tree.
	free_new_array(&new_array);
	free(str);
	return (0);
}
