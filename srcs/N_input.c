/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/09 13:12:38 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   N_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docteurbadluck <docteurbadluck@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/06 18:43:07 by docteurbadl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

 //count the number of <<
 // store EOF and position for later modification.
 // create tempfiles names.
 // print " or ' depending on quote heredoc.
 // create a child which read in paralele. 
 //when eof or ctrld D close.
 //print another ' 
 // modify the 

int	init_eof_and_to_modif(int nbr_of_heredoc, t_parsed_command *array_of_cmd, t_heredoc_manip	*heredoc)
{
	int	y;
	int	i;
	int	z;

	heredoc->EOFtext = ft_calloc(nbr_of_heredoc + 1, sizeof(char *));
	heredoc->to_modif = ft_calloc(nbr_of_heredoc + 1, sizeof(t_iofile *));
	heredoc->tempfiles_names = ft_calloc(nbr_of_heredoc + 1, sizeof(t_iofile));
	if (!(*heredoc).EOFtext || !(*heredoc).tempfiles_names || !(*heredoc).to_modif)
	{
		 printf("error alocation\n");
		 return -1;
	 }
	 i = 0;
	 z = 0;
	 while (array_of_cmd[i].command)
	{
		y = 0;
		while (array_of_cmd[i].input_file && array_of_cmd[i].input_file[y].filename)
		{
			if (array_of_cmd[i].input_file[y].filename && array_of_cmd[i].input_file[y].mode == 4 )
			{
				(*heredoc).EOFtext[z] = ft_strdup(array_of_cmd[i].input_file[y].filename);
				(*heredoc).to_modif[z] = &array_of_cmd[i].input_file[y];
				 z++;
			}
			y++;
		}
		i++; 
	}
	return 0;
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
	result =readline(">");
	result = ft_strjoin_2(result, "\n");
	if (ft_strncmp(result, limiter, ft_strlen(limiter) + 1) != 0)
		write (heredoc->fd[y], result, ft_strlen(result));
	else
		break ;
}
free(result);
free(limiter);
}

void	modif_in_struct(t_heredoc_manip *heredoc, int y)
{
	if ((*heredoc->to_modif)[y].filename)
		free ((*heredoc->to_modif)[y].filename);
	(*heredoc->to_modif)[y].filename = heredoc->tempfiles_names[y];
	(*heredoc->to_modif)[y].mode = 3;
}

void transform_temp_variable(t_heredoc_manip *heredoc, int y)
{
	int fd;
	char	*buffer;
	char	*result;
	
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
	result = variable_manager(result);
	printf("result : %s", result);
}

void	create_temp_files(t_heredoc_manip *heredoc, int nbr_of_heredoc)
{
	int	y;
	char quote;

	heredoc->fd = ft_calloc(nbr_of_heredoc + 1, sizeof(int));
	heredoc->fd[nbr_of_heredoc] = -1;
	y = 0;
	while (heredoc->fd[y] > -1)
	{
		if ((*heredoc->to_modif)->quote_heredoc)
			quote = '\'';
		else 
			quote = '"';
		heredoc->fd[y] = open(heredoc->tempfiles_names[y], O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0666 );
		write(heredoc->fd[y], &quote, 1);
		write_into_temp(heredoc, y);
		write(heredoc->fd[y], &quote, 1);
		transform_temp_variable(heredoc, y);
		// variable
		modif_in_struct(heredoc, y);
		y++;
	}
}

int	create_heredoc_files(int nbr_of_heredoc, t_parsed_command *array_of_cmd)
{
	t_heredoc_manip heredoc;
	init_eof_and_to_modif(nbr_of_heredoc, array_of_cmd, &heredoc);
	names_tempo_files(&heredoc);
	create_temp_files(&heredoc,nbr_of_heredoc);
		 return 0;
}

int	read_input(void)
{
	char	*input;
	char	*pos;
	t_parsed_command *ptr;
	int i;
	int heredoc_counter;

	while (1)
	{
		pos = ft_strjoin(getenv("PWD"), "> ");
		input = readline(pos);
		if (ft_strlen(input))
		{
			add_history(input);
		}
		free(pos);

		if (!ft_strncmp("exit", input, 5))
		{
			free(input);
			break;
		}

		if (ft_strlen(input))
		{
			ptr = from_input_to_group(input); // verify that the input is valid
			 if (!ptr)
			 {
				free(input);
				continue;
			 }
			 i = 0;
			int y = 0;
			heredoc_counter = 0;
			 while (ptr[i].command) //count the number of <<
			 {
				y =0;
				while (ptr[i].input_file && ptr[i].input_file[y].filename)
				{	
					if (ptr[i].input_file[y].mode == 4)
						heredoc_counter++;
					y++;
				}
				i++; 
			 }
			if (heredoc_counter == 0) // if no << find execut
			{
				printf("0 heredoc\n");
				free_new_array(&ptr);
				//t_ast_node *tree = from_text_to_tree(input, &ptr);
				// exec...
			}
			else
			{
				create_heredoc_files(heredoc_counter, ptr);
				printf("new name :%s mode : %d", ptr->input_file[0].filename, ptr->input_file[0].mode);
				free_new_array(&ptr);
			}
				//free ptr
				// count how many <<
				// create temporary file temp, .txt if 'EOF' '...' else "..."
				// readline until EOF or SIGNAL
				// transform the string : 
				// transform << into < temp1.txt   \\ later unlink the temporary file.
		}
		free(input);
	}
	rl_clear_history();
	return 0;
}

int main()
{
	read_input();
	return 0;
	
}

