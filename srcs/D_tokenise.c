/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   D_tokenise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:30:21 by tdeliot           #+#    #+#             */
/*   Updated: 2025/04/03 11:40:25 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_quote(char *input, int *i, int *y, t_parsed_command *array);
void	split_words(char *input, int *i, int *y, t_parsed_command *array);

// This function transform the input in a array t_parsed_command
// in this array only the char *text is attributed. one word for each.
// ( are one word." \"  asdf  adsf \" " is one word
// return NULL if fail. 
t_parsed_command	*tokenise(char *input)
{
	int					nbr_word;
	t_parsed_command	*array;
	int					i;
	int					y;

	y = 0;
	i = 0;
	nbr_word = count_word_valid_quote(input);
	if (nbr_word == -1 || nbr_word == 0)
	{
		printf("nbr_word error\n");
		return (NULL);
	}
	array = ft_calloc(nbr_word + 1, sizeof(t_parsed_command));
	if (!array)
		return (NULL);
	while (input[i] && y < nbr_word)
	{
		split_quote(input, &i, &y, array);
		split_special_char(input, &i, &y, array);
		split_words(input, &i, &y, array);
		i++;
	}
	return (array);
}

void	split_quote(char *input, int *i, int *y, t_parsed_command *array)
{
	int	save;
	int	count_letter;

	split_double_quote(input, i, y, array);
	if (input[*i] == '\'')
	{
		save = *i;
		count_letter = 1;
		while (input[++(*i)])
		{
			if (input[(*i)] == '\'' && input[(*i) - 1] != '\\')
				break ;
			count_letter++;
		}
		array[*y].text = ft_substr(input, save, count_letter + 1);
		(*y)++;
	}
}

void	split_words(char *input, int *i, int *y, t_parsed_command *array)
{
	int	save;
	int	count_letter;

	if ((input[*i] != '"') && (input[*i] != '(') 
		&& (input[*i] != ')') && (input[*i] != ' ')
		&& (input[*i] != '|') && (input[*i] != '&')
		&& (input[*i] != '>') && (input[*i] != '<')
		&& (input[*i] != '\'') && input[*i]) // modif
	{
		save = *i;
		count_letter = 1;
		while (input[(*i) + 1] != '<' && input[(*i) + 1] != '>'
			&& input[(*i) + 1] != '|' && input[(*i) + 1] != '&'
			&& input[(*i) + 1] != '"' && input[(*i) + 1] != '('
			&& input[(*i) + 1] != ')' && input[(*i) + 1] != ' '
			&& input[(*i) + 1] != '\'' && input[(*i) + 1])
		{
			count_letter++;
			(*i)++;
		}
		array[*y].text = ft_substr(input, save, count_letter);
		(*y)++;
	}
}

/*
int main()
{
	
	t_parsed_command *ptr;
	int i = 0;
	ptr = tokenise("adf <<sd < f  ");
	while (ptr[i].text)
	{
		printf("%s\n", ptr[i].text);
		i++;
	}
	while (i > 0)
	{
		i--;
		free(ptr[i].text);
	}
	free(ptr);

	t_parsed_command *ptr2;
	 i = 0;
	ptr2 = tokenise("     \" ");
	if (ptr2) 
	{
	while (ptr2[i].text)
	{
		printf("%s\n", ptr2[i].text);
		i++;
	}
	while (i > 0)
	{
		i--;
		free(ptr2[i].text);
	}
	free(ptr2);
	}
	

	t_parsed_command *ptr3;
	  i = 0;
	
	ptr3 = tokenise(" ls > \"\" ");
	if (!ptr3)
	{
		printf("ptr3 = NULL\n");
	return 1;
	}
	while (ptr3[i].text)
	{
		printf(".%s.\n", ptr3[i].text);
		i++;
	}
	while (i > 0)
	{
		i--;
		free(ptr3[i].text);
	}
	free(ptr3);

	printf("\n\n");
	t_parsed_command *ptr4;
	 i = 0;
	ptr4 = tokenise("abcdef ||asd >> ( sdf)  ");
	if (!ptr4)
	{
		printf("ptr4 = NULL\n");
	return 1;
	}
	while (ptr4[i].text)
	{
		printf(".%s.\n", ptr4[i].text);
		i++;
	}
	while (i > 0)
	{
		i--;
		free(ptr4[i].text);
	}
	free(ptr4);

return 0;
}*/