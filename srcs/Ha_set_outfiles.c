/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ha_set_outfiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/03 16:55:07 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


//function with all sign with mutlipe of them
int	control_operator(char *redirection)
{
	int y;
	y = 0;
	if (redirection && (!ft_strncmp(redirection, ">", 1) || !ft_strncmp(redirection, "<", 1)))
		return 0;

	return 1;
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
			continue;
		}
		if (grouped_array[i].redirection_array[y])
		{
			while (grouped_array[i].redirection_array[y])
			{
				if (!ft_strncmp("\'\'", grouped_array[i].redirection_array[y], 2) || (!ft_strncmp("\"\"", grouped_array[i].redirection_array[y], 2))) // control "" or '' 
					return 1;
					
				//printf("%s, ", grouped_array[i].redirection_array[y]);
				if (!control_operator(grouped_array[i].redirection_array[y]) && !control_operator(grouped_array[i].redirection_array[y + 1])) // contro > >  two operator in a row.
				{
					return (1);
				}
				y++;
			}
			y--;
			if (!control_operator(grouped_array[i].redirection_array[y]))		// control last one. 
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}


char *process_redirection_filename(const char *input) {
	if (!input || !*input)
		return NULL;

	size_t len = ft_strlen(input);
	if (len < 2 || (input[0] != '\'' && input[0] != '"')) 
		return ft_strdup(input); // No valid enclosing quotes, return as-is

	char quote_type = input[0];

	char *result = ft_substr(input, 1, len -2); // Duplicate without outer quotes
	if (!result)
		return NULL;

	// Check if the other type of quote exists inside char other_quote = '"';
	char other_quote;
	if (quote_type == '"')
	{
		other_quote = '\'';
	}
	else
	{
		other_quote = '"';
	}
	if (ft_strchr(result, other_quote))
	{
		free(result);
		return ft_strdup(input); // Return without change.
	}
	// Check for spaces inside
	if (ft_strchr(result, ' '))
	{
		char *modified = malloc(len + 1); // Adjust space for new quotes
		if (!modified) {
			free(result);
			return NULL;
		}
		sprintf(modified, "'%s'", result); // Wrap in single quotes
		free(result);
		return modified;
	}
	return (result); // Otherwise, return stripped version
}
//ls >'' || ls > "" = error check 
// ls > ' ' = ' ' ls > 'a' = a ls > "a" = a 
//ls > "'a'" = "'a'"
// ls > "a b" = 'a b' && ls > 'a b' = 'a b'



int	which_symbole(char *redirection)
{
	if (!ft_strncmp(">>", redirection,2))
	{
		return 3;
	}
	if (!ft_strncmp("<<", redirection,2))
	{
		return 4;
	}
	if (!ft_strncmp(">", redirection, 1))
	{
		return 1;
	}
	if (!ft_strncmp("<", redirection, 1))
	{
		return 2;
	}
	return 0;
}

int count_files_names(char **redirection_array)
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
	return count;
}

int	set_outfiles(t_parsed_command *grouped_array)
{
	int		i, y, x, z;
	int		flag = 0; // Initialize flag
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
		z = 0; // Reset infile index
		x = 0; // Reset outfile index

		// Ensure redirection_array is not NULL before accessing it
		if (!grouped_array[i].redirection_array)
		{
			grouped_array[i].input_file = ft_calloc(1, sizeof (t_iofile));
			grouped_array[i].output_file = ft_calloc(1, sizeof (t_iofile));
			i++;
			continue;
		}
		// Count number of files to allocate correct size
		int file_count = count_files_names(grouped_array[i].redirection_array);
		if (file_count == 0) // Prevent allocating 0 elements
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
				// Correct redirection logic
				if (flag == 2 || flag == 4) // `<` or `<<` → infile
				{
					infiles[z].filename = process_redirection_filename(grouped_array[i].redirection_array[y]);
					infiles[z].mode = flag;
					z++;
				}
				else if (flag == 1 || flag == 3) // `>` or `>>` → outfile
				{
					outfiles[x].filename = process_redirection_filename(grouped_array[i].redirection_array[y]);
					outfiles[x].mode = flag;
					x++;
				}
			}
			y++;
		}
		// Assign the arrays to the grouped command
		grouped_array[i].input_file = infiles;
		grouped_array[i].output_file = outfiles;
		i++;
	}
	return (0);
}


/*
int	set_outfiles(t_parsed_command *grouped_array)
{
	int		i;
	int		y;
	int		x;
	int		z; 
	int		flag;
	t_iofile	*infiles;
	t_iofile	*outfiles;

	flag = 0;
	infiles = NULL;
	outfiles = NULL;
	if (control_redirection_logique(grouped_array))
	{
		return (1);
	}
	// count array size (without sign)
	// ft_calloc(char * +1); infiles and outfiles.
	
	 //index outfile

	 i = 0;
	 z = 0;	//index infile
	 x = 0;
	while (grouped_array[i].command)
	{
		y = 0;

		if (!grouped_array[i].redirection_array[y])
	{
		infiles = ft_calloc(1, sizeof (t_iofile));
		outfiles = ft_calloc( 1, sizeof (t_iofile));

		grouped_array[i].input_file = infiles;
		grouped_array[i].output_file = outfiles;
		i++;
		continue ;
	}
		if (grouped_array[i].redirection_array[y])
		{
			infiles = ft_calloc(count_files_names(grouped_array[i].redirection_array) + 1, sizeof (t_iofile));
			outfiles = ft_calloc(count_files_names(grouped_array[i].redirection_array) + 1, sizeof (t_iofile));
			while (grouped_array[i].redirection_array[y])
			{
				// flag 
				if (control_operator(grouped_array[i].redirection_array[y])) //if is a word.
				{
					if (flag == 1 || flag == 3)
					{
						infiles[z].filename = process_redirection_filename(grouped_array[i].redirection_array[y]);
						infiles[z].mode = flag;
						z++;
					}
					if (flag == 1 || flag == 4)
					{
						outfiles[x].filename = process_redirection_filename(grouped_array[i].redirection_array[y]);
						outfiles[x].mode = flag;
						x++;
					}
				}
				else 
				{		// > 1 < 2 >> 3 << 4
					flag = which_symbole(grouped_array[i].redirection_array[y]);
					printf( "flag : %d\n ", flag);
				}
				y++;
			}
		}
		grouped_array[i].input_file = infiles;
		grouped_array[i].output_file = outfiles;
		i++;
	}

	printf("\n\n\n");
	return (0);
}
*/


//count infile and outfile


// ls > ' ' = ' ' ls > 'a' = a ls > "a" = a 
//ls > "'a'" = "'a'"
// ls > "a b" = 'a b' && ls > 'a b' = 'a b'
// -> look first char to know what kind of quotation. if no quotation -> exit
//	-> look if you can look the other type of quotation. if yes -> exit 
// -> look if you have internal space if yes replace quotation by ' -> exit
// -> remove quotation.


//attribute and manage append. 

