/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_3_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:05:06 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/13 16:01:54 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_before_output_files(int num_files, t_iofile *file)
{
	int	i;
	int	fd;

	i = 0;
	while (i < num_files)
	{
		fd = open(file[i].filename, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
		{
			perror("Error creating file\n");
			exit(1);
		}
		close(fd);
		i++;
	}
}

void	handle_output_file(t_parsed_command *command)
{
	int		flag;
	int		fd_output;
	int		num_output_files;

	fd_output = -1;
	num_output_files = count_files(command->output_file) - 1;
	handle_before_output_files(num_output_files, command->output_file);
	if (command->output_file[num_output_files].mode == 3)
		flag = O_WRONLY | O_CREAT | O_APPEND;
	else
		flag = O_WRONLY | O_CREAT | O_TRUNC;
	fd_output = open(command->output_file[num_output_files].filename,
			flag, 0644);
	if (fd_output == -1)
	{
		perror("open output file");
		exit(1);
	}
	dup2(fd_output, STDOUT_FILENO);
	close(fd_output);
}

int	execute_command_output(t_parsed_command *command, t_ast_helper *ast_helper)
{
	if (command->output_file && command->output_file->filename)
		handle_output_file(command);
	else if (command->pipe_out == 1)
	{
		dup2(ast_helper->pipe_fds[ast_helper->pipe_counter][1], STDOUT_FILENO);
		close(ast_helper->pipe_fds[ast_helper->pipe_counter][0]);
		close(ast_helper->pipe_fds[ast_helper->pipe_counter][1]);
	}
	return (0);
}
