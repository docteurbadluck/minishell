/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/15 11:16:54 by tdeliot          ###   ########.fr       */
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


	struct sigaction sa_menu, sa_orig, sa_ign, sa_soft_quit;

	

	sa_menu.sa_handler = &handler_menu;
	sa_menu.sa_flags = SA_RESTART;
	sigemptyset(&sa_menu.sa_mask);
	sigaction(SIGINT, &sa_menu, &sa_orig);
	sigaction(SIGQUIT, &sa_menu, &sa_orig);


	sa_ign.sa_handler = SIG_IGN;
	sa_ign.sa_flags = 0;
	sigemptyset(&sa_ign.sa_mask);
	
	sa_soft_quit.sa_handler = &soft_quit_handler;
	sa_soft_quit.sa_flags = 0;
	sigemptyset(&sa_soft_quit.sa_mask);

	while (1)
	{
		pos = ft_strjoin(getenv("PWD"), "> ");
		input = readline(pos);
		if (!input)
		{
			free(pos);
			printf("exit\n");
			break ;
		}
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
				t_ast_node *tree = from_text_to_tree(input, &ptr);
				// exec...
				//execute
				print_tree(tree, 0);
				//free
				free_new_array(&ptr);
				free_tree(tree);
			}
			else
			{
				sigaction(SIGQUIT, &sa_ign, &sa_menu);
				sigaction(SIGINT, &sa_soft_quit, NULL);
				create_heredoc_files(heredoc_counter, ptr);
				sigaction(SIGINT, &sa_menu, NULL);
				sigaction(SIGQUIT, &sa_menu, NULL);
				if (cancel_heredoc)
				{
					cancel_heredoc = 0;
					printf("go to begining \n");
					free_new_array(&ptr);
					continue;
				}
				tree = from_group_to_tree(&ptr);
				//execute
				print_tree(tree, 0);
				//free
				free_new_array(&ptr);
				free_tree(tree);
				//unlink
			}
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


/*
int	read_input(void)
{

	char	*input;
	char	*pos;
	t_parsed_command *ptr;
	t_ast_node *tree;
	int i;
	int heredoc_counter;


	struct sigaction sa_menu, sa_orig, sa_ign, sa_soft_quit;

	

	sa_menu.sa_handler = &handler_menu;
	sa_menu.sa_flags = SA_RESTART;
	sigemptyset(&sa_menu.sa_mask);
	sigaction(SIGINT, &sa_menu, &sa_orig);
	sigaction(SIGQUIT, &sa_menu, &sa_orig);


	sa_ign.sa_handler = SIG_IGN;
	sa_ign.sa_flags = 0;
	sigemptyset(&sa_ign.sa_mask);
	sa_soft_quit.sa_handler = &soft_quit_handler;	

	while (1)
	{
		pos = ft_strjoin(getenv("PWD"), "> ");
		input = readline(pos);
		if (!input)
		{
			free(pos);
			printf("exit\n");
			break ;
		}
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
				t_ast_node *tree = from_text_to_tree(input, &ptr);
				// exec...
				//execute
				print_tree(tree, 0);
				//free
				free_new_array(&ptr);
				free_tree(tree);
			}
			else
			{
				int status;
				sigaction(SIGINT, &sa_ign, &sa_menu);
				sigaction(SIGQUIT, &sa_ign, &sa_menu);
				int pid =fork();
				if (!pid)
				{
					sigaction(SIGINT, &sa_orig, NULL);
					create_heredoc_files(heredoc_counter, ptr);
					exit(0);
				}
				waitpid(pid, &status, 0);
				sigaction(SIGINT, &sa_menu, NULL);
				sigaction(SIGQUIT, &sa_menu, NULL);
				if (WIFSIGNALED(status))
				{
					printf("go to begining \n");
					free_new_array(&ptr);
					continue;
				}
			
				tree = from_group_to_tree(&ptr);
				//execute
				print_tree(tree, 0);
				//free
				free_new_array(&ptr);
				free_tree(tree);
				//unlink
			}
		}
		free(input);
	}
	rl_clear_history();
	return 0;
}
*/