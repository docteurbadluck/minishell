/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   L_print_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 11:07:49 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_indentation(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

void	print_arguments(char **arguments)
{
	int	y;

	y = 0;
	if (arguments)
	{
		printf(" arg : ");
		while (arguments[y])
		{
			printf(" %s ", arguments[y]);
			y++;
		}
	}
}

void	print_redirections(char **redirection_array)
{
	int	z;

	z = 0;
	if (redirection_array)
	{
		printf(" redir : ");
		while (redirection_array[z])
		{
			printf(" .%s. ", redirection_array[z]);
			z++;
		}
	}
}

void	print_iofiles(t_parsed_command *command)
{
	int	i;

	i = 0;
	if (command->input_file[0].filename)
		printf("input files  : ");
	while (command->input_file[i].filename)
	{
		printf("%s ", command->input_file[i].filename);
		i++;
	}
	if (command->output_file[0].filename)
		printf("output files  : ");
	i = 0;
	while (command->output_file[i].filename)
	{
		printf("%s ", command->output_file[i].filename);
		i++;
	}
}

void	print_tree(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	print_indentation(depth);
	printf("%s", node->command->command);
	print_arguments(node->command->arguments);
	print_indentation(depth);
	print_iofiles(node->command);
	printf("\n");
	print_tree(node->left, depth + 1);
	print_tree(node->right, depth + 1);
}
