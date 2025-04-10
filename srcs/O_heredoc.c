/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   O_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/10 10:23:20 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	modif_in_struct(t_heredoc_manip *heredoc, int y)
{
	free(heredoc->to_modif[y]->filename);
	heredoc->to_modif[y]->filename = ft_strdup(heredoc->tempfiles_names[y]);
	heredoc->to_modif[y]->mode = 2;
}

void	transform_temp_variable(t_heredoc_manip *heredoc, int y)
{
	int		fd;
	char	*buffer;
	char	*result;
	char	*result_final;

	fd = open(heredoc->tempfiles_names[y], O_RDWR);
	buffer = get_next_line(fd);
	if (buffer)
		result = ft_strdup(buffer);
	while (buffer)
	{
		free(buffer);
		buffer = get_next_line(fd);
		if (buffer)
			result = ft_strjoin_2(result, buffer);
	}
	close(fd);
	result_final = variable_manager(result);
	fd = open(heredoc->tempfiles_names[y], O_RDWR | O_TRUNC);
	write(fd, result, ft_strlen(result));
	close(fd);
	free(result);
	free(buffer);
	free(result_final);
}

void	create_temp_files(t_heredoc_manip *heredoc, int nbr_of_heredoc)
{
	int		y;
	char	quote;

	heredoc->fd = ft_calloc(nbr_of_heredoc + 1, sizeof(int));
	heredoc->fd[nbr_of_heredoc] = -1;
	y = 0;
	while (y < nbr_of_heredoc)
	{
		if ((*heredoc->to_modif)->quote_heredoc)
			quote = '\'';
		else 
			quote = '"';
		heredoc->fd[y] = open(heredoc->tempfiles_names[y],
				O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0666);
		write(heredoc->fd[y], &quote, 1);
		write_into_temp(heredoc, y);
		write(heredoc->fd[y], &quote, 1);
		transform_temp_variable(heredoc, y);
		close(heredoc->fd[y]);
		modif_in_struct(heredoc, y);
		y++;
	}
}

void	free_heredoc(t_heredoc_manip *heredoc, int nbr_of_heredoc)
{
	int	i;

	i = 0;
	while (i < nbr_of_heredoc)
	{
		free(heredoc->EOFtext[i]);
		free(heredoc->tempfiles_names[i]);
		i++;
	}
	free(heredoc->EOFtext);
	free(heredoc->tempfiles_names);
	free(heredoc->to_modif);
	free(heredoc->fd);
}

//TODO quit writing if ctrl +d
int	create_heredoc_files(int nbr_of_heredoc, t_parsed_command *array_of_cmd)
{
	t_heredoc_manip	heredoc;

	if (init_eof_and_to_modif(nbr_of_heredoc, array_of_cmd, &heredoc))
		return (-1);
	names_tempo_files(&heredoc);
	create_temp_files(&heredoc, nbr_of_heredoc);
	free_heredoc(&heredoc, nbr_of_heredoc);
	return (0);
}
