/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_2_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:03:01 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/15 15:11:30 by jholterh         ###   ########.fr       */
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

int	handle_input_file(t_parsed_command *command)
{
	int	fd_input;
	int	num_input_files;

	fd_input = -1;
	num_input_files = count_files(command->input_file) - 1;
	handle_before_input_files(num_input_files, command->input_file);
	fd_input = open(command->input_file[num_input_files].filename, O_RDONLY);
	if (fd_input == -1)
	{
		if (errno == ENOENT)
			write(2, "File does not exist\n", 21);
		else if (errno == EACCES)
			write(2, "Permission denied\n", 18);
		else
			perror("Error opening input file");
		exit(1);
	}
	dup2(fd_input, STDIN_FILENO);
	close(fd_input);
	return (0);
}

int	handle_pipe_input(t_ast_helper *ast_helper)
{
	dup2(ast_helper->pipe_fds[ast_helper->pipe_counter - 1][0], 0);
	close(ast_helper->pipe_fds[ast_helper->pipe_counter - 1][0]);
	close(ast_helper->pipe_fds[ast_helper->pipe_counter - 1][1]);
	return (0);
}

int	execute_command_input(t_parsed_command *command, t_ast_helper *ast_helper)
{
	if (command->input_file && command->input_file->filename)
		handle_input_file(command);
	else if (command->pipe_in == 1)
		handle_pipe_input(ast_helper);
	return (0);
}
