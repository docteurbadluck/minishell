/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   O_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/05/19 09:25:28 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	modif_in_struct(t_heredoc_manip *heredoc, int y)
{
	free(heredoc->to_modif[y]->filename);
	heredoc->to_modif[y]->filename = ft_strdup(heredoc->tempfiles_names[y]);
	heredoc->to_modif[y]->mode = 2;
}

void	transform_temp_variable(t_heredoc_manip *heredoc
		, int y, t_env_exp *env_exp)
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
	result_final = variable_manager(result, env_exp);
	fd = open(heredoc->tempfiles_names[y], O_RDWR | O_TRUNC);
	write(fd, result_final + 1, ft_strlen(result_final) - 2);
	close(fd);
	free(result);
	free(buffer);
	free(result_final);
}

void	create_temp_files(t_heredoc_manip *heredoc
		, int nbr_of_heredoc, t_env_exp *env_exp)
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
		if (g_cancel_heredoc)
			break ;
		write(heredoc->fd[y], &quote, 1);
		transform_temp_variable(heredoc, y, env_exp);
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
		if (heredoc->eoftext[i])
			free(heredoc->eoftext[i]);
		if (heredoc->tempfiles_names[i])
			free(heredoc->tempfiles_names[i]);
		i++;
	}
	if (heredoc->eoftext)
		free(heredoc->eoftext);
	if (heredoc->tempfiles_names)
		free(heredoc->tempfiles_names);
	if (heredoc->to_modif)
		free(heredoc->to_modif);
	if (heredoc->fd)
		free(heredoc->fd);
}

//TODO quit writing if ctrl +d
int	create_heredoc_files(int nbr_of_heredoc,
			t_parsed_command *array_of_cmd, char *way_to_tmp, t_env_exp *env_exp)
{
	t_heredoc_manip	heredoc;

	if (init_eof_and_to_modif(nbr_of_heredoc, array_of_cmd, &heredoc))
		return (-1);
	names_tempo_files(&heredoc, way_to_tmp);
	create_temp_files(&heredoc, nbr_of_heredoc, env_exp);
	free_heredoc(&heredoc, nbr_of_heredoc);
	return (0);
}
