/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ha_set_outfiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 11:10:33 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_outfiles(t_parsed_command	*grouped_array)
{
	int		i, y, x, z;
	int		flag = 0;
	t_iofile	*infiles;
	t_iofile	*outfiles;

	infiles = NULL;
	outfiles = NULL;
	if (control_redirection_logique(grouped_array))
		return (1);
	i = 0;
	while (grouped_array[i].command)
	{
		y = 0;
		z = 0;
		x = 0;
		if (!grouped_array[i].redirection_array)
		{
			grouped_array[i].input_file = ft_calloc(1, sizeof (t_iofile));
			grouped_array[i].output_file = ft_calloc(1, sizeof (t_iofile));
			i++;
			continue;
		}
		int file_count = count_files_names(grouped_array[i].redirection_array);
		if (file_count == 0)
		{
			grouped_array[i].input_file = ft_calloc(1, sizeof (t_iofile));
			grouped_array[i].output_file = ft_calloc(1, sizeof (t_iofile));
			i++;
			continue;
		}
		infiles = ft_calloc(file_count + 1, sizeof (t_iofile));
		outfiles = ft_calloc(file_count + 1, sizeof (t_iofile));
		while (grouped_array[i].redirection_array[y])
		{
			if (!control_operator(grouped_array[i].redirection_array[y])) 
			{
				flag = which_symbole(grouped_array[i].redirection_array[y]);
			}
			else 
			{
				
				if (flag == 2 || flag == 4)
				{
					infiles[z].filename = process_redirection_filename(grouped_array[i].redirection_array[y]);
					infiles[z].mode = flag;
					z++;
				}
				else if (flag == 1 || flag == 3)
				{
					outfiles[x].filename = process_redirection_filename(grouped_array[i].redirection_array[y]);
					outfiles[x].mode = flag;
					x++;
				}
			}
			y++;
		}
		grouped_array[i].input_file = infiles;
		grouped_array[i].output_file = outfiles;
		i++;
	}
	return (0);
}
