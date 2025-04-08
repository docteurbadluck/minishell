/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ha_set_outfiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/08 10:43:12 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//function with all sign with mutlipe of them
int	control_operator(char *redirection)
{
	int	y;

	y = 0;
	if (redirection && (!ft_strncmp(redirection, ">", 1)
			|| !ft_strncmp(redirection, "<", 1)))
		return (0);
	return (1);
}

int	control_redirection_logique(t_parsed_command *grouped_array)
{
	int	i;
	int	y;

	i = 0;
	while (grouped_array[i].command)
	{
		y = 0;
		if (grouped_array[i].logical_operator != 0)
		{
			i++;
			continue ;
		}
		if (grouped_array[i].redirection_array[y])
		{
			while (grouped_array[i].redirection_array[y])
			{
				if (!ft_strncmp("\'\'", grouped_array[i].redirection_array[y], 2) || (!ft_strncmp("\"\"", grouped_array[i].redirection_array[y], 2)))
					return (1);
				if (!control_operator(grouped_array[i].redirection_array[y]) && !control_operator(grouped_array[i].redirection_array[y + 1]))
					return (1);
				y++;
			}
			y--;
			if (!control_operator(grouped_array[i].redirection_array[y]))
				return (1);
		}
		i++;
	}
	return (0);
}

char	*process_redirection_filename(const char *input)
{
	if (!input || !*input)
		return (NULL);
	size_t len = ft_strlen(input);
	if (len < 2 || (input[0] != '\'' && input[0] != '"')) 
		return ft_strdup(input);
	char quote_type = input[0];
	char *result = ft_substr(input, 1, len -2);
	if (!result)
		return (NULL);
	char other_quote;
	if (quote_type == '"')
		other_quote = '\'';
	else
		other_quote = '"';
	if (ft_strchr(result, other_quote))
	{
		free(result);
		return ft_strdup(input);
	}
	if (ft_strchr(result, ' '))
	{
		char *modified = malloc(len + 1);
		if (!modified) {
			free(result);
			return (NULL);
		}
		sprintf(modified, "'%s'", result);
		free(result);
		return (modified);
	}
	return (result);
}

int	which_symbole(char *redirection)
{
	if (!ft_strncmp(">>", redirection,2))
	{
		return (3);
	}
	if (!ft_strncmp("<<", redirection, 2))
	{
		return (4);
	}
	if (!ft_strncmp(">", redirection, 1))
	{
		return (1);
	}
	if (!ft_strncmp("<", redirection, 1))
	{
		return (2);
	}
	return (0);
}

int	count_files_names(char	**redirection_array)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (redirection_array[i])
	{
		if (which_symbole(redirection_array[i]))
			count++;
		i++;
	}
	return (count);
}

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
