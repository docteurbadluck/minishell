/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ca_count_word_valid_quote.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:51:06 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/24 16:26:24 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		skip_quoted_section(const char *input, int i, char quote);
int		skip_escaped_or_quoted(const char *input, int *i, int *c, int *flag);
void	count_parentheses_or_op(int *i, const char *input, int *counter);
int		char_is(char c);

// This function count the number of word in the input, quoted part as one word
// it veryfy also that the quote are closed. it work with \" it work also with '
// which allow you to write quotationthe
int	count_word_valid_quote(const char *input)
{
	int	i;
	int	flag;
	int	counter;
	int	result;

	counter = 0;
	i = -1;
	flag = 0;
	while (input[++i])
	{
		result = skip_escaped_or_quoted(input, &i, &counter, &flag);
		if (result == -1)
			return (-1);
		if (result == 1)
			continue ;
		if (char_is(input[i]))
			flag = 0;
		else if (!flag)
		{
			counter++;
			flag = 1;
		}
		count_parentheses_or_op(&i, input, &counter);
	}
	return (counter);
}

int	skip_escaped_or_quoted(const char *input, int *i, int *counter, int *flag)
{
	int	new_pos;

	if (input[*i] == '\\' && (input[*i + 1] == '"' || input[*i + 1] == '\''))
	{
		*i += 2;
		return (1);
	}
	if (input[*i] == '"' || input[*i] == '\'')
	{
		new_pos = skip_quoted_section(input, *i, input[*i]);
		if (new_pos == -1)
			return (-1);
		(*counter)++;
		*flag = 0;
		*i = new_pos;
		return (1);
	}
	return (0);
}

int	skip_quoted_section(const char *input, int i, char quote)
{
	i++;
	while (input[i])
	{
		if (input[i] == '\\' && input[i + 1] == quote)
			i += 2;
		else if (input[i] == quote)
			break ;
		else
			i++;
	}
	if (input[i] == '\0')
		return (-1);
	return (i + 1);
}

void	count_parentheses_or_op(int *i, const char *input, int *counter)
{
	if (input[*i] == '(' || input[*i] == ')')
	{
		(*counter)++;
	}
	count_op(i, input, counter);
}

int	char_is(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == ')' || c == '(' || c == '|'
		|| c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

/*
int main()
{
	
	char *test = " a ab|cd&&def > def ||  ";
	printf("\n test : %s  : %d\n", test ,count_word_valid_quote(test));

	char *test1 = " \" ab&&v \\\" abcd  \\\" \"def  ";
	printf("\n test : %s  :%d\n", test1, count_word_valid_quote(test1));

	char *test2 = "";
	printf("%d\n",count_word_valid_quote(test2));

	char *test3 = " '  abcd def ' abd";
	printf("%d\n",count_word_valid_quote(test3));
	
	char *test4 = " ' \" abcd \"def  abd'";
	printf("%d\n",count_word_valid_quote(test4));
	
	char *test5 = "''";
	printf("%d\n",count_word_valid_quote(test5));

	char *test6 = " 'abcd def'abd";
	printf("%d\n",count_word_valid_quote(test6));

	char *test7 = " \"abc\\\"d de\\\"fabd\" ";
	printf("%d\n",count_word_valid_quote(test7));

	char *test8 = " 'abc \\' |rd de \\' fabd ' ";
	printf("%d\n",count_word_valid_quote(test8));

	char *test9 = " ((abvde || abcd) && (abc && def )) ()";
	printf("%d\n",count_word_valid_quote(test9));

	return (0);
}*/