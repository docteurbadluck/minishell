/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/10 10:15:59 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	read_input(void)
{
	char	*input;
	char	*pos;
	t_parsed_command *ptr;
	t_ast_node *tree;
	int i;
	int heredoc_counter;

	while (1)
	{
		pos = ft_strjoin(getenv("PWD"), "> ");
		input = readline(pos);

		if (ft_strlen(input))
		{
			add_history(input);
		}
		free(pos);

		if (!ft_strncmp("exit", input, 5))
		{
			free(input);
			break;
		}
		if (ft_strlen(input))
		{
			ptr = from_input_to_group(input); // verify that the input is valid
			 if (!ptr)
			 {
				free(input);
				continue;
			 }
			 printf("%s\n", input);
			 int y = 0;
			 heredoc_counter = 0;
			 i = 0;
			 while (ptr[i].command) //count the number of <<
			 {
				y =0;
				while (ptr[i].input_file && ptr[i].input_file[y].filename)
				{	
					if (ptr[i].input_file[y].mode == 4)
						heredoc_counter++;
					y++;
				}
				i++; 
			 }
			if (heredoc_counter == 0) // if no << find execut
			{
				printf("0 heredoc\n");
				free_new_array(&ptr);
				//t_ast_node *tree = from_text_to_tree(input, &ptr);
				// exec...
			}
			else
			{
				create_heredoc_files(heredoc_counter, ptr);
				tree = from_group_to_tree(&ptr);
				//execute
				print_tree(tree, 0);
				free_new_array(&ptr);
				free_tree(tree);
			}
				//free ptr
				// count how many <<
				// create temporary file temp, .txt if 'EOF' '...' else "..."
				// readline until EOF or SIGNAL
				// transform the string : 
				// transform << into < temp1.txt   \\ later unlink the temporary file.
		}
		free(input);
	}
	rl_clear_history();
	return 0;
}

int main()
{
	read_input();
	return 0;
	
}
