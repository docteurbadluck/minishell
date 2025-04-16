/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   P_name_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/16 09:44:26 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*name_and_path_generator(char *argv0, char *directory, char *file_name)
{
	char	*temp;
	int		i;
	int		counter;

	counter = 0;
	i = ft_strlen(argv0);
	while (i > 0)
	{
		if (argv0[i] == '/')
		{
			counter++; 
			if (counter == 2)
			{
				i++;
				break ;
			}
		}
		i--;
	}
	temp = ft_substr(argv0, 0, i);
	temp = ft_strjoin_2(temp, directory);
	temp = ft_strjoin_2(temp, "/");
	temp = ft_strjoin_2(temp, file_name);
	return (temp);
}

void	unlink_tempo_files(char *argv0)
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
		tmp = name_and_path_generator(argv0, "tmp", file_name);
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

/*
int main(int argc, char **argv)
{

	(void)argc;
	char *name = name_and_path_generator(argv[0], "tmp", "0temp.txt");
	printf("%s\n", name);
	free(name);
	return 0;
}*/