/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   P_name_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/06/02 16:16:39 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*path_to_tmp(char *argv0)
{
	char	*temp;
	char	cwd[10000];
	char	*last_slash;

	if (argv0[0] == '/')
	{
		temp = ft_strdup(argv0);
	}
	else
	{
		if (!getcwd(cwd, sizeof(cwd)))
			return (NULL);
		temp = ft_strjoin(cwd, "/");
		temp = ft_strjoin_2(temp, argv0);
	}
	last_slash = ft_strrchr(temp, '/');
	if (last_slash)
	{
		last_slash++;
		*last_slash = '\0';
	}
	temp = ft_strjoin_2(temp, "tmp");
	temp = ft_strjoin_2(temp, "/");
	return (temp);
}

void	unlink_tempo_files(char *way_to_tmp)
{
	int		y;
	char	*number;
	char	*file_name;
	char	*tmp;

	y = 0;
	while (1)
	{
		number = ft_itoa(y);
		file_name = ft_strjoin(number, "temp.txt");
		tmp = ft_strjoin(way_to_tmp, file_name);
		if (access(tmp, F_OK) == 0)
			unlink(tmp);
		else
		{
			free(tmp);
			free(file_name);
			free(number);
			break ;
		}
		free(tmp);
		free(file_name);
		free(number);
		y++;
	}
}

void	heredoc_dollar(t_parsed_command *command, t_env_exp *env_exp)
{
	int	i;

	i = 0;
	(void)env_exp;
	while (command->input_file[i].filename)
	{
		if (command->input_file[i].mode == 4)
		{
			transform_heredoc_variable(command->input_file[i].filename,
				env_exp);
		}
		i++;
	}
}

/*
int main(int argc, char **argv)
{

	(void)argc;
	char *name = name_and_path_generator(argv[0], "tmp", "0temp.txt");
	printf("%s\n", name);
	free(name);
	return 0;
}*/