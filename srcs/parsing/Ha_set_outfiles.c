/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ha_set_outfiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholterh <jholterh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 17:00:40 by jholterh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_io_structs(t_parsed_command *cmd)
{
	cmd->input_file = ft_calloc(1, sizeof(t_iofile));
	cmd->output_file = ft_calloc(1, sizeof(t_iofile));
}

static void	allocate_io_arrays(t_iofile **in, t_iofile **out, int count)
{
	*in = ft_calloc(count + 1, sizeof(t_iofile));
	*out = ft_calloc(count + 1, sizeof(t_iofile));
}

static void	handle_redirection_entry(char *entry,
		int flag, t_redir_state *st)
{
	if (flag == 2 || flag == 4)
	{
		st->infiles[st->z].filename = process_redirection_filename(entry);
		st->infiles[st->z].mode = flag;
		if (flag == 4 && (ft_strchr(entry, '\'') || ft_strchr(entry, '"')))
			st->infiles[st->z].quote_heredoc = 1;
		st->z++;
	}
	else if (flag == 1 || flag == 3)
	{
		st->outfiles[st->x].filename = process_redirection_filename(entry);
		st->outfiles[st->x].mode = flag;
		st->x++;
	}
}

static void	process_redirections(char **redir_array, t_iofile *infiles,
	t_iofile *outfiles)
{
	int				y;
	int				flag;
	t_redir_state	state;

	y = 0;
	flag = 0;
	state.infiles = infiles;
	state.outfiles = outfiles;
	state.x = 0;
	state.z = 0;
	while (redir_array[y])
	{
		if (!control_operator(redir_array[y]))
			flag = which_symbole(redir_array[y]);
		else
			handle_redirection_entry(redir_array[y], flag, &state);
		y++;
	}
}

int	set_outfiles(t_parsed_command *grouped_array)
{
	int			i;
	int			file_count;
	t_iofile	*in;
	t_iofile	*out;

	i = 0;
	if (control_redirection_logique(grouped_array))
		return (1);
	while (grouped_array[i].command)
	{
		if (!grouped_array[i].redirection_array
			|| (count_files_names(grouped_array[i].redirection_array)) == 0)
		{
			initialize_io_structs(&grouped_array[i]);
			i++;
			continue ;
		}
		file_count = count_files_names(grouped_array[i].redirection_array);
		allocate_io_arrays(&in, &out, file_count);
		process_redirections(grouped_array[i].redirection_array, in, out);
		grouped_array[i].input_file = in;
		grouped_array[i].output_file = out;
		i++;
	}
	return (0);
}
