/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oa_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/09 15:00:02 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 //count the number of <<
 // store EOF and position for later modification.
 // create tempfiles names.
 // print " or ' depending on quote heredoc.
 // create a child which read in paralele. 
 //when eof or ctrld D close.
 //print another ' 
 // modify the 
*/
int	alloc_heredoc(int nbr_heredoc, t_heredoc_manip	*heredoc)
{
	heredoc->EOFtext = ft_calloc(nbr_heredoc + 1, sizeof(char *));
	heredoc->to_modif = ft_calloc(nbr_heredoc + 1, sizeof(t_iofile *));
	heredoc->tempfiles_names = ft_calloc(nbr_heredoc + 1, sizeof(t_iofile));
	if (!(*heredoc).EOFtext || !(*heredoc).tempfiles_names
		|| !(*heredoc).to_modif)
	{
		printf("problem alloc\n");
		return (-1);
	}
	return (0);
}

static void	fill_eof_and_to_modif(
	t_parsed_command *array_of_cmd, t_heredoc_manip *heredoc, int *z)
{
	int	i;
	int	y;

	i = 0;
	while (array_of_cmd[i].command)
	{
		y = 0;
		while (array_of_cmd[i].input_file
			&& array_of_cmd[i].input_file[y].filename)
		{
			if (array_of_cmd[i].input_file[y].filename
				&& array_of_cmd[i].input_file[y].mode == 4)
			{
				(*heredoc).EOFtext[*z] = ft_strdup(array_of_cmd[i]
						.input_file[y].filename);
				(*heredoc).to_modif[*z] = &array_of_cmd[i].input_file[y];
				(*z)++;
			}
			y++;
		}
		i++;
	}
}

int	init_eof_and_to_modif(int nbr_heredoc,
	t_parsed_command *array_of_cmd, t_heredoc_manip *heredoc)
{
	int	z;

	if (alloc_heredoc(nbr_heredoc, heredoc))
		return (-1);
	z = 0;
	fill_eof_and_to_modif(array_of_cmd, heredoc, &z);
	return (0);
}

void	names_tempo_files(t_heredoc_manip *heredoc)
{
	int		y;
	char	*number;

	y = 0;
	while ((*heredoc).EOFtext[y])
	{
		number = ft_itoa(y);
		(*heredoc).tempfiles_names[y] = ft_strjoin(number, "temp.txt");
		free(number);
		y++;
	}
}

void	write_into_temp(t_heredoc_manip *heredoc, int y)
{
	char	*result;
	char	*limiter;

	result = NULL;
	limiter = ft_strjoin(heredoc->EOFtext[y], "\n");
	while (1)
	{
		if (result != NULL)
			free(result);
		result = readline(">");
		result = ft_strjoin_2(result, "\n");
		if (ft_strncmp(result, limiter, ft_strlen(limiter) + 1) != 0)
			write (heredoc->fd[y], result, ft_strlen(result));
		else
			break ;
	}
	free(result);
	free(limiter);
}
