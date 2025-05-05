/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_2_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:03:01 by jholterh          #+#    #+#             */
/*   Updated: 2025/04/29 11:05:15 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_files(t_iofile *file)
{
	int	i;

	i = 0;
	while (file[i].filename)
		i++;
	return (i);
}

void	handle_before_input_files(int num_files, t_iofile *file)
{
	int	i;

	i = 0;
	while (i < num_files)
	{
		if (access(file[i].filename, F_OK) != 0)
		{
			exit(1);
		}
		i++;
	}
}

int	execute_command_input(t_parsed_command *command, t_ast_helper *ast_helper)
{
	int	fd_input;
	int	num_input_files;

	fd_input = -1;
	if (command->input_file && command->input_file->filename)
	{
		num_input_files = count_files(command->input_file) - 1;
		handle_before_input_files(num_input_files, command->input_file);
		fd_input = open(command->input_file[num_input_files].filename,
				O_RDONLY);
		if (fd_input == -1)
		{
			if (errno == ENOENT)
        		fprintf(stderr, "File does not exist: %s\n", command->input_file[num_input_files].filename);
    		else if (errno == EACCES)
       			 fprintf(stderr, "Permission denied: %s\n", command->input_file[num_input_files].filename);
   			else
       		 	perror("Error opening input file");
			exit(1);
		}
		// TODO
		dup2(fd_input, STDIN_FILENO);
		close(fd_input);
	}
	else if (command->pipe_in == 1)
	{
		dup2(ast_helper->pipe_fds[ast_helper->pipe_counter - 1][0], 0);
		close(ast_helper->pipe_fds[ast_helper->pipe_counter - 1][0]);
		close(ast_helper->pipe_fds[ast_helper->pipe_counter - 1][1]);
	}
	return (0);
}
