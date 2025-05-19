/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oa_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/19 09:32:10 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 //count the number of <<
 // store EOF and position for later modification.
 // create tempfiles names.
 // print " or ' depending on quote heredoc.
 //when eof or ctrld D close.
 //print another ' 
 // modify the 
*/
int	alloc_heredoc(int nbr_heredoc, t_heredoc_manip	*heredoc)
{
	heredoc->eoftext = ft_calloc(nbr_heredoc + 1, sizeof(char *));
	heredoc->to_modif = ft_calloc(nbr_heredoc + 1, sizeof(t_iofile *));
	heredoc->tempfiles_names = ft_calloc(nbr_heredoc + 1, sizeof(t_iofile));
	if (!(*heredoc).eoftext || !(*heredoc).tempfiles_names
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
				(*heredoc).eoftext[*z] = ft_strdup(array_of_cmd[i]
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

void	names_tempo_files(t_heredoc_manip *heredoc, char *way_to_tmp)
{
	int		y;
	char	*number;
	char	*file_name;

	y = 0;
	while ((*heredoc).eoftext[y])
	{
		number = ft_itoa(y);
		file_name = ft_strjoin(number, "temp.txt");
		(*heredoc).tempfiles_names[y] = ft_strjoin(way_to_tmp, file_name);
		free(file_name);
		free(number);
		y++;
	}
}

void	write_into_temp(t_heredoc_manip *heredoc, int y)
{
	char	*result;
	char	*limiter;

	result = NULL;
	limiter = ft_strjoin(heredoc->eoftext[y], "\n");
	while (1)
	{
		if (result != NULL)
			free(result);
		write(1, ">", 1);
		result = get_next_line(0);
		if (!result)
		{
			if (g_cancel_heredoc)
				break ;
			printf("\nwarning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strncmp(result, limiter, ft_strlen(limiter) + 1) != 0)
			write (heredoc->fd[y], result, ft_strlen(result));
		else
			break ;
	}
	free(result);
	free(limiter);
}
