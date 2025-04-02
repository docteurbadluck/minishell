/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/02 17:44:40 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// error logic should include the case where the EOF is folowed by text and not a comand. 
/*
int	create_heredoc_files(int nbr_of_heredoc, t_parsed_command *array_of_cmd)
{
	int		i;
	int		y;
	char	**EOFtext;
	
	EOFtext = ft_calloc(nbr_of_heredoc + 1, sizeof(char *));
	if (!EOFtext)
	{
		printf("error alocation\n");
		return -1;
	}
	i = 0;
	y = 0;
		 while (array_of_cmd[i].command)
		 {
		//	printf("%s\n", array_of_cmd[i].command);
			if (!ft_strncmp(array_of_cmd[i].command, "<<", 3 ))
			{
				if (array_of_cmd[i + 1].command)
				{
					EOFtext[y] = ft_strdup(array_of_cmd[i + 1].command);
					y++;
				}
			}
			i++; 
		 }
		 y = 0;

		 while (nbr_of_heredoc > 0)
		 {
			nbr_of_heredoc--;
			//char *number;
				//convert y into char *
				//join chqr number and temp.txt
			if (EOFtext[y][0] == '\'' && last_char(EOFtext[y]) == '\'')
			{
				
				//create file whith " at start.
				//getnextline until EOF or signal.
				//write " at the end. 
 			}
			else 
			{
				//create file with ' at start
				//getnextline until EOF or signal.
				//write ' at the end 
			}
		 }

		 y = 0;
		 while (EOFtext[y])
		 {
			printf("%s\n", EOFtext[y]);
			y++;
		 }

		 
		 return 0;
}

int	read_input(void)
{
	char	*input;
	char	*pos;
	t_parsed_command *ptr;
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
			ptr = from_input_to_group(input);
			 if (!ptr)
			 {
				free(input);
				continue;
			 }
			 i = 0;
			 heredoc_counter = 0;
			 while (ptr[i].command)
			 {
				//printf("%s\n", ptr[i].command);
				if (!ft_strncmp(ptr[i].command, "<<", 3 ))
					heredoc_counter++;
				i++; 
			 }
			if (heredoc_counter == 0)
			{
				free_new_array(&ptr);
				//t_ast_node *tree = from_text_to_tree(input, &ptr);
				// exec...
			}
			else
			{
				create_heredoc_files(heredoc_counter, ptr);
				free_new_array(&ptr);

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
	
}*/