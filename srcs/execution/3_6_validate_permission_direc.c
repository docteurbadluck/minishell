/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_6_validate_permission_direc.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:10:12 by jholterh          #+#    #+#             */
/*   Updated: 2025/05/15 15:09:26 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_path_error(int error_code)
{
	if (error_code == EACCES)
	{
		write(2, "Permission denied\n", 18);
		exit(126);
	}
	else if (error_code == ENOENT)
	{
		write(2, "No such file or directory\n", 26);
		exit(127);
	}
	else
	{
		perror("Error opening file");
		exit(126);
	}
}

void	check_executable(const char *path)
{
	if (access(path, X_OK) != 0)
	{
		if (errno == EACCES)
		{
			write(2, "Permission denied\n", 18);
			exit(126);
		}
		write(2, "Path is not executable\n", 24);
		exit(126);
	}
}

void	check_directory(const char *path)
{
	DIR	*dir;

	if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
	{
		dir = opendir(path);
		if (dir != NULL)
		{
			closedir(dir);
			write(2, "Path is a directory\n", 20);
			exit(126);
		}
	}
}

void	check_path(const char *path)
{
	int	fd;

	if (path == NULL)
	{
		write(2, "Command not found\n", 19);
		exit(127);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		handle_path_error(errno);
	close(fd);
	check_executable(path);
	check_directory(path);
}

void	validate_permissions_and_directory(const char *path)
{
	DIR	*dir;

	if (access(path, X_OK) != 0)
	{
		if (errno == EACCES)
		{
			write(2, "Permission denied\n", 18);
			exit(126);
		}
		write(2, "Path is not executable\n", 24);
		exit(126);
	}
	if (access(path, F_OK) == 0)
	{
		dir = opendir(path);
		if (dir != NULL)
		{
			closedir(dir);
			write(2, "Path is a directory\n", 20);
			exit(126);
		}
	}
}
